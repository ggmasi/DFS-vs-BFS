#include <stdlib.h>
#include "pilha.h"

Stack *InitializeStack( int limit ){
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->data = (int*)malloc(limit *sizeof(int));
    s->top = -1;
    s->limit = limit;
}

int IsStackEmpty( Stack *s ){
    return s->top == -1;
}
int IsStackFull( Stack *s ){
    return s->top == s->limit-1;
}
void Push( Stack *s, int value ){
    if(IsStackFull(s)) return;
    s->data[++s->top] = value;
}
int Pop( Stack *s ){
    if(IsStackEmpty(s)) return -1;
    s->top--;
    return s->data[s->top+1];
}
int Peek( Stack *s ){
    if(IsStackEmpty(s)) return -1;
    return s->data[s->top];
}
void DestroyStack( Stack *s){
    free(s->data);
    s->data = NULL;
    s->top = -1;
    s->limit = 0;
}