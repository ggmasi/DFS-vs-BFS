#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "fila.h"

#define TAM 5

typedef struct Posicao{
    int x;
    int y;

}Posicao;


int DFS(int x, int y, int labirinto[TAM][TAM], int visitado[TAM][TAM], int destino[2], stack *pilha);
int BFS(int x, int y, int labirinto[5][5], int visitadoBFS[TAM][TAM], int destino[2], Fila *fila);

int main(){
   int labirinto[TAM][TAM] = 
   {{0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0},
    {1, 1, 1, 1 ,0},
    {0, 0, 0, 0, 0}};;

    int visitadoDFS[TAM][TAM] = { 0 };
    
    int visitadoBFS[TAM][TAM] = { 0 };

    int destino[2] = {TAM-1, TAM-1};
    
    stack pilha;
    initialize(&pilha, TAM*TAM);

    Fila *fila = CriarFila(TAM*TAM);
    
    if(!DFS(0, 0, labirinto, visitadoDFS, destino, &pilha)){
        printf("Caminho nao encontrado\n");
    }


    if(!BFS(0, 0, labirinto, visitadoBFS, destino, fila)){
        printf("Caminho nao encontrado\n");
    }

   


}
//CS2 OU R6?
int DFS(int x, int y, int labirinto[TAM][TAM], int visitado[TAM][TAM], int destino[2], stack *pilha) {
    if (labirinto[x][y] == 1) return 0;

    int pos = x * TAM + y;
    push(pilha, pos);
    visitado[x][y] = 1;


    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};

    while (!isEmpty(pilha)) {
        pos = pop(pilha);
        Posicao atual;
        atual.x = pos / TAM;
        atual.y = pos % TAM;

        if (atual.x == destino[0] && atual.y == destino[1]) {
            printf("\nDFS\n");
            for (int i = 0; i < TAM; i++) {
                for (int j = 0; j < TAM; j++) {
                    printf("%d ", visitado[i][j]);
                }
                printf("\n");
            }
            return 1;
        }

        for (int i = 3; i >= 0; i--) {
            int nx = atual.x + dx[i];
            int ny = atual.y + dy[i];

            if (nx >= 0 && nx < TAM && ny >= 0 && ny < TAM && labirinto[nx][ny] == 0 && !visitado[nx][ny]) {
                
                int new_pos = nx * TAM + ny;
                push(pilha, new_pos);
                visitado[nx][ny] = 1;
                
            }
        }
    }

    return 0;
}


int BFS(int x, int y, int labirinto[5][5], int visitadoBFS[TAM][TAM], int destino[2], Fila *fila){

    if(labirinto[x][y] == 1){
        return 0;
    }

    

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
            printf("\nBFS\n");
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
            int ny = atual.y + dy[i];

            int pos_fake;
            if(nx >= 0 && ny >= 0 && nx < TAM && ny < TAM && labirinto[nx][ny] == 0 && !visitadoBFS[nx][ny]){
                pos_fake = (nx * TAM) + ny;
                Push(fila, pos_fake);
                visitadoBFS[nx][ny] = 1;
            }
              

        }


    }

    
    return 0;


}