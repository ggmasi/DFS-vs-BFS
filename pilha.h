#ifndef PILHA_H
#define PILHA_H

typedef struct {
    int *data;
    int top;
    int limit;
} stack;

void initialize( stack *s, int limit );
int isEmpty( stack *s );
int isFull( stack *s );
void push( stack *s, int value );
int pop( stack *s );
int peek( stack *s );
void destroy( stack *s);
#endif