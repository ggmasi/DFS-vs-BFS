#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "pilha.h"
#include "fila.h"


#define VELOCIDADE 3 //Quadros por pixel

typedef struct Posicao{
    int x;      
    int y;          

}Posicao;

void DesenharLabirinto( int TAM, int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], Posicao atual, int destino[2], int desenhaDFS, int desenhaBFS, int CELL_SIZE);
void DesenharLabirintoFinal(int TAM, int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], int destino[2], int CELL_SIZE);
int DFS(int x, int y, int TAM, int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], int destino[2], Stack *pilha, int CELL_SIZE);
int BFS(int x, int y, int TAM, int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], int destino[2], Queue *fila, int CELL_SIZE);
// funcoes de resolução (DFS E BFS) e a função de desenhar o labirinto


int main(){
   
    int TAM, inicioX, inicioY, destino[2]; 
    printf("Insira o tamanho do seu labirinto quadrado: \n");
    scanf("%d", &TAM); // inicialização das variáveis
    int labirinto[TAM][TAM]; // matriz que define o labirinto
    int visitadoDFS[TAM][TAM];  // matriz das coordenadas visitas pelo dfs
    int visitadoBFS[TAM][TAM];  // matriz das coordenadas visitas pelo bfs
    printf("Insira o labirinto desejado para realizar as buscas (0 para possíveis caminhos, 1 para paredes): \n");
    for (int i = 0; i < TAM; i++){
        for (int j = 0; j < TAM; j++)
        {
            scanf("%d", &labirinto[i][j]);
            visitadoBFS[i][j] = 0;
            visitadoDFS[i][j] = 0;
        }
    }
    printf("Insira o local (comprimento e altura) desejado para se iniciar as buscas (0 a %d): \n", TAM-1);
    scanf("%d %d", &inicioX, &inicioY);
    printf("Insira o local (comprimento e altura) desejado para se terminar as buscas (0 a %d): \n", TAM-1);
    scanf("%d %d", &destino[0], &destino[1]);
    int CELL_SIZE = 300/TAM; // o tamanho de cada "pixel" é equivalente a 300 dividido pelo comprimento/largura do labirinto
    
    

    
    

    
    
    Stack *pilha = InitializeStack(TAM*TAM);   // inicializa a pilha com tamanho 25
    
    Queue *fila = InitializeQueue(TAM*TAM);    // inicializa a fila com tamanho 25
    
    Posicao atual = {0};    // posicao inicial eh a (0,0)

    
    

    

    InitWindow(((TAM+6)*CELL_SIZE)*2, (TAM+6)*CELL_SIZE, "DFS vs BFS"); // inicializacao da janela grafica
    //altura: (TAM+6)*CELL_SIZE
    // largura: ((TAM+6)*CELL_SIZE)*2 — a largura da janela (ajusta para mostrar os dois algoritmos lado a lado)
    // "DFS vs BFS": Título da janela

    SetTargetFPS(60);   // define a quantos frames per second vai rodar a animação
    
  
    int resultadoDFS = -1; 
    while (!WindowShouldClose()){ // mantem a janela rodando enquanto o usuario nao quer fechar.
        if(resultadoDFS == -1){ // so sera executado no primeiro loop
            WaitTime(1);    // espera 1 segundo para executar
            resultadoDFS = DFS(inicioX, inicioY, TAM, labirinto, visitadoDFS, visitadoBFS, destino, pilha, CELL_SIZE); // caso return == 0 ,nao ha caminho
            if(!resultadoDFS)  printf("Caminho nao encontrado"); // caso falhe o caminho dfs, printa que nao achou
            if(!WindowShouldClose()){
                if(!BFS(inicioX, inicioY, TAM, labirinto, visitadoDFS, visitadoBFS, destino, fila, CELL_SIZE)) printf("Caminho nao encontrado\n"); // mesma logica do anterior      
            }
        }else{
            DesenharLabirintoFinal(TAM, labirinto, visitadoDFS, visitadoBFS, destino, CELL_SIZE); // desenha o labirinto final
            
        }      
    }   
    CloseWindow(); //funcao fecha de fato a janela

    
    DestroyStack(pilha);    // destroi a pilha
    DestroyQueue(fila);      //destroi a fila
}

