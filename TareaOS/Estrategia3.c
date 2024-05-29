/**Estrategia 3: Modificar la estructura Range para almacenar el número de primos encontrados */
/**Miguel Angel Moreno Romero (2125737)
Juan Esteban Guerrero Camacho (2040798)
Juan David Fonseca - 2323942
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
    int primeCount;
} Range;

void *countPrimes(void *arg) {
    Range *range = (Range *)arg;
    range->primeCount = 0;
    for (int num = range->start; num <= range->end; num++) {
        int prime = 1;
        if (num < 2) prime = 0;
        for (int i = 2; i*i <= num; i++) {
            if (num % i == 0) {
                prime = 0;
                break;
            }
        }
        if (prime) range->primeCount++;
    }
    return NULL;
}

int main() {
    int numThreads = 4;
    pthread_t threads[numThreads];
    Range ranges[numThreads];
    int totalPrimes = 0;

    for (int i = 0; i < numThreads; i++) {
        ranges[i].start = i * 25 + 1;
        ranges[i].end = (i + 1) * 25;
        ranges[i].primeCount = 0;
        pthread_create(&threads[i], NULL, countPrimes, &ranges[i]);
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
        totalPrimes += ranges[i].primeCount;
    }

    printf("Total primes: %d\n", totalPrimes);
    return 0;
}
