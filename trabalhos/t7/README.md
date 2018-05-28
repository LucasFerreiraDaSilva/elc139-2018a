[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2018a) > Trabalhos

# T7: Primeiros passos com MPI

Para este trabalho, você vai precisar instalar OpenMPI, que é uma implementação do padrão MPI. As principais distribuições Linux possuem pacotes para isso (por exemplo, no Ubuntu, instale os pacotes openmpi-bin e libopenmpi-dev).


## Aquecimento

Para começar, exercite compilação e execução de programas MPI:

- Baixe o arquivo [hello_mpi.c](hello_mpi.c).

- Compile o programa:
  ```
  mpicc -o hello_mpi hello_mpi.c
  ```

- Execute o programa com 5 processos e observe a saída:
  ```
  mpiexec -np 5 hello_mpi
  ```


## Parte 1

+ Implemente uma versão em MPI do programa do trabalho [t3](../t3), que calcula repetidas vezes o produto escalar entre 2 vetores. Os argumentos do programa devem ser: o número de elementos para cada processo e o número de repetições.

+ Avalie o desempenho do programa conforme as instruções do trabalho [t3](../t3), mas usando processos ao invés de threads.

## Parte 2

Implemente um programa MPI que transporte uma mensagem em um pipeline formado por processos de 0 a NP-1 (processo 0 envia para 1, processo 1 envia para 2, ..., processo NP-1 mostra o resultado). A mensagem é um número inteiro que é incrementado antes de ser passado adiante.


## Parte 3


+ O programa [mpi_errado1.c](mpi_errado1.c) deveria realizar a troca de mensagens entre 2 processos, mas ele não funciona como esperado. Identifique o erro e corrija-o.

+ O programa [mpi_errado2.c](mpi_errado2.c) deveria realizar a troca de mensagens entre 2 processos, mas também não funciona como esperado. Identifique o erro e corrija-o.



## Entrega

No seu repositório da disciplina, na pasta `trabalhos/t7`, crie um documento `Entrega.md`, contendo:
 - Identificação da disciplina e do(a) aluno(a);
 - Respostas para as partes 1, 2 e 3, incluindo links para os códigos desenvolvidos;
 - Referências.



## Material de apoio


- [Tutorial MPI](https://computing.llnl.gov/tutorials/mpi/)  
  Tutorial do Lawrence Livermore National Laboratory (LLNL) sobre MPI.
