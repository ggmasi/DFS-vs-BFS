#include <stdlib.h>
#include "fila.h"

Fila *CriarFila(int capacidade){

    Fila *fila = (Fila*)malloc(sizeof(Fila));
    fila->array = (int*)malloc(capacidade*sizeof(int));

    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
    fila->capacidade = capacidade;

    return fila;
}

int Push(Fila *fila, int numero){

    if(Full(fila))
        return 0;
    
    if(!(Empty(fila))){
        if(fila->fim == fila->capacidade - 1)
            fila->fim = 0;
        else 
            fila->fim++;
    }

    fila->array[fila->fim] = numero;
    fila->tamanho++;
    return 1;
}

int Pop(Fila *fila, int *numero){

    if(Empty(fila))
        return 0;
    
    *numero = fila->array[fila->inicio];
    fila->tamanho--;
    if(fila->inicio != fila->fim){
        if(fila->inicio == fila->capacidade - 1)
            fila->inicio = 0;
        else 
            fila->inicio++;
    }
    return 1;
}

int Empty (Fila *fila){
    return fila->tamanho == 0;
}

int Full (Fila *fila){
    return fila->tamanho == fila->capacidade;
}

void LiberarFila(Fila *fila){
    free (fila->array);
    free (fila);
}