int DFS(int x, int y, int TAM, int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], int destino[2], Stack *pilha, int CELL_SIZE) {

    if(labirinto[x][y] == 1) // se comecar numa parede, falhou
        return 0;
    
    int pos = (x*TAM) + y;  // posicao eh codifificada
    Push(pilha, pos);   // empilha a posicao
    visitadoDFS[x][y] = 1;  //  primeiro vertice eh visitado

        
    while (!IsStackEmpty(pilha) && !WindowShouldClose()) {   // enquanto a pilha nao estiver vazia
        int pos = Peek(pilha);   // recebe o topo da pilha como posicao a ser analisada 
        int cx = pos / TAM;  // decodifica o x
        int cy = pos % TAM;  // decodifica o y
        WaitTime(0.3); // tempo de espera para agir
        DesenharLabirinto(TAM, labirinto, visitadoDFS, visitadoBFS, (Posicao){.x = cx, .y = cy}, destino, 1, 0, CELL_SIZE);   // desenha toda vez que comeca a buscar um novo vertice

        if (cx == destino[0] && cy == destino[1]) return 1;  // destino encontrado

        int vizinhoEncontrado = 0; // variavel utilizada para definir se há vizinho disponivel
        int dx[] = {0, 1, 0, -1}; // anda para direita, anda para baixo, anda para esquerda, anda para cima 
        int dy[] = {1, 0, -1, 0}; 

        for (int i = 0; i < 4; i++) { // inicia as 4 movimentacoes
            int nx = cx + dx[i]; // x observado recebe seu x mais seu movimento
            int ny = cy + dy[i]; // y observado recebe seu y mais seu movimento 
            if (nx >= 0 && nx < TAM && ny >= 0 && ny < TAM && labirinto[nx][ny] == 0 && !visitadoDFS[nx][ny]) { // primeiro verifica se nao esta olhando para fora do labirinto, apos isso, verifica se a posicao olhada eh uma area disponivel, por fim, verifica se a posicao ja nao foi visitada
                Push(pilha, nx * TAM + ny); // empilha a recem descoberta posicao
                visitadoDFS[nx][ny] = 1;    // marca a posicao descoberta como visitada   
                vizinhoEncontrado = 1; //altera a variavel pois há vizinho disponivel
                break;
            }
        }

        //caso nao haja vizinho disponivel, retorna para o "pixel" anterior
        if(!vizinhoEncontrado){
            Pop(pilha);
        }

    }
    return 0;  // caso saia do while sem achar, nao a caminho.
}

int BFS(int x, int y, int TAM, int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], int destino[2], Queue *fila, int CELL_SIZE){

    if(labirinto[x][y] == 1){ // se comecar numa parede, falhou
        return 0;
    }
    int pos = (x*TAM) + y; // posicao eh codifificada
    Enqueue(fila, pos);     // enfileira a posicao
    visitadoBFS[x][y] = 1;   //  primeiro vertice eh visitado
       
    
    int dx[] = {-1, 1, 0, 0}; //anda para cima, anda para baixo, anda para esquerda e anda para a direita 
    int dy[] = {0, 0, -1, 1}; 


    while(!IsQueueEmpty(fila) && !WindowShouldClose()){ // enquanto a fila nao esta vazia
        
        int pos = Dequeue(fila);    /*desenfileira a primeira posicao da fila*/ 
        Posicao atual;  // declara a struct posicao

        atual.x = pos / TAM;  // decodifica o x 
        atual.y = pos % TAM;  // decodifica o y

        WaitTime(0.3); // tempo de espera para agir
        DesenharLabirinto(TAM, labirinto, visitadoDFS, visitadoBFS, atual, destino, 0, 1, CELL_SIZE); // desenha o labirinto atual

        if (atual.x == destino[0] && atual.y == destino[1])
            return 1;  // destino encontrado


        for(int i = 0; i < 4; i++){ // observa as 4 posicoes 
            int nx = atual.x + dx[i]; // olha para cima, baixo, esquerda, e direita
            int ny = atual.y + dy[i];   

            int pos_fake;   // posicao observada 
            if(nx >= 0 && ny >= 0 && nx < TAM && ny < TAM && labirinto[nx][ny] == 0 && !visitadoBFS[nx][ny]){ // caso a posicao observada preencha os requisitos, ela eh uma pos valida
                pos_fake = (nx * TAM) + ny; // codifica o x e o y para a pos observaa
                Enqueue(fila, pos_fake);   // empilha a pos observada
                visitadoBFS[nx][ny] = 1; // marca o vertice x y como visita
            }
        }
    }

    return 0; // caso saia do while e nao ache, nao ha caminho
}



void DesenharLabirinto(int TAM, int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], Posicao atual, int destino[2], int desenhaDFS, int desenhaBFS, int CELL_SIZE){
    // inicia o processo de desenho na tela
    BeginDrawing();
    
    // limpa a tela com a cor branca (constante RAYWHITE da Raylib)
    ClearBackground(RAYWHITE);
    
    //if(atual.x != destino[0] || atual.y != destino[1]){
        // desenha um quadrado vermelho no destino (para o painel DFS)
        // a posição é ajustada somando 3 às coordenadas de destino e multiplicando pelo tamanho da célula
        DrawRectangle((destino[1]+3)*CELL_SIZE, (destino[0]+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);

        // desenha um quadrado vermelho no destino (para o painel BFS)
        // aqui a posição horizontal é deslocada em (destino+9+TAM) células para separar os dois painéis
        DrawRectangle((destino[1]+9+TAM)*CELL_SIZE, (destino[0]+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);
    //}
    
    
    

    // loop para desenhar as células do labirinto e suas bordas extras
    // o loop vai de -1 até TAM (inclusive) para criar uma "moldura" em volta do labirinto
    for (int i = -1; i < TAM+1; i++){
        for (int j = -1; j < TAM+1; j++){
            // se a célula é uma parede (valor 1 na matriz do labirinto)
            if(i >= 0 && i < TAM && j >=0 && j < TAM){
                if(labirinto[i][j] == 1){
                    // desenha a parede no painel DFS com cor cinza (GRAY)
                    DrawRectangle((j+3) * CELL_SIZE, (i+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, GRAY);
                    // desenha a parede no painel BFS; nota o deslocamento horizontal para separar os painéis
                    DrawRectangle((j+TAM+9) * CELL_SIZE, (i+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, GRAY);
                }
            }
            // se a célula faz parte da moldura externa (bordas do labirinto)
            if( i == -1 || i == TAM || j == -1|| j == TAM){
                // desenha a borda preta no painel DFS
                DrawRectangle((j+3) * CELL_SIZE, (i+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
                // desenha a borda preta no painel BFS
                DrawRectangle((j+TAM+9) * CELL_SIZE, (i+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
            }
        }
    }

    // desenha as linhas da grade sobre todo o espaço dos dois painéis
    // o loop percorre todas as linhas necessárias considerando o tamanho total (TAM+6)*2
    for (int i = 0; i <= (TAM+6)*2; i++){
        // linha horizontal
        DrawLine(0, i*CELL_SIZE, ((TAM+6)*CELL_SIZE)*2, i*CELL_SIZE, BLACK);
        // linha vertical
        DrawLine(i * CELL_SIZE, 0, i*CELL_SIZE, ((TAM+6)*CELL_SIZE)*2, BLACK);
    }

    int xBFS;
    int y;
    // desenha as células internas do labirinto para cada painel (DFS e BFS)
    for (int i = 0; i < TAM; i++){
        for (int j = 0; j < TAM; j++){
            // calcula a posição X para o painel DFS (deslocado 3 células à direita)
            int xDFS = (3+j)*CELL_SIZE;
            // calcula a posição Y comum para ambos os painéis (deslocado 3 células para baixo)
            int y = (3+i)*CELL_SIZE;
            // calcula a posição X para o painel BFS (deslocado para a direita: 9+TAM células)
            int xBFS = (9+TAM+j)*CELL_SIZE;
            
            // variável calculada, mas que não é utilizada nas próximas linhas
            int posDestino = (destino[0]*TAM)+destino[1];

            // se a célula atual é a posição "atual" (passada como parâmetro)
            if(i == atual.x && j == atual.y ){
                // se o DFS visitou essa célula
                if(visitadoDFS[i][j] == 1){
                    // se o flag de desenho do DFS está ativado, pinta a célula de verde
                    if(desenhaDFS == 1){
                        DrawRectangle(xDFS, y, CELL_SIZE, CELL_SIZE, GREEN);
                        // desenha a borda da célula
                        DrawRectangleLines(xDFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                    }else{
                        // se não, pinta a célula de magenta
                        DrawRectangle(xDFS, y, CELL_SIZE, CELL_SIZE, MAGENTA);
                        DrawRectangleLines(xDFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                    }
                }
                // se o BFS visitou essa célula
                if(visitadoBFS[i][j] == 1){
                    // se o flag de desenho do BFS está ativado, pinta a célula de verde
                    if(desenhaBFS == 1){
                        DrawRectangle(xBFS, y, CELL_SIZE, CELL_SIZE, GREEN);
                        DrawRectangleLines(xBFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                    }else{
                        // caso contrário, pinta a célula de roxo escuro (SKYBLUE)
                        DrawRectangle(xBFS, y, CELL_SIZE, CELL_SIZE, SKYBLUE);
                        DrawRectangleLines(xBFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                    }
                }
            }
            // caso a célula atual não seja o destino (ou seja, não é a célula de chegada)
            else if(i != destino[0] || j != destino[1]){
                // para o painel DFS:
                // se a célula foi visitada, pinta de magenta
                if(visitadoDFS[i][j] == 1){
                    DrawRectangle(xDFS, y, CELL_SIZE, CELL_SIZE, MAGENTA);
                    DrawRectangleLines(xDFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                }else{
                    // se não foi visitada, pinta de branco (BLANK) com borda preta
                    DrawRectangle(xDFS, y, CELL_SIZE, CELL_SIZE, BLANK);
                    DrawRectangleLines(xDFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                }
    
                // para o painel BFS:
                // se a célula foi visitada, pinta de roxo escuro
                if(visitadoBFS[i][j] == 1){
                    DrawRectangle(xBFS, y, CELL_SIZE, CELL_SIZE, SKYBLUE);
                    DrawRectangleLines(xBFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                }else{
                    // se não foi visitada, pinta de branco; nota o pequeno ajuste no deslocamento horizontal (pode ser para manter alinhamento)
                    DrawRectangle(xBFS+TAM+9, y, CELL_SIZE, CELL_SIZE, BLANK);
                    DrawRectangleLines(xBFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                }
            }else{
                if(visitadoDFS[i][j] == 1){
                    DrawRectangle(xDFS, y, CELL_SIZE, CELL_SIZE, GREEN);
                    DrawRectangleLines(xDFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                }

                if(visitadoBFS[i][j] == 1){
                    DrawRectangle(xBFS, y, CELL_SIZE, CELL_SIZE, GREEN);
                    DrawRectangleLines(xBFS, y, CELL_SIZE, CELL_SIZE, BLACK);
                }
            }
        }
    }
    
    // redesenha os quadrados de destino para garantir que fiquem visíveis por cima de outros elementos
    // DrawRectangle((destino[1]+3)*CELL_SIZE, (destino[0]+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);
    // DrawRectangle((destino[1]+9+TAM)*CELL_SIZE, (destino[0]+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);

    // Desenha os rótulos "DFS" e "BFS" acima dos labirintos
    int fontSize = CELL_SIZE;
    const char *dfsText = "DFS";
    const char *bfsText = "BFS";

    // Calcula posição para "DFS"
    int dfsTextWidth = MeasureText(dfsText, fontSize);
    int dfsX = 3 * CELL_SIZE + (TAM * CELL_SIZE) / 2 - dfsTextWidth / 2;
    int dfsY = 1 * CELL_SIZE;
    DrawText(dfsText, dfsX, dfsY, fontSize, MAGENTA);

    // Calcula posição para "BFS"
    int bfsTextWidth = MeasureText(bfsText, fontSize);
    int bfsX = (TAM + 9) * CELL_SIZE + (TAM * CELL_SIZE) / 2 - bfsTextWidth / 2;
    int bfsY = 1 * CELL_SIZE;
    DrawText(bfsText, bfsX, bfsY, fontSize, SKYBLUE);


    EndDrawing();
}



void DesenharLabirintoFinal(int TAM, int labirinto[TAM][TAM], int visitadoDFS[TAM][TAM], int visitadoBFS[TAM][TAM], int destino[2], int CELL_SIZE){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    // Desenha os quadrados de destino para ambos os painéis
    DrawRectangle((destino[1]+3)*CELL_SIZE, (destino[0]+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);
    DrawRectangle((destino[1]+9+TAM)*CELL_SIZE, (destino[0]+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);
    
    // Desenha paredes e bordas (moldura) sem acessar índices inválidos
    for (int i = -1; i < TAM+1; i++){
        for (int j = -1; j < TAM+1; j++){
            if(i >= 0 && i < TAM && j >= 0 && j < TAM){
                if(labirinto[i][j] == 1){
                    // Painel DFS
                    DrawRectangle((j+3) * CELL_SIZE, (i+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, GRAY);
                    // Painel BFS
                    DrawRectangle((j+TAM+9) * CELL_SIZE, (i+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, GRAY);
                }
            }
            // Desenha as bordas da moldura
            if(i == -1 || i == TAM || j == -1 || j == TAM){
                DrawRectangle((j+3) * CELL_SIZE, (i+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
                DrawRectangle((j+TAM+9) * CELL_SIZE, (i+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
            }
        }
    }
    
    // Desenha a grade sobre ambos os painéis
    for (int i = 0; i <= (TAM+6)*2; i++){
        DrawLine(0, i*CELL_SIZE, ((TAM+6)*CELL_SIZE)*2, i*CELL_SIZE, BLACK);
        DrawLine(i * CELL_SIZE, 0, i*CELL_SIZE, ((TAM+6)*CELL_SIZE)*2, BLACK);
    }
    
    int xDFS;
    int y;
    int xBFS;
    // Desenha as células internas para cada painel
    for (int i = 0; i < TAM; i++){
        for (int j = 0; j < TAM; j++){
            xDFS = (3+j)*CELL_SIZE;       // Posição X para o painel DFS
            y = (3+i)*CELL_SIZE;           // Posição Y comum
            xBFS = (9+TAM+j)*CELL_SIZE;      // Posição X para o painel BFS
            
            // Painel DFS: se visitado, pinta de magenta; senão, branco
            if(visitadoDFS[i][j] == 1)
                DrawRectangle(xDFS, y, CELL_SIZE, CELL_SIZE, MAGENTA);
            else
                DrawRectangle(xDFS, y, CELL_SIZE, CELL_SIZE, BLANK);
            DrawRectangleLines(xDFS, y, CELL_SIZE, CELL_SIZE, BLACK);
            
            // Painel BFS: se visitado, pinta de roxo escuro; senão, branco
            if(visitadoBFS[i][j] == 1)
                DrawRectangle(xBFS, y, CELL_SIZE, CELL_SIZE, SKYBLUE);
            else
                DrawRectangle(xBFS, y, CELL_SIZE, CELL_SIZE, BLANK);
            DrawRectangleLines(xBFS, y, CELL_SIZE, CELL_SIZE, BLACK);
        }
    }
    
   
    //caso o caminho seja encontrado, a casa destino fica verde
    if(visitadoDFS[destino[0]][destino[1]] == 1){
        DrawRectangle((destino[1]+3)*CELL_SIZE, (destino[0]+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN);
        
    }
    if(visitadoBFS[destino[0]][destino[1]] == 1){
        DrawRectangle((destino[1]+9+TAM)*CELL_SIZE, (destino[0]+3)*CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN);
    }
    
    //desenha as linhas
    for (int i = 0; i <= (TAM+6)*2; i++){
        DrawLine(0, i*CELL_SIZE, ((TAM+6)*CELL_SIZE)*2, i*CELL_SIZE, BLACK);
        DrawLine(i * CELL_SIZE, 0, i*CELL_SIZE, ((TAM+6)*CELL_SIZE)*2, BLACK);
    }

    // Desenha os rótulos "DFS" e "BFS" acima dos labirintos
    int fontSize = CELL_SIZE;
    const char *dfsText = "DFS";
    const char *bfsText = "BFS";
    const char *NEText  = "Caminho Não Encontrado";

    // Calcula posição para "DFS"
    int dfsTextWidth = MeasureText(dfsText, fontSize);
    int dfsX = 3 * CELL_SIZE + (TAM * CELL_SIZE) / 2 - dfsTextWidth / 2;
    int dfsY = 1 * CELL_SIZE;
    DrawText(dfsText, dfsX, dfsY, fontSize, MAGENTA);

    // Calcula posição para "BFS"
    int bfsTextWidth = MeasureText(bfsText, fontSize);
    int bfsX = (TAM + 9) * CELL_SIZE + (TAM * CELL_SIZE) / 2 - bfsTextWidth / 2;
    int bfsY = 1 * CELL_SIZE;
    DrawText(bfsText, bfsX, bfsY, fontSize, SKYBLUE);

    if(visitadoDFS[destino[0]][destino[1]] != 1){
        int NETextWidth = MeasureText(NEText, fontSize); 
        int NEX = NETextWidth/2;
        int NEY = (TAM + 5) * CELL_SIZE;
        DrawText(NEText, NEX, NEY, fontSize, BLACK);
    }


    EndDrawing();
}

