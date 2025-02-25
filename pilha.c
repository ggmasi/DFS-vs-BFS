#include <stdlib.h>
#include "pilha.h"

void initialize( stack *s, int limit ){
    s->data = (int*)malloc(limit *sizeof(int));
    s->top = -1;
    s->limit = limit;
}

int isEmpty( stack *s ){
    return s->top == -1;
}
int isFull( stack *s ){
    return s->top == s->limit-1;
}
void push( stack *s, int value ){
    if(isFull(s)) return;
    s->top++;
    s->data[s->top] = value;
}
int pop( stack *s ){
    if(isEmpty(s)) return '\0';
    s->top--;
    return s->data[s->top+1];
}
int peek( stack *s ){
    if(isEmpty(s)) return '\0';
    return s->data[s->top];
}
void destroy( stack *s){
    free(s->data);
    s->data = NULL;
    s->top = -1;
    s->limit = 0;
}