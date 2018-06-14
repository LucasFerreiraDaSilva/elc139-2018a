[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2018a) > Trabalhos

# T8: Comunicação coletiva em MPI

Aluno: Lucas Ferreira da Silva

Disciplina: ELC139 - Programação Paralela

## Implementações com comunicação coletiva em MPI:

Os links abaixo são para as implementações das tarefas 1 e 2 do trabalho 8:

**Tarefa 1:**

```
No código fornecido, são feitas várias chamadas de send/recv que podem ser trocadas por outras funções. Você deve descobrir quais são essas funções, fazer a alteração e testar se o resultado é o mesmo. (O programa gera sempre as mesmas matrizes, então o resultado deve ser sempre o mesmo).
```

[Implementação da tarefa 1](matrix_mult_pt1.c)


**Tarefa 2:**

```
Implemente também uma versão usando quantidades de envio/recebimento variáveis, o que permite que o número de linhas da matriz A não precise ser proporcional ao número de processos.
```

[Implementação da tarefa 2](matrix_mult_pt2.c)


# Referências
- [MPI: A Message-Passing Interface Standard](https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf)  
- [A Comprehensive MPI Tutorial Resource](http://mpitutorial.com/)  
- [MPI Scatter, Gather, and Allgather](http://mpitutorial.com/tutorials/mpi-scatter-gather-and-allgather/)  
- [MPI Broadcast and Collective Communication](http://mpitutorial.com/tutorials/mpi-broadcast-and-collective-communication/)  
- [Examples using MPI_SCATTER, MPI_SCATTERV](https://www.mpi-forum.org/docs/mpi-1.1/mpi-11-html/node72.html)  