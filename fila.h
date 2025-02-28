#ifndef FILA_H
#define FILA_H
typedef struct {

    int *array;
    int inicio;
    int fim;
    int tamanho;
    int capacidade;

} Fila;

Fila *InitializeQueue(int capacidade);
int Enqueue(Fila *fila, int numero);
int Dequeue(Fila *fila);
int IsQueueEmpty(Fila *fila);
int IsQueueFull(Fila *fila);
void DestroyQueue(Fila *fila);

#endif