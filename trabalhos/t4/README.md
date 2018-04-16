[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2018a) > Trabalhos

# T4: Scheduling com OpenMP 

## Preparação

1. Para realizar este trabalho, escolha um computador com mais de um núcleo de processamento. 

2. Faça fetch e merge do repositório original da disciplina para obter o arquivo de exemplo necessário para o trabalho.


3. Estude o programa [ThreadDemoABC.cpp](ThreadDemoABC.cpp), que implementa 3 casos de teste para ilustrar o escalonamento de 3 threads que atualizam concorrentemente um array compartilhado. Este programa usa POSIX Threads. Cada thread insere 20 caracteres A, B ou C na próxima posição livre. Os caracteres podem ser adicionados em diferentes posições, dependendo do escalonamento das threads. Qualquer que seja a ordem, no final de um caso de teste a contagem de caracteres no array deve ser igual a 60, a não ser em casos de implementação incorreta, em que não é garantida exclusão mútua.



4. Compile e execute o programa, observando os resultados em cada caso de teste.

   ```
   g++ -std=c++11 ThreadDemoABC.cpp -pthread -o ThreadDemoABC
   ./ThreadDemoABC
   
   ```


## Trabalho

1. Usando o programa [ThreadDemoABC.cpp](ThreadDemoABC.cpp) como inspiração, você deverá criar um novo programa usando OpenMP, para ilustrar os diferentes tipos de escalonamento disponíveis para a cláusula `schedule`. Note que, ao contrário do programa com POSIX Threads, você deixará o particionamento também a cargo do OpenMP (no programa original, isso é feito manualmente e cada thread faz exatamente 20 inserções).

2. Seu programa deverá implementar pelo menos um caso incorreto, ilustrando o que acontece sem exclusão mútua.


## Entrega

No seu repositório da disciplina, na pasta `trabalhos/t4`, crie um documento `Entrega.md`, contendo:
 - Identificação da disciplina e do aluno;
 - Link para o programa desenvolvido e descrição dos casos de teste.
 - Exemplo de saída do programa.
 - Referências.
 
 
## Material de apoio

- [Tutorial OpenMP](https://computing.llnl.gov/tutorials/openMP/)  
  Tutorial do Lawrence Livermore National Laboratory (LLNL) sobre OpenMP. 

