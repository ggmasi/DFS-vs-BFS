#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

#define TAM 5

typedef struct Posicao{
    int x;
    int y;
    struct Posicao *pai;
}Posicao;


int DFS(int x, int y, int labirinto[TAM][TAM], int visitado[TAM][TAM], int destino[2], stack *pilha);

int main(){
   int labirinto[TAM][TAM] = 
   {{0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0},
    {1, 1, 1, 1 ,0},
    {0, 0, 0, 0, 0}};

    int visitadoDFS[TAM][TAM] = { 0 };
    int solucaoDFS[TAM][TAM] = { 0 };

    int destino[2] = {TAM-1, TAM-1};
    
    stack pilha;
    initialize(&pilha, TAM*TAM);

    Posicao *inicio = malloc(sizeof(Posicao));
    inicio->x = 0;
    inicio->y = 0;
    inicio->pai = NULL;
    int inicioPos = 0;

   
    

    if(DFS(0, 0, labirinto, visitadoDFS, destino, &pilha)){
        int temp;
        while(!isEmpty(&pilha)){
            temp = pop(&pilha);
            int tempX = temp/TAM;
            int tempY = temp%TAM;
            solucaoDFS[tempX][tempY] = 1;
        }
        for (int i = 0; i < TAM; i++){
            for (int j = 0; j < TAM; j++){
                printf("%d ", solucaoDFS[i][j]);
            }
            printf("\n");
        }
        
        
    }else{printf("Nao encontrado");}
    



}

int DFS(int x, int y, int labirinto[TAM][TAM], int visitado[TAM][TAM], int destino[2], stack *pilha){
    if(x < 0 || x >= TAM || y < 0 || y >= TAM) return 0;
    if(labirinto[x][y] == 1 || visitado[x][y] == 1) return 0;


    visitado[x][y] = 1;
    int pos = (x*TAM) + y;
    push(pilha, pos);
    if(x == destino[0] && y == destino[1]){
        return 1;
    }

    int direcoes[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    for (int i = 0; i < 4; i++){
        int novoX = x + direcoes[i][0];
        int novoY = y + direcoes[i][1];
        if(DFS(novoX, novoY, labirinto, visitado, destino, pilha)){
            return 1;
        }
    }
    pop(pilha);
    return 0;
}