[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2018a) > Trabalhos

# T2: Experiências com Profilers


## Parte 1

1. Verifique se você tem GCC instalado. Se não tiver, pode usar algum computador do NCC (mesmo remotamente).

2. Faça fetch e merge do repositório original da disciplina para obter os arquivos necessários para o trabalho. 
Para isso, consulte a documentação do cliente Git que você estiver usando. Se estiver usando git via linha de comando, faça assim:
   ```
   git remote add upstream https://github.com/AndreaInfUFSM/elc139-2018a.git
   git fetch upstream
   git merge upstream/master master
   ```
   Obs.: o primeir comando liga seu repositório local com o repositório remoto original da disciplina. Você só fará isso uma vez. 
   Para os outros trabalhos, basta fazer fetch e merge.
  
3. Abra o programa [dotprod_seq.c](dotprod_seq/dotprod_seq.c), que contém o código fonte de um programa simples para calcular o produto escalar de 2 vetores. 
Este programa permite configurar o tamanho dos vetores e o número de repetições do cálculo, para variar a carga de trabalho.

3. Compile o programa [dotprod_seq.c](dotprod_seq/dotprod_seq.c):

   ```
   make
   ```

4. Execute o programa com uma configuração "pequena", por exemplo:

   ```
   ./dotprod_seq 3000 10
   ```

5. Execute o programa com uma configuração maior, por exemplo:

   ```
   ./dotprod_seq  30000000 90
   ```

6. Edite o Makefile fornecido e habilite a flag de profiling (-pg).

7. Recompile o programa e execute-o novamente. Ao final deve ser gerado um arquivo gmon.out.

8. Use o profiling gprof para analisar o perfil da execução:

   ```
   gprof dotprod_seq
   ```

9. Faça profiling do programa com diferentes configurações, observando os perfis gerados.

10. Responda:
  - (a) O perfil é afetado pelas opções de configuração?
  - (b) Pelo perfil de execução, há alguma função que poderia ser candidata a paralelização? Por quê?



## Parte 2


+ Escolha um programa que você tenha desenvolvido, ou que seja desenvolvido por outros mas que você conheça o código. 
Pode ser um programa em qualquer linguagem, de preferência estruturado em vários subprogramas (procedimentos, funções, métodos...), e que possa ter a entrada variada facilmente.

+ Escolha 2 profilers para a linguagem alvo e procure repetir os passos da Parte 1, adequando-os a possíveis diferenças.

+ Observe e faça anotações sobre: 
   - (a) particularidades de instalação, recursos ou funcionamento dos profilers, 
   - (b) resultados obtidos e 
   - (c) dúvidas e/ou dificuldades encontradas.


## Entrega

No seu repositório da disciplina, na pasta `trabalhos/t2`, crie um documento `Entrega.md`, contendo:
 - Identificação completa da disciplina e do aluno
 - Sumário;
 - Seções separadas para a Parte 1 e a Parte 2;
 - Anotações, respostas, screenshots e quaisquer outras observações adicionais sobre cada um dos itens das Partes 1 e 2;
 - Referências.



