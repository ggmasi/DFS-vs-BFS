#include <stdlib.h>
#include "fila.h"

Queue *InitializeQueue(int capacidade){

    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->array = (int*)malloc(capacidade*sizeof(int));

    queue->inicio = 0;
    queue->fim = 0;
    queue->tamanho = 0;
    queue->capacidade = capacidade;

    return queue;
}

int Enqueue(Queue *queue, int numero){

    if(IsQueueFull(queue))
        return 0;
    
    if(!(IsQueueEmpty(queue))){
        if(queue->fim == queue->capacidade - 1)
            queue->fim = 0;
        else 
            queue->fim++;
    }

    queue->array[queue->fim] = numero;
    queue->tamanho++;
    return 1;
}

int Dequeue(Queue *queue){

    if(IsQueueEmpty(queue))
        return '\0';
    
    int numero = queue->array[queue->inicio];
    queue->tamanho--;
    if(queue->inicio != queue->fim){
        if(queue->inicio == queue->capacidade - 1)
            queue->inicio = 0;
        else 
            queue->inicio++;
    }
    return numero;
}

int IsQueueEmpty(Queue *queue){
    return queue->tamanho == 0;
}

int IsQueueFull(Queue *queue){
    return queue->tamanho == queue->capacidade;
}

void DestroyQueue(Queue *queue){
    free (queue->array);
    free (queue);
}