#ifndef FILA_H
#define FILA_H
typedef struct {

    int *array;
    int inicio;
    int fim;
    int tamanho;
    int capacidade;

} Fila;

Fila *CriarFila(int capacidade);
int Push(Fila *fila, int numero);
int Pop(Fila *fila, int *numero);
int Empty (Fila *fila);
int Full (Fila *fila);
void LiberarFila(Fila *fila);

#endif