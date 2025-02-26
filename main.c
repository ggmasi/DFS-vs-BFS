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

void DesenharLabirinto(int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], Posicao atual, int destino[2]);
// void DesenharLabirinto(int labirinto[TAM][TAM], int celulasDesenhadas);
int DFS(int x, int y, int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], int destino[2], stack *pilha);
int BFS(int x, int y, int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM],int visitadoBFS[TAM][TAM], int destino[2], Fila *fila);

int main(){
   
    
    
    int labirinto[TAM][TAM] = 
    {{0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0 ,0},
    {0, 0, 0, 0, 0}};
    
    int visitadoDFS[TAM][TAM] = { 0 };
    
    int visitadoBFS[TAM][TAM] = { 0 };
    
    int destino[2] = {1, 1};
    
    stack pilha;
    initialize(&pilha, TAM*TAM);
    
    Fila *fila = CriarFila(TAM*TAM);
    
    Posicao atual = {0};

    
    

    

    InitWindow(((TAM+6)*CELL_SIZE)*2, (TAM+6)*CELL_SIZE, "DFS vs BFS");
    
    SetTargetFPS(15);
    
    
    int chamouDFS = 0;
    int chamouBFS = 0;
    int chamouDesenho = 0;
    int resultadoDFS = -1;
    while (!WindowShouldClose()){
            while(resultadoDFS == -1){
                // if(!chamouDesenho){
            //     DesenharLabirinto(labirinto, visitadoDFS, visitadoBFS, atual);
            //     chamouDesenho = 1;
            // }
            WaitTime(1);
            
            // if(!chamouDFS){
            //     if(!DFS(0, 0, labirinto, visitadoDFS, destino, &pilha)){
            //         printf("Caminho nao encontrado\n");
            //     }
            //     chamouDFS = 1;
            // }
            resultadoDFS = DFS(0, 0, labirinto, visitadoDFS, destino, &pilha);
            if(!resultadoDFS)  printf("Caminho nao encontrado");
            DesenharLabirinto(labirinto, visitadoDFS, visitadoBFS, (Posicao){0}, destino);


            if(!chamouBFS){
                if(!BFS(0, 0, labirinto, visitadoBFS, destino, fila)){
                    printf("Caminho nao encontrado\n");
                }
                chamouBFS = 1;
            }
            // DesenharLabirinto(labirinto, pixelsDesenhados);
        }   
    }
    // EndDrawing();
    CloseWindow();

    
    destroy(&pilha);
    Destroy(fila);
}

int DFS(int x, int y, int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], int destino[2], stack *pilha) {
    // if (labirinto[x][y] == 1) return 0;

    // int pos = x * TAM + y;
    // push(pilha, pos);
    // visitado[x][y] = 1;


    // int dx[] = {-1, 0, 1, 0};
    // int dy[] = {0, -1, 0, 1};
    // // BeginDrawing();
    // while (!isEmpty(pilha)) {
    //     pos = pop(pilha);
    //     Posicao atual;
    //     atual.x = pos / TAM;
    //     atual.y = pos % TAM;

    //     if (atual.x == destino[0] && atual.y == destino[1]) {
    //         printf("\nDFS\n");
    //         for (int i = 0; i < TAM; i++) {
    //             for (int j = 0; j < TAM; j++) {
    //                 printf("%d ", visitado[i][j]);
    //             }
    //             printf("\n");
    //         }
    //         return 1;
    //     }
        
    //     for (int i = 3; i >= 0; i--) {
    //         int nx = atual.x + dx[i];
    //         int ny = atual.y + dy[i];

    //         if (nx >= 0 && nx < TAM && ny >= 0 && ny < TAM && labirinto[nx][ny] == 0 && !visitado[nx][ny]) {
                
    //             int new_pos = nx * TAM + ny;
    //             push(pilha, new_pos);
    //             visitado[nx][ny] = 1;
    //             DesenharLabirinto(labirinto, visitado, visitado, atual);
    //             // int pixelsDesenhadosDFS = 0;
    //             // int contadorPixelsDFS = 0;
    //             // if(contadorPixelsDFS++ >= VELOCIDADE && pixelsDesenhadosDFS < TAM*TAM){
    //             //     pixelsDesenhadosDFS++;
    //             //     contadorPixelsDFS = 0;
                   
    //             // }


    //             // int xPixel = (nx + 1)*CELL_SIZE;
    //             // int yPixel = (ny + 1)*CELL_SIZE;
    //             // Color corDFS = MAGENTA;
                
    //             // //Desenha o bloco principal
    //             // DrawRectangle(xPixel+(2*CELL_SIZE), yPixel+(2*CELL_SIZE), CELL_SIZE, CELL_SIZE, MAGENTA);
                
    //             // //Desenha a borda da célula
    //             // DrawRectangleLines(xPixel+(2*CELL_SIZE), yPixel+(2*CELL_SIZE), CELL_SIZE, CELL_SIZE, BLACK);
    //         }
    //     }
    // }
    // // EndDrawing();
    
    // return 0;

    static bool iniciado = false;
    if(!iniciado){
        if(labirinto[x][y] == 1){
            return 0;
        }
        int pos = 0;
        push(pilha, pos);
        visitado[x][y] = 1;
        iniciado = true;
    }

    if(isEmpty(pilha)) return 0;

    while (!isEmpty(pilha)) {
        int pos = pop(pilha);
        int x = pos / TAM;
        int y = pos % TAM;
        WaitTime(0.25);
        DesenharLabirinto(labirinto, visitado, visitado, (Posicao){.x = x, .y = y}, destino);

        if (x == destino[0] && y == destino[1])
            return 1;  // destino encontrado

        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, -1, 0, 1};

        for (int i = 3; i >= 0; i--) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < TAM && ny >= 0 && ny < TAM && labirinto[nx][ny] == 0 && !visitado[nx][ny]) {
                i = -1;
                push(pilha, nx * TAM + ny);
                visitado[nx][ny] = 1;
                
            }
        }
    }
    return 0; 
}

