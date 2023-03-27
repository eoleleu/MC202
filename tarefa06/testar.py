#!/usr/bin/env python

import _thread
import argparse
import os
import re
import sys
import threading
from contextlib import contextmanager
from os import listdir
from os.path import isfile, join
from subprocess import PIPE, TimeoutExpired, run


class BaseTask:
    TIME_LIMIT_SECONDS = 0.2
    ABS_TOLERANCE = 0.001

    SPACES_RE = re.compile(r"\s+", re.M)
    CFLAGS = ["-std=c99", "-Wall", "-Werror", "-Werror=vla", "-g"]
    LDFLAGS = ["-lm"]

    def __init__(self, continue_on_error=True, only_matching=None):
        self.continue_on_error = continue_on_error
        self.only_matching = only_matching
        self.compiled_binaries = set()
        self.tested_cases = set()
        self.passed_cases = set()
        self.tested_units = set()
        self.passed_units = set()
        self.run_valgrind = False
        self.show_all_errors = False
        self.python3 = self.find_python3()

    def find_python3(self):
        suffix = ".exe" if os.name == "nt" else ""
        for py in ["python3", "python", "py"]:
            for path in os.environ["PATH"].split(os.pathsep):
                exe_file = os.path.join(path, py + suffix)
                if isfile(exe_file):
                    return py
        print("o interpretador python3 não está no path; verifique sua instalação")
        sys.exit(1)

    def read_file_utf8(self, filename):
        assert isfile(filename), f"não existe o arquivo {filename}"
        try:
            with open(filename, encoding="utf-8", errors="strict") as f:
                return f.read()
        except ValueError:
            raise AssertionError(f"enconding inválido em {filename}; por favor, use UTF-8")
        except Exception as e:  # noqa
            raise AssertionError(f"falha ao ler arquivo {filename}: {e}")

    def strip_spaces(self, text):
        return self.SPACES_RE.sub(" ", text.strip())

    def compare_stripped(self, out, res):
        return self.strip_spaces(out) == self.strip_spaces(res)

    def exists(self, filename):
        assert isfile(filename), f"você deve criar um arquivo {filename}"

    def normalize_binary_name(self, binary):
        if os.name == "nt":
            binary += ".exe"
        return join(".", binary)

    def compare_files(self, out, res):
        out = self.read_file_utf8(out)
        res = self.read_file_utf8(res)
        return self.compare_output(out, res)

    @staticmethod
    def get_possible_number(text):
        try:
            return float(text)
        except ValueError:
            return None

    def compare_doubles(self, out, res):
        import math

        out = out.split()
        res = res.split()
        if len(out) != len(res):
            return False
        for a, b in zip(out, res):
            if a == b:
                continue
            a = self.get_possible_number(a)
            b = self.get_possible_number(b)
            if a is None or b is None:
                return False
            if not math.isclose(a, b, abs_tol=self.ABS_TOLERANCE):
                return False
        return True

    def compare_output(self, out, res):
        return self.compare_stripped(out, res)

    def make(self, binary):
        norm_binary = self.normalize_binary_name(binary)
        if binary not in self.compiled_binaries:
            if isfile(norm_binary):
                os.remove(norm_binary)
            self.compiled_binaries.add(binary)
            self.exists("Makefile")
            p = run(["make", binary])
            assert p.returncode == 0, f"falha ao criar {norm_binary} com Makefile"
        assert isfile(norm_binary), f"o Makefile não criou um arquivo {norm_binary}"
        return norm_binary

    def compile(self, sources=None, binary=None):
        if sources is None:
            sources = sorted([f for f in listdir(".") if f.endswith(".c")])
        if binary is None:
            binary = sources[0][:-2]  # binário padrão é primeiro arquivo sem extensão .c
        norm_binary = self.normalize_binary_name(binary)
        if binary not in self.compiled_binaries:
            if isfile(norm_binary):
                os.remove(norm_binary)
            self.compiled_binaries.add(binary)
            for source in sources:
                self.exists(source)
            compile_cmd = ["gcc"] + self.CFLAGS + sources + ["-o", binary] + self.LDFLAGS
            p = run(compile_cmd)
            assert p.returncode == 0, f"falha ao compilar {norm_binary}"
        assert isfile(norm_binary), f"não foi possível compilar {norm_binary}"
        return norm_binary

    def run_binary_inner(self, cmd, stdin, stdout, input):
        if input is None:
            p = run(
                cmd,
                stdin=stdin,
                stdout=stdout,
                encoding="utf8",
                errors="ignore",
                timeout=self.TIME_LIMIT_SECONDS,
            )
        else:
            p = run(
                cmd,
                input=input,
                stdout=stdout,
                encoding="utf8",
                errors="ignore",
                timeout=self.TIME_LIMIT_SECONDS,
            )
        assert p.returncode == 0, f"código de saída é {p.returncode}"
        return p

    def run_binary(
        self,
        cmd,
        stdin,
        stdout,
        input=None,
        in_filename=None,
        out_filename=None,
    ):
        cmd_str = " ".join([c if " " not in c and c != "" else f'"{c}"' for c in cmd])
        if in_filename:
            cmd_str += f" < {in_filename}"
        if out_filename:
            cmd_str += f" > {out_filename}"
        if input:
            cmd_str += f' com entrada "{input}"'
        try:
            return self.run_binary_inner(cmd, stdin, stdout, input)
        except AssertionError as e:
            raise AssertionError(f"falha ao executar {cmd_str} : {e}")
        except TimeoutExpired:
            raise AssertionError(
                f"falha ao executar {cmd_str} : tempo limite de {self.TIME_LIMIT_SECONDS}s excedido"
            )

    def test_one_case(self, cmd, in_filename):
        out_filename = in_filename.replace(".in", ".out")
        res_filename = in_filename.replace(".in", ".res")
        with open(in_filename) as i, open(out_filename, "w") as o:
            self.run_binary(cmd, i, o, in_filename=in_filename, out_filename=out_filename)
        ok = self.compare_files(out_filename, res_filename)
        assert ok, f'execute: diff "{out_filename}" "{res_filename}"'

    def test_cases(self, binary, in_filenames, folder="testes", args=[]):
        self.exists(binary)
        cmd = [binary] + args
        assert type(in_filenames) != str, "erro no caso de teste, deveria ser lista de strings"
        errors = []
        for in_filename in in_filenames:
            in_filename = join(folder, in_filename)
            try:
                self.tested_cases.add(in_filename)
                self.test_one_case(cmd, in_filename)
                self.passed_cases.add(in_filename)
                print(f"  -> {in_filename} passou")
            except AssertionError as e:
                print(f"  -> {in_filename} falhou")
                errors.append(str(e))
                if not self.continue_on_error:
                    break
        assert not errors, "\n  -> ".join(errors)

    def input_output(self, binary, input, expected, args=[]):
        self.exists(binary)
        cmd = [binary] + args
        p = self.run_binary(cmd, None, PIPE, input=input)
        output = p.stdout.strip()
        ok = self.compare_output(output, expected)
        assert ok, f'para entrada "{input}", a saída é "{output}", mas era esperado "{expected}"'

    def should_test(self, name):
        if not name.startswith("teste_"):
            return False
        if not self.only_matching:
            return True
        for pattern in self.only_matching:
            if pattern in name:
                return True
        return False

    def test_units(self):
        for name in sorted(dir(self)):
            if not self.should_test(name):
                continue
            print()
            print(f"Executando {name}...")
            sys.stderr.flush()
            sys.stdout.flush()
            try:
                test = getattr(self, name)
                self.tested_units.add(name)
                test()
                self.passed_units.add(name)
                print(f"{name}: OK")
            except AssertionError as e:
                print(f"{name}: FALHOU")
                if "privado" not in name or self.show_all_errors:
                    print(f"  -> {e}\n")
                if not self.continue_on_error:
                    break

    def case_range(self, input_template, start, end):
        input_files = []
        for i in range(start, end + 1):
            input_files.append(input_template.format(i))
        return input_files

    def has_n_words(self, filename, n_words):
        text = self.read_file_utf8(filename)
        length = len(text.split())
        assert length >= n_words, f"{filename} deve ter pelos menos {n_words} palavras"

    @staticmethod
    @contextmanager
    def time_limit(seconds, desc):
        timer = threading.Timer(seconds, lambda: _thread.interrupt_main())
        timer.start()
        try:
            yield
        except KeyboardInterrupt:
            raise AssertionError(f"{desc} falhou: tempo limite de {seconds}s excedido")
        finally:
            timer.cancel()

    def test_closure(self, closure, desc="comando"):
        import traceback

        with self.time_limit(self.TIME_LIMIT_SECONDS, desc):
            try:
                closure()
            except Exception:
                tb = traceback.format_exc()
                assert False, f"algum erro ocorreu durante a execução:\n{tb}"


class Task(BaseTask):
    def teste_1_otimizar_pequeno(self):
        binary = self.make("otimizar")
        self.test_cases(binary, self.case_range("otimizar{}.in", 1, 4))

    def teste_2_otimizar_medio(self):
        binary = self.make("otimizar")
        self.test_cases(binary, self.case_range("otimizar{}.in", 5, 7))

    def teste_3_calculadora_pequeno(self):
        binary = self.make("calculadora")
        self.test_cases(binary, self.case_range("calculadora{}.in", 1, 2))

    def teste_4_calculadora_medio(self):
        binary = self.make("calculadora")
        self.test_cases(binary, self.case_range("calculadora{}.in", 3, 6))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Testa tarefa.")
    parser.add_argument("only", nargs="*", help="apenas unidades contendo essa string")
    parser.add_argument("-c", action="store_true", help="continua mesmo que anteriores falhem")
    args = parser.parse_args()
    Task(args.c, args.only).test_units()
