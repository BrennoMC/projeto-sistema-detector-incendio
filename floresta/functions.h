#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <pthread.h>

#define TAMANHO 30

typedef struct {
    char estado;
    pthread_mutex_t lock;
} Celula;

void inicializar_floresta();
void* sensor(void* args);
void* gerador_de_incendios(void* args);
void* central_de_controle(void* args);
void imprimir_floresta();

extern Celula floresta[TAMANHO][TAMANHO];

#endif
