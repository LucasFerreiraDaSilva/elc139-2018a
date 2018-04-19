#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include <omp.h>

class SharedArray
{
    private:
        char *array;
        int index;
        int size;

    public:
        SharedArray(int n) : size(n), index(0)
        {
            array = new char[size];
            std::fill(array, array + size, '-');
        }

        ~SharedArray()
        {
            delete[] array;
        }

        void addChar(char c)
        {
            #pragma omp critical
            {
                array[index] = c;
                spendSomeTime();
                index++;
            }
        }

        void addCharUnsecure(char c)
        {
            array[index] = c;
            spendSomeTime();
            index++;
        }

        int countOccurrences(char c)
        {
            return std::count(array, array + size, c);
        }

        std::string toString()
        {
            return std::string(array, size);
        }

    private:
        void spendSomeTime()
        {
            for (int i = 0; i < 10000; i++)
                for (int j = 0; j < 1000; j++);
        }
};

class ArrayFiller
{
    private:
        static const int nThreads = 3;
        static const int nTimes = 20;
        SharedArray *array;

    public:
        ArrayFiller()
        {
            array = new SharedArray(nThreads * nTimes);
        }

        void fillArrayConcurrently(int sched)
        {   
            int i;
            switch(sched){
                case 0: // Sem o critical
                    #pragma omp parallel for schedule(auto) num_threads(nThreads) private(i)
                    for (i = 0; i < nTimes*nThreads; i++)
                        array->addCharUnsecure('A' + omp_get_thread_num());
                    break;

                case 1: // Schedule static
                    #pragma omp parallel for schedule(static) num_threads(nThreads) private(i)
                    for (i = 0; i < nTimes*nThreads; i++)
                        array->addChar('A' + omp_get_thread_num());
                    break;
                
                case 2: // Schedule dynamic
                    #pragma omp parallel for schedule(dynamic) num_threads(nThreads) private(i)
                    for (i = 0; i < nTimes*nThreads; i++)
                        array->addChar('A' + omp_get_thread_num());
                    break;

                case 3: // Schedule guided
                    #pragma omp parallel for schedule(guided) num_threads(nThreads) private(i)
                    for (i = 0; i < nTimes*nThreads; i++)
                        array->addChar('A' + omp_get_thread_num());
                    break;

                case 4: // Schedule auto
                    #pragma omp parallel for schedule(auto) num_threads(nThreads) private(i)
                    for (i = 0; i < nTimes*nThreads; i++)
                        array->addChar('A' + omp_get_thread_num());
                    break;

                case 5: // Schedule runtime
                    #pragma omp parallel for schedule(runtime) num_threads(nThreads) private(i)
                    for (i = 0; i < nTimes*nThreads; i++)
                        array->addChar('A' + omp_get_thread_num());
                    break;
            }
            
        }

        void printStats()
        {
            std::cout << array->toString() << std::endl;
            for (int i = 0; i < nThreads; ++i)
                std::cout << (char)('A' + i) << "="
                        << array->countOccurrences('A' + i) << " ";
            std::cout << std::endl;
        }

        ~ArrayFiller()
        {
            delete array;
        }
};

int main()
{
    std::cout << "Cada thread vai adicionar um caracter no array n vezes (n=20)" << std::endl;
    std::cout << "Resultados corretos possuem um total exato de nThreads*nTimes caracteres" << std::endl;

    std::cout << "\nCaso 1: Sem tratamento de exclusão mútua e com scheduling AUTO (resultado errado)" << std::endl;
    ArrayFiller c1;
    c1.fillArrayConcurrently(0);
    c1.printStats();

    std::cout << "\nCaso 2: Com tratamento de exclusão mútua e com scheduling STATIC" << std::endl;
    ArrayFiller c2;
    c2.fillArrayConcurrently(1);
    c2.printStats();

    std::cout << "\nCaso 3: Com tratamento de exclusão mútua e com scheduling DYNAMIC" << std::endl;
    ArrayFiller c3;
    c3.fillArrayConcurrently(2);
    c3.printStats();

    std::cout << "\nCaso 4: Com tratamento de exclusão mútua e com scheduling GUIDED" << std::endl;
    ArrayFiller c4;
    c4.fillArrayConcurrently(3);
    c4.printStats();

    std::cout << "\nCaso 5: Com tratamento de exclusão mútua e com scheduling AUTO" << std::endl;
    ArrayFiller c5;
    c5.fillArrayConcurrently(4);
    c5.printStats();

    std::cout << "\nCaso 6: Com tratamento de exclusão mútua e com scheduling RUNTIME" << std::endl;
    ArrayFiller c6;
    c6.fillArrayConcurrently(5);
    c6.printStats();

}