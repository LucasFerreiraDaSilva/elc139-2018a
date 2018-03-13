[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2018a) > T1

TOP500 & me: Comparativo de Arquiteturas Paralelas
--------------------------------------------------

Nome: Lucas Ferreira da Silva

| Característica                                            | Computador no TOP500       | Meu computador  |
| --------------------------------------------------------- | -------------------------- | --------------- |
| Nome/Título                                               |    Discover SCU12 - NASA   |     ASUS K43E   |
| Imagem (foto, diagrama, screenshot, etc.)                 | <img src="https://www.nas.nasa.gov/SC15/assets/images/content/33_Pfaff_B_Tripling_Compute_1_SC15_big.jpg" width="100"> | <img src="https://www.asus.com/media/BR/products/0QXA6BlaKTmYocDA/P_500.jpg" width="100">|
| Classificação de Flynn                                    |          MIMD              |       MIMD      |
| Memória: compartilhada, distribuída ou ambas?             |         Ambas              |  Compartilhada  |
| Número total de núcleos de processamento                  |         17,136             |        2        |
| Fabricante e modelo do(s) processador(es)                 |  Intel® Xeon® E5-2697v3 14C| Intel® Core™ i5-2410M |
| Frequência do(s) processador(es)                          |           2.6GHz           |    2.30GHz      |
| Memória total                                             |        78,336 GB           |      6 GB       |
| Tipo(s) de interconexão entre os núcleos/processadores    |      Infiniband FDR        |  Quick Path Interconnect (QPI)          |
| Desempenho Linpack                                        |      548.672 TFlop/s       |        *        |

*O computador congela antes de acabar a execução do benchmark. (3 tentativas de execução)

### Referências
- Intel. Intel® Math Kernel Library Benchmarks (Intel® MKL Benchmarks). https://software.intel.com/en-us/articles/intel-mkl-benchmarks-suite
- Top500.org. Discover SCU12 - Rackable Cluster, Xeon E5-2697v3 14C 2.6GHz, Infiniband FDR. https://www.top500.org/system/178530
- Intel. Processador Intel® Core™ i5-2410M. https://ark.intel.com/pt-br/products/52224/Intel-Core-i5-2410M-Processor-3M-Cache-up-to-2_90-GHz
- NASA. Tripling the Compute Capacity at the NASA Center for Climate Simulation. https://www.nas.nasa.gov/SC15/demos/demo33.html#prettyPhoto
- Intel. Intel® QuickPath Interconnect. https://www.intel.com/content/www/us/en/io/quickpath-technology/quickpath-technology-general.html
