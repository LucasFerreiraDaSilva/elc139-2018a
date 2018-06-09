[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2018a) > Trabalhos

# T8: Comunicação coletiva em MPI

Este trabalho foi formulado pelo mestrando Rudieri Colbek, como parte de suas atividades de docência orientada.

É fornecido um arquivo [matrix_mult_sr.c](matrix_mult_sr.c), que contém uma versão paralelizada usando send/receive. O mesmo gera duas matrizes A e B, depois multiplica as mesmas e gera a matriz C. No final são mostradas todas as matrizes.

## Trabalho

1. No código fornecido, são feitas várias chamadas de send/recv que podem ser trocadas por outras funções. Você deve descobrir quais são essas funções, fazer a alteração e testar se o resultado é o mesmo. (O programa gera sempre as mesmas matrizes, então o resultado deve ser sempre o mesmo).

2. Implemente também uma versão usando quantidades de envio/recebimento variáveis, o que permite que o número de linhas da matriz A não precise ser proporcional ao número de processos.


## Entrega

No seu repositório da disciplina, na pasta `trabalhos/t8`, crie um documento `Entrega.md`, contendo:
 - Identificação da disciplina e do aluno;
 - Links para os códigos desenvolvidos;
 - Referências.


## Apresentação

Os códigos-fonte deste trabalho deverão ser apresentado em aula no dia 14/06.


## Material de apoio


- [MPI: A Message-Passing Interface Standard](https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf)  
- [A Comprehensive MPI Tutorial Resource](http://mpitutorial.com/)  
- [Exemplos de comunicação](exemplos/)


