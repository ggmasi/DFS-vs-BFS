#include <stdio.h>
#include "pilha.h"


typedef struct Posicao{
    int x;
    int y;
    struct Posicao *pai;
}Posicao;


int DFS(int x, int y, int labirinto[5][5], int visitado[5][5], int solucao[5][5], int destino[2]);

int main(){
   int labirinto[5][5] = 
   {{0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0},
    {1, 1, 1, 1 ,0},
    {0, 0, 0, 0, 0}};

    int visitadoDFS[5][5] = { 0 };
    int solucaoDFS[5][5] = { 0 };

    int destino[2] = {4, 4};
    
    // stack pilha;
    // initialize(&pilha, 5*5);

    // Posicao *inicio = malloc(sizeof(Posicao));
    // inicio->x = 0;
    // inicio->y = 0;
    // inicio->pai = NULL;
    // int inicioPos = 0;

    // visitadoDFS[0][0] = 1;
    // push(&pilha, inicioPos);

    if(DFS(0, 0, labirinto, visitadoDFS, solucaoDFS, destino)){
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                printf("%d ", solucaoDFS[i][j]);
            }
            printf("\n");
        }
        
    }else{printf("Nao encontrado");}
    



}

int DFS(int x, int y, int labirinto[5][5], int visitado[5][5], int solucao[5][5], int destino[2]){
    if(x < 0 || x >= 5 || y < 0 || y >= 5) return 0;
    if(labirinto[x][y] == 1 || visitado[x][y] == 1) return 0;

    visitado[x][y] = 1;
    solucao[x][y] = 1;

    if(x == destino[0] && y == destino[1]){
        return 1;
    }

    if(DFS(x, y + 1, labirinto, visitado, solucao, destino)) return 1;
    if(DFS(x + 1, y, labirinto, visitado, solucao, destino)) return 1;
    if(DFS(x, y - 1, labirinto, visitado, solucao, destino)) return 1;
    if(DFS(x - 1, y, labirinto, visitado, solucao, destino)) return 1;


}