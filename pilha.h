#ifndef PILHA_H
#define PILHA_H

typedef struct {
    int *data;
    int top;
    int limit;
} Stack;

Stack *InitializeStack( int limit );
int IsStackEmpty( Stack *s );
int IsStackFull( Stack *s );
void Push( Stack *s, int value );
int Pop( Stack *s );
int Peek( Stack *s );
void DestroyStack( Stack *s);
#endif