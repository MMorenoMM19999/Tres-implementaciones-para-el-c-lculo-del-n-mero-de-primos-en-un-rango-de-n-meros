/**Estrategia 2: Ajuste del rango y el número de hilos, comprobaciones de error, algoritmo más eficiente para es_primo*/
/**Miguel Angel Moreno Romero (2125737)
Juan Esteban Guerrero Camacho (2040798)
Juan David Fonseca - 2323942
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

// Estructura para mantener el rango para cada hilo
typedef struct {
    int inicio;
    int fin;
    int count;
} Rango;

// Función para verificar si un número es primo
int es_primo(int num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}

// Función del hilo para verificar números primos en un rango dado
void* verificar_primo(void* arg) {
    Rango* rango = (Rango*)arg;
    rango->count = 0;
    for (int i = rango->inicio; i <= rango->fin; i++) {
        if (es_primo(i)) {
            rango->count++;
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <rango> <num_hilos>\n", argv[0]);
        return 1;
    }

    int rango = atoi(argv[1]);
    int num_hilos = atoi(argv[2]);
    if (rango <= 0 || num_hilos <= 0) {
        fprintf(stderr, "Rango y número de hilos deben ser mayores a 0\n");
        return 1;
    }

    pthread_t hilos[num_hilos];
    Rango rangos[num_hilos];

    // Dividir el rango en partes para cada hilo
    int tamano_rango = rango / num_hilos;
    for (int i = 0; i < num_hilos; i++) {
        rangos[i].inicio = i * tamano_rango + 1;
        rangos[i].fin = (i == num_hilos - 1) ? rango : (i + 1) * tamano_rango;
        if (pthread_create(&hilos[i], NULL, verificar_primo, &rangos[i]) != 0) {
            perror("Error al crear el hilo");
            return 1;
        }
    }

    // Unir hilos
    int total_primos = 0;
    for (int i = 0; i < num_hilos; i++) {
        pthread_join(hilos[i], NULL);
        total_primos += rangos[i].count;
    }

    printf("Total de primos: %d\n", total_primos);

    return 0;
}
