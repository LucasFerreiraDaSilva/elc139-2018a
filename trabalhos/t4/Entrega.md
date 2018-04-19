[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2018a) > Trabalhos

# T4: Scheduling com OpenMP

Aluno: Lucas Ferreira da Silva

Disciplina: ELC139 - Programação Paralela

##  Casos de teste
Para a realização deste trabalho foram implementados 6 casos de teste utilizando OpenMP, cuja implementação pode ser encontrada no seguinte arquivo: [OpenMpABC.cpp](OpenMpABC.cpp). A seguir a descrição e as saídas para cada um dos casos de teste realizados.

OBS.: conforme o enunciado do trabalho, o particionamento foi deixado todo a cargo do OpenMP, portanto não foram utilizados valores para os chunks.

### 1) Sem tratamento de exclusão mútua e com scheduling AUTO

Para o tratamento da exclusão mútua, foi utilizada a cláusula critical do OpenMP conforme pode ser visto nos trechos de código a seguir:

``` c
    // Trecho de código sem o tratamento de exclusão mútua

    array[index] = c;
    spendSomeTime();
    index++;

```

``` c
    // Trecho de código com tratamento de exclusão mútua

    #pragma omp critical
    {
        array[index] = c;
        spendSomeTime();
        index++;
    }
```

Nos códigos acima pode-se perceber que para tratar a região crítica do programa bastou somente sinalizar com a diretiva critical qual o trecho que há acessos concorrentes e que estão desprotegidos da exclusão mútua, feito isso, com apenas 3 linhas a mais o problema foi designado ao OpenMP, que se encarregará de evitar as condições de corrida no acesso desse trecho.

A saída da versão sem o tratamento da região crítica mostra com clareza que sem a exclusão mútua o array não é totalmente preenchido e a saída pe incorreta, pois a soma das quantidades de A, B e C não é igual ao valor 60:

```
CACBCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCAB--
A=19 B=19 C=20

```
Os demais casos de teste foram implementados já tratando a exclusão mútua da região citada acima.


### 2) Com tratamento de exclusão mútua e com scheduling STATIC
Nesse tipo de escalonamneto o OpenMP, se não for fornecido um valor de chunk, basicamente divide o número de iterações do laço pelo número de threads que o executarão em paralelo, fazendo com que assim todas as threads possuam a mesma quantidade de iterações.

Saída do código:

```
AAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCBBBBBBBBBBBBBBBBBBBB
A=20 B=20 C=20 

```


### 3) Com tratamento de exclusão mútua e com scheduling DYNAMIC
Neste caso, como não foi especificado um valor para o chunk, por default o chunk é 1, sendo assim, cada thread inicialmente será responsável por uma iteração do laço e somente que o trabalho dessa iteração acabar que a thread pega uma nova iteração. A distribuição das iterações do laço entre as threads não segue um padrão e será dado a primeira thread que solicitar uma nova iteração.

Saída do código:

```
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBAC
A=1 B=58 C=1 
```

### 4) Com tratamento de exclusão mútua e com scheduling GUIDED
Este caso, utilizando o scheduling guided, é semelhante ao anterior (dynamic), porém com o diferencial no tamanho do chunk. no scheduling guided, se não informado, o primeiro chunk geralmente será igual ao númeroi de iterações dividido pelo número de threads, porém vai diminuindo conforme a execução vai sendo realizada. Esse tipo de escalonamento geralmente é utilizado em problemas cuja carga está concentrada nas últimas iterações do laço objetivando assim uma maior vazão já que o trabalho será escalonado com um chunck próximo de 1 nas iterações finais.

Saída do código:

```
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCBBBBBBBBBBBBBB
A=37 B=14 C=9 
```

### 5) Com tratamento de exclusão mútua e com scheduling AUTO
No caso da utilização do scheduling auto, a tarefa de escolher a melhor forma de escalonar o problema é designada ao compilador. No problema em questão, dada a característica de homogeniedade da carga de trabalho entre as iterações, pode-se perceber que o compilador optou pelo schedule static.

Saída do código:

```
BBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCC
A=20 B=20 C=20 

```

### 6) Com tratamento de exclusão mútua e com scheduling RUNTIME
Como a propria designação já diz, esse caso deixa que o tipo de scheduling seja escolhido em tempo de execução. Uma das formas de especificar o schedule que será utilizado com esssa estratégia é alterar a variável de ambiente OMP_SCHEDULE. Outra maneira é chamar dentro do próprio código a função omp_set_schedule(). Esse caso não é muito utilizado, porém, possibilita que o scheduling seja trocado no meio da execução pelo próprio algoritmo.

Saída do código:

```
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBAC
A=1 B=58 C=1 
```

# Referências

- OpenMP Scheduling. http://cs.umw.edu/~finlayson/class/fall14/cpsc425/notes/12-scheduling.html
- Synchronization Constructs, CRITICAL Directive. https://computing.llnl.gov/tutorials/openMP/#CRITICAL
- Loop Scheduling in OpenMP. http://www.openmp.org/wp-content/uploads/SC17-Kale-LoopSchedforOMP_BoothTalk.pdf
