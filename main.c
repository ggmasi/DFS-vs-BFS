#include <stdio.h>
#include "pilha.h"
#include"fila.h"

#define TAM 5

typedef struct Posicao{
    int x;
    int y;

}Posicao;




int DFS(int x, int y, int labirinto[5][5], int visitado[5][5], int solucao[5][5], int destino[2]);

int main(){
   int labirinto[TAM][TAM] = 
   {{0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0},
    {1, 1, 1, 1 ,0},
    {0, 0, 0, 0, 0}};

    int visitadoDFS[TAM][TAM] = { 0 };
    int solucaoDFS[TAM][TAM] = { 0 };
    int visitadoBFS[TAM][TAM] = { 0 };
    int solucaoBFS[TAM][TAM] = { 0 };

    int destino[2] = {4, 4};

    Fila* fila;

    fila = CriarFila(TAM * TAM);
    
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




int BFS(int x, int y, int labirinto[5][5], int visitadoBFS[TAM][TAM], int destino[2], Fila *fila){

    

    

    int pos = (x * TAM) + y;

    

    Push(fila, pos);

    
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};


    while(!Empty(fila)){

        pos = Pop(fila);
        Posicao atual;

        atual.x = pos / TAM;
        atual.y = pos % TAM;

        if( atual.x == destino[0] && atual.y == destino[1]){
            for(int i = 0; i < TAM; i++){
                for(int j = 0; j < TAM; j++){
                    printf("%d ", visitadoBFS[i][j]);
                }
                printf("\n");
            }
            return 1;
        }

        for(int i = 0; i < 4; i++){
            int nx = atual.x + dx[i];
            int ny = atual.x + dy[i];

            int pos_fake;
            if(nx >= 0 && ny >= 0 && nx < TAM && ny < TAM && labirinto[nx][ny] == 0 && !visitadoBFS[nx][ny]){
                pos_fake = (nx * TAM) + ny;
                Push(fila, pos_fake);
                visitadoBFS[nx][ny] = 1;
            }
              

        }


    }

    return -1;


}