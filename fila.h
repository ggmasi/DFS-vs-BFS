#ifndef FILA_H
#define FILA_H
typedef struct {

    int *array;
    int inicio;
    int fim;
    int tamanho;
    int capacidade;

} Queue;

Queue *InitializeQueue(int capacidade);
int Enqueue(Queue *queue, int numero);
int Dequeue(Queue *queue);
int IsQueueEmpty(Queue *queue);
int IsQueueFull(Queue *queue);
void DestroyQueue(Queue *queue);

#endif