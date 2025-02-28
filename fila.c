#include <stdlib.h>
#include "fila.h"

Fila *InitializeQueue(int capacidade){

    Fila *fila = (Fila*)malloc(sizeof(Fila));
    fila->array = (int*)malloc(capacidade*sizeof(int));

    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
    fila->capacidade = capacidade;

    return fila;
}

int Enqueue(Fila *fila, int numero){

    if(IsQueueFull(fila))
        return 0;
    
    if(!(IsQueueEmpty(fila))){
        if(fila->fim == fila->capacidade - 1)
            fila->fim = 0;
        else 
            fila->fim++;
    }

    fila->array[fila->fim] = numero;
    fila->tamanho++;
    return 1;
}

int Dequeue(Fila *fila){

    if(IsQueueEmpty(fila))
        return '\0';
    
    int numero = fila->array[fila->inicio];
    fila->tamanho--;
    if(fila->inicio != fila->fim){
        if(fila->inicio == fila->capacidade - 1)
            fila->inicio = 0;
        else 
            fila->inicio++;
    }
    return numero;
}

int IsQueueEmpty(Fila *fila){
    return fila->tamanho == 0;
}

int IsQueueFull(Fila *fila){
    return fila->tamanho == fila->capacidade;
}

void DestroyQueue(Fila *fila){
    free (fila->array);
    free (fila);
}