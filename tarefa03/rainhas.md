Inicialmente precisamos receber a entrada, criar uma matriz(tabuleiro) dinamicamente e preenchê-la.
Depois verificamos se existe alguma possibilidade de solução com base no tamanho do tabuleiro e
na quantidade de rainhas que precisamos colocar, caso não exista, imprimimos -1.
Caso exista solução, fazemos uma iteração para colocar de 0 até 5 peões.
Considerando o caso básico (0 peão), o algoritmo começa a posicionar a rainha na primeira casa do tabuleiro (0,0),
e depois irá posicionando as rainhas nas próximas colunas subsequentemente. Caso não encontre nenhuma solução, o algoritmo
retornar, tira a rainha posicionada anteriormente, e posiciona na próxima casa válida do tabuleiro e 
assim sucessivamente até achar uma solução com rainhas que não se ataquem. Para verificar que rainhas não se ataquem é invocada
uma função onde a linha é percorrida para a esquerda, as colunas são percorridas para cima e para baixo e as diagonais esquerdas
são percorridas no sentido inferior e superior.
Supondo que o algoritmo não encontre nenhuma solução com 0 peão, ele tentará encontrar com 1 peão, assim por diante.
Considerando o segundo caso (1 peão), o algoritmo posiciona o peão em todas as casas possíveis no tabuleiro, para cada vez 
que posiciona o peão é chamada a função que posiciona as rainhas, e depois tiramos o peão daquela posição para colocar na próxima
posição, até encontrar uma solução ou acabar a iteração e ir para 2 peões. Além disso, há outras diferenças quando tem
um ou mais peões no tabuleiro, na função onde são colocadas as rainhas, precisamos ver se tem peão em tal coluna para 
posicionar outra rainha nessa coluna, caso não encontre nenhuma outra posição válida nessa coluna, obrigamos a ir para a próxima.
Ademais, como nesse caso temos peão, na parte de verificar se pode colocar uma rainha em uma posição, mesmo que exista outra
rainha na mesma linha, coluna ou diagonal, o peão poderá servir de escudo.
Por fim, ao encontrar um tabuleiro válido, é mostrado a quantidade de peões utilizados, como também o tabuleiro com os peões e 
com as rainhas que precisavam ser colocadas de maneira que não se atacassem.