int BFS(int x, int y, int labirinto[5][5], int visitadoBFS[TAM][TAM], int destino[2], Fila *fila){

    if(labirinto[x][y] == 1){
        return 0;               // posicao inicial do labirinto, caso seja uma "parede" retorna 0
    }



    int pos = (x * TAM) + y;  // cada par (x,y) tem um "pos" unico, que pode ser decodificado posteriormente 

    
    Push(fila, pos);    // insera na fila a pos atual que será investigada

    
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



void DesenharLabirinto(int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], Posicao atual, int destino[2]){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangle((destino[0]+3)*CELL_SIZE, (destino[1]+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);

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

    // for (int i = 0; i < TAM; i++){
    //     for (int j = 0; j < TAM; j++)
    //     {
    //         int x = ((i/TAM)+1)*CELL_SIZE;
    //         int y = ((j%TAM)+1)*CELL_SIZE;
    //         Color corDFS = visitadoDFS[i][j] == 1 ? MAGENTA : BLANK;
    //         DrawRectangle(x+(2*CELL_SIZE), y+(2*CELL_SIZE), CELL_SIZE, CELL_SIZE, corDFS);
    //     }
        
    // }

    for (int i = 0; i < TAM; i++){
        for (int j = 0; j < TAM; j++){
            int x = (3+j)*CELL_SIZE;
            int y = (3+i)*CELL_SIZE;

            if(visitadoDFS[i][j] == 1){
                DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, MAGENTA);
                DrawRectangleLines(x, y, CELL_SIZE, CELL_SIZE, BLACK);
            }else{
                DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, BLANK);
                DrawRectangleLines(x, y, CELL_SIZE, CELL_SIZE, BLACK);
            }
        }
        
    }
    

    

    // Desenha células internas progressivamente
    // for(int idx = 0; idx < pixelsDesenhados; idx++) {
    //     int i = idx / TAM;  // Linha
    //     int j = idx % TAM;  // Coluna

    //     // Posição com offset para as bordas
    //     int x = (j + 1) * CELL_SIZE;
    //     int y = (i + 1) * CELL_SIZE;

    //     // Escolhe a cor baseado no valor do labirinto
    //     Color corDFS = visitadoDFS[i][j] == 1 ? MAGENTA : BLANK;
        
    //     // Desenha o bloco principal
    //     DrawRectangle(x+(2*CELL_SIZE), y+(2*CELL_SIZE), CELL_SIZE, CELL_SIZE, corDFS);
        
    //     //Desenha a borda da célula
    //     DrawRectangleLines(x+(2*CELL_SIZE), y+(2*CELL_SIZE), CELL_SIZE, CELL_SIZE, BLACK);
        
        
    //     Color corBFS = visitadoBFS[i][j] == 1 ? DARKPURPLE : BLANK;
        
    //     DrawRectangle((x+TAM)*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE, corBFS);
    // }


    EndDrawing();
    
}