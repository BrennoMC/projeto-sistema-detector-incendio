#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "functions.h"

#define TAMANHO 30

#define LIVRE '-'
#define SENSOR 'T'
#define FOGO '@'
#define QUEIMADO '/'

Celula floresta[TAMANHO][TAMANHO];

void inicializar_floresta() {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            floresta[i][j].estado = LIVRE;
            pthread_mutex_init(&floresta[i][j].lock, NULL);
        }
    }
}

void* sensor(void* args) {
    int x = ((int*)args)[0];
    int y = ((int*)args)[1];

    while (1) {
        pthread_mutex_lock(&floresta[x][y].lock);
        if (floresta[x][y].estado == FOGO) {
            printf("\nSensor [%d, %d] detectou fogo!\n", x, y);
        }
        pthread_mutex_unlock(&floresta[x][y].lock);
        sleep(1);
    }
}

void* gerador_de_incendios(void* args) {
    while (1) {
        sleep(3);

        int x = rand() % TAMANHO;
        int y = rand() % TAMANHO;

        pthread_mutex_lock(&floresta[x][y].lock);
        if (floresta[x][y].estado == LIVRE) {
            floresta[x][y].estado = FOGO;
            printf("\nIncêndio iniciado em [%d, %d]\n", x, y);
        }
        pthread_mutex_unlock(&floresta[x][y].lock);
    }
}

void* central_de_controle(void* args) {
    while (1) {
        for (int i = 0; i < TAMANHO; i++) {
            for (int j = 0; j < TAMANHO; j++) {
                pthread_mutex_lock(&floresta[i][j].lock);
                if (floresta[i][j].estado == FOGO) {
                    printf("Central: Combatendo fogo em [%d, %d]\n", i, j);
                    floresta[i][j].estado = QUEIMADO;
                }
                pthread_mutex_unlock(&floresta[i][j].lock);
            }
        }
        sleep(2);
    }
}

void imprimir_floresta() {

    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            pthread_mutex_lock(&floresta[i][j].lock);
            printf("%c ", floresta[i][j].estado);
            pthread_mutex_unlock(&floresta[i][j].lock);
        }
        printf("\n");
    }
}
