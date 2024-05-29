/**Estrategia 1: Cada hilo retorna el número de primos encontrados*/
/**Miguel Angel Moreno Romero (2125737)
Juan Esteban Guerrero Camacho (2040798)
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

void *countPrimes(void *arg) {
    Range *range = (Range *)arg;
    int count = 0;
    for (int num = range->start; num <= range->end; num++) {
        int prime = 1;
        if (num < 2) prime = 0;
        for (int i = 2; i*i <= num; i++) {
            if (num % i == 0) {
                prime = 0;
                break;
            }
        }
        if (prime) count++;
    }
    return (void *)(intptr_t)count;
}

int main() {
    int numThreads = 4;
    pthread_t threads[numThreads];
    Range ranges[numThreads];
    int status[numThreads];
    int totalPrimes = 0;

    for (int i = 0; i < numThreads; i++) {
        ranges[i].start = i * 25 + 1;
        ranges[i].end = (i + 1) * 25;
        pthread_create(&threads[i], NULL, countPrimes, &ranges[i]);
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], (void **)&status[i]);
        totalPrimes += status[i];
    }

    printf("Total primes: %d\n", totalPrimes);
    return 0;
}
