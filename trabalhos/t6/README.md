[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2018a) > Trabalhos

# T6: N-Rainhas com OpenMP

## Introdução

O problema das N-Rainhas é um clássico em Computação. Esse problema consiste em posicionar N damas (rainhas) em um tabuleiro de dimensão NxN, de tal modo que nenhuma rainha ataque qualquer outra. Uma rainha pode atacar outra quando estiver na mesma linha, coluna ou diagonal do tabuleiro. Dependendo do valor de N, o problema pode não ter solução, ou podem haver várias soluções. Conforme N aumenta, o tempo de solução pode tornar-se proibitivo. A programação paralela pode ser uma alternativa para reduzir este tempo.


## Desenvolvimento


1. Este trabalho pode ser feito **em dupla ou individualmente**.

2. Para começar, obtenha os arquivos da pasta [nqueens](nqueens), que contém o programa sequencial de referência para este trabalho.

3. Teste o programa sequencial com difentes parâmetros de entrada (N). Analise o código e identifique oportunidades de paralelismo, considerando que a arquitetura paralela será um computador multicore.

4. Projete **duas soluções** paralelas para o programa em questão e implemente-as usando OpenMP. Você pode, por exemplo, variar as estratégias de particionamento, de escalonamento, etc.

5.  Para avaliar o desempenho dos programas, será necessário medir os tempos de execução sequencial e paralela para diferentes configurações do problema (por exemplo, com N variando de 12 a 16) e com diferentes números de threads. Utilize a mesma técnica de medição de tempos para os dois programas.


## Entrega

No seu repositório da disciplina, na pasta `trabalhos/t6`, crie um documento `Entrega.md`, contendo:
 - Identificação da disciplina e do(s) aluno(s);
 - Links para os códigos desenvolvidos;
 - Link para **slides** explicando as estratégias de paralelização adotadas, descrevendo os experimentos realizados e discutindo os resultados obtidos;
 - Referências.

**Atenção:** Trabalhos feitos em dupla deverão constar nos repositórios de ambos os integrantes, do contrário serão avaliados como trabalhos individuais.


## Apresentação

Este trabalho deverá ser apresentado em aula no dia 8/05, usando os slides elaborados.


## Material de apoio


- [Tutorial OpenMP](https://computing.llnl.gov/tutorials/openMP/)  
  Tutorial do Lawrence Livermore National Laboratory (LLNL) sobre OpenMP.
