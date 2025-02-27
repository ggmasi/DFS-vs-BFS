#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "pilha.h"
#include "fila.h"

#define TAM 5   // tamanho escolhido para o labirinto (5x5)
#define CELL_SIZE 60 // tamanho de cada "pixel" desenhado
#define VELOCIDADE 3 //Quadros por pixel

typedef struct Posicao{
    int x;      
    int y;          

}Posicao;

void DesenharLabirinto(int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], Posicao atual, int destino[2], int desenhaDFS, int desenhaBFS);
int DFS(int x, int y, int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], int destino[2], Stack *pilha);
int BFS(int x, int y, int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], int destino[2], Fila *fila);

int main(){
   
    
    
    int labirinto[TAM][TAM] = 
    {{0, 1, 0, 0, 0},
     {0, 1, 0, 0, 0},
     {0, 0, 0, 1, 0},
     {1, 1, 1, 1 ,0},
     {0, 0, 0, 0, 0}};
    
    int visitadoDFS[TAM][TAM] = { 0 };
    
    int visitadoBFS[TAM][TAM] = { 0 };
    
    int destino[2] = {TAM-1, TAM-1};
    
    Stack *pilha = InitializeStack(TAM*TAM);
    
    
    Fila *fila = InitializeQueue(TAM*TAM);
    
    Posicao atual = {0};

    
    

    

    InitWindow(((TAM+6)*CELL_SIZE)*2, (TAM+6)*CELL_SIZE, "DFS vs BFS");
    
    SetTargetFPS(15);
    
    



    int resultadoDFS = -1;
    while (!WindowShouldClose()){
        if(resultadoDFS == -1){
            WaitTime(1);

            resultadoDFS = DFS(0, 0, labirinto, visitadoDFS, visitadoBFS, destino, pilha);
            if(!resultadoDFS)  printf("Caminho nao encontrado");

            if(!BFS(0, 0, labirinto, visitadoDFS, visitadoBFS, destino, fila)) printf("Caminho nao encontrado\n");
             
        }   
    }
    CloseWindow();

    
    DestroyStack(pilha);
    DestroyQueue(fila);
}

int DFS(int x, int y, int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], int destino[2], Stack *pilha) {
    
    if(labirinto[x][y] == 1) return 0;

   
    int pos = (x*TAM) + y;
    Push(pilha, pos);
    visitadoDFS[x][y] = 1;
    

    while (!IsStackEmpty(pilha)) {
        int pos = Pop(pilha);
        int x = pos / TAM;
        int y = pos % TAM;
        WaitTime(0.25);
        DesenharLabirinto(labirinto, visitadoDFS, visitadoBFS, (Posicao){.x = x, .y = y}, destino, 1, 0);

        if (x == destino[0] && y == destino[1])
            return 1;  // destino encontrado

        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, -1, 0, 1};

        for (int i = 3; i >= 0; i--) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < TAM && ny >= 0 && ny < TAM && labirinto[nx][ny] == 0 && !visitadoDFS[nx][ny]) {
                i = -1;
                Push(pilha, nx * TAM + ny);
                visitadoDFS[nx][ny] = 1;
                
            }
        }
    }
    return 0; 
}

int BFS(int x, int y, int labirinto[5][5], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], int destino[2], Fila *fila){

    if(labirinto[x][y] == 1) return 0;
    
    int pos = (x*TAM) + y;
    Enqueue(fila, pos);
    visitadoBFS[x][y] = 1;
    
    
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};


    while(!IsQueueEmpty(fila)){
        
        int pos = Dequeue(fila);
        Posicao atual;

        atual.x = pos / TAM;
        atual.y = pos % TAM;

        WaitTime(0.25);
        DesenharLabirinto(labirinto, visitadoDFS, visitadoBFS, atual, destino, 0, 1);

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
                Enqueue(fila, pos_fake);
                visitadoBFS[nx][ny] = 1;
            }
              
            

        }


    }

    
    return 0;


}



void DesenharLabirinto(int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], Posicao atual, int destino[2], int desenhaDFS, int desenhaBFS){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangle((destino[0]+3)*CELL_SIZE, (destino[1]+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);
    DrawRectangle((destino[0]+9+TAM)*CELL_SIZE, (destino[1]+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);

    for (int i = -1; i < TAM+1; i++){
        for (int j = -1; j < TAM+1; j++){
            if(labirinto[i][j] == 1){
                DrawRectangle((j+3) * CELL_SIZE, (i+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, GRAY);
                DrawRectangle((j+TAM+9) * CELL_SIZE, (i+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, GRAY);
            }
            if( i == -1 || i == TAM || j == -1|| j == TAM){
                DrawRectangle((j+3) * CELL_SIZE, (i+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
                DrawRectangle((j+TAM+9) * CELL_SIZE, (i+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
            }
            
        }
        
    }

    for (int i = 0; i <= (TAM+6)*2; i++){
        DrawLine(0, i*CELL_SIZE, ((TAM+6)*CELL_SIZE)*2, i*CELL_SIZE, BLACK);
        DrawLine(i * CELL_SIZE, 0, i*CELL_SIZE, ((TAM+6)*CELL_SIZE)*2, BLACK);
    }

    for (int i = 0; i < TAM; i++){
        for (int j = 0; j < TAM; j++){
            int xDFS = (3+j)*CELL_SIZE;
            int y = (3+i)*CELL_SIZE;
            int xBFS = (9+TAM+j)*CELL_SIZE;
            
            int posDestino = (destino[0]*TAM)+destino[1];

            if(i == atual.x && j == atual.y ){
                if(visitadoDFS[i][j] == 1){
                    if(desenhaDFS == 1){
                        DrawRectangle(xDFS, y, CELL_SIZE, CELL_SIZE, GREEN);
                        DrawRectangleLines(xDFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                    }else{
                        DrawRectangle(xDFS, y, CELL_SIZE, CELL_SIZE, MAGENTA);
                        DrawRectangleLines(xDFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                    }
                    
                }
                if(visitadoBFS[i][j] == 1){
                    if(desenhaBFS == 1){
                        DrawRectangle(xBFS, y, CELL_SIZE, CELL_SIZE, GREEN);
                        DrawRectangleLines(xBFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                    }else{
                        DrawRectangle(xBFS, y, CELL_SIZE, CELL_SIZE, DARKPURPLE);
                        DrawRectangleLines(xBFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                    }
                }
                
            }else if(i != destino[0] || j != destino[1]){
                if(visitadoDFS[i][j] == 1){
                    DrawRectangle(xDFS, y, CELL_SIZE, CELL_SIZE, MAGENTA);
                    DrawRectangleLines(xDFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                }else{
                    DrawRectangle(xDFS, y, CELL_SIZE, CELL_SIZE, BLANK);
                    DrawRectangleLines(xDFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                }
    
                if(visitadoBFS[i][j] == 1){
                    DrawRectangle(xBFS, y, CELL_SIZE, CELL_SIZE, DARKPURPLE);
                    DrawRectangleLines(xBFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                }else{
                    DrawRectangle(xBFS+TAM+9, y, CELL_SIZE, CELL_SIZE, BLANK);
                    DrawRectangleLines(xBFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                }
            }
            
            
            
            
        }
        
    }
    
    DrawRectangle((destino[0]+3)*CELL_SIZE, (destino[1]+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);
    DrawRectangle((destino[0]+9+TAM)*CELL_SIZE, (destino[1]+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);

    EndDrawing();
    
}