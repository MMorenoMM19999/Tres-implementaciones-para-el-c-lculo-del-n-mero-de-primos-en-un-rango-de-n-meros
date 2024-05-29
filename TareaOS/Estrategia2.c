/**Estrategia 2: Usar un vector global para almacenar el número de primos encontrados por cada hilo*/
/**Miguel Angel Moreno Romero (2125737)
Juan Esteban Guerrero Camacho (2040798)
Juan David Fonseca - 2323942
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4
int primesFound[NUM_THREADS];

typedef struct {
    int start;
    int end;
    int index;
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
    primesFound[range->index] = count;
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    Range ranges[NUM_THREADS];
    int totalPrimes = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        ranges[i].start = i * 25 + 1;
        ranges[i].end = (i + 1) * 25;
        ranges[i].index = i;
        pthread_create(&threads[i], NULL, countPrimes, &ranges[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        totalPrimes += primesFound[i];
    }

    printf("Total primes: %d\n", totalPrimes);
    return 0;
}
