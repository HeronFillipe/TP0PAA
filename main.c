#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LARGURA 80
#define ALTURA 20

char quadro[ALTURA][LARGURA];

//Função para inicializar o quadro
void iniciaQuadro() {
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            if (i == 0 || i == ALTURA - 1) {
                quadro[i][j] = '-';
            } else if (j == 0 || j == LARGURA - 1) {
                quadro[i][j] = '|';
            } else {
                quadro[i][j] = ' ';
            }
        }
    }
}

int posicaoValida(int x, int y, int tipoFigura) {
    //(1x1)
    if (tipoFigura == 1) {  
        return quadro[x][y] == ' ';
    } 
    //(3x3)
    else if (tipoFigura == 2 || tipoFigura == 3) { 
        return x > 0 && x < ALTURA - 1 && y > 0 && y < LARGURA - 1 &&
               quadro[x][y] == ' ' && quadro[x-1][y] == ' ' && quadro[x+1][y] == ' ' &&
               quadro[x][y-1] == ' ' && quadro[x][y+1] == ' ';
    } 
    //(7x6)
    else if (tipoFigura == 5) {
        return x > 0 && x < ALTURA - 1 && y > 1 && y < LARGURA - 6 &&
               quadro[x][y] == ' ' &&
               quadro[x + 1][y + 1] == ' ' &&
               quadro[x + 1][y + 2] == ' ' &&
               quadro[x + 2][y + 2] == ' ' &&
               quadro[x + 2][y + 3] == ' ' &&
               quadro[x + 3][y + 2] == ' ' &&
               quadro[x + 3][y + 3] == ' ' &&
               quadro[x + 3][y + 4] == ' ' &&
               quadro[x + 3][y + 5] == ' ' &&
               quadro[x + 4][y + 4] == ' ' &&
               quadro[x + 4][y + 5] == ' ' &&
               quadro[x + 5][y + 5] == ' ' &&
               quadro[x + 5][y + 6] == ' ' &&
               quadro[x + 6][y + 7] == ' ';
    }
    return 0;
}

//Funções para desenhar as figuras
void desenhaAsterisco(int x, int y) {
    if (posicaoValida(x, y, 1)) {
        quadro[x][y] = '*';
    }
}

void desenhaSoma(int x, int y) {
    if (posicaoValida(x, y, 2)) {
        quadro[x][y] = '*';
        quadro[x + 1][y] = '*';
        quadro[x - 1][y] = '*';
        quadro[x][y + 1] = '*';
        quadro[x][y - 1] = '*';
    }
}

void desenhaX(int x, int y) {
    if (posicaoValida(x, y, 3)) {
        quadro[x][y] = '*';
        quadro[x + 1][y + 1] = '*';
        quadro[x - 1][y - 1] = '*';
        quadro[x + 1][y - 1] = '*';
        quadro[x - 1][y + 1] = '*';
    }
}

void desenhaRaio(int x, int y) {
    if (posicaoValida(x, y, 5)) {
        quadro[x][y] = '*';           
        quadro[x + 1][y+1] = '*';
        quadro[x + 1][y+2] = '*';    
        quadro[x + 2][y+2] = '*';   
        quadro[x + 2][y+3] = '*';      
        quadro[x + 3][y+2] = '*';  
        quadro[x + 3][y+3] = '*';       
        quadro[x + 3][y+4] = '*';   
        quadro[x + 3][y+5] = '*';   
        quadro[x + 4][y+4] = '*'; 
        quadro[x + 4][y+5] = '*';
        quadro[x + 5][y+5] = '*';
        quadro[x + 5][y+6] = '*';   
        quadro[x + 6][y+7] = '*'; 
    }
}


//Função para imprimir o quadro
void imprimeQuadro() {
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            putchar(quadro[i][j]);
        }
        putchar('\n');
    }
}

int main() {
    int tipo, quantidade;
    char opcao;
    srand(time(NULL));

    do {
        //menu
        printf("PROGRAMA GERADOR DE OBRA DE ARTE:\n");
        printf("=================================\n");
        printf("Escolha o tipo de figura basica a ser usada para criar a obra:\n");
        printf("[1] - Asterisco simples.\n");
        printf("[2] - Simbolo de soma com asteriscos.\n");
        printf("[3] - Letra X com asteriscos.\n");
        printf("[4] - Figuras aleatorias.\n");
        printf("[5] - Desenho de Raio\n");
        printf("Digite o tipo de figura basica desejada: ");
        scanf("%d", &tipo);

        printf("Digite a quantidade de figuras (menor ou igual a zero para aleatorio): ");
        scanf("%d", &quantidade);

        if (quantidade <= 0) {
            quantidade = rand() % 100 + 1;
            printf("\nValor fora do limite!\n Novo valor atribuido é %i\n", quantidade);
        } else if (quantidade > 100) {
            quantidade = 100;
            printf("\nValor fora do limite!\n Novo valor atribuido é %i\n", quantidade);
        }

        iniciaQuadro();

        for (int i = 0; i < quantidade; i++) {
            int x, y;
            int figuraAleatoria = tipo;

            //tipo for 4, escolhe aleatoriamente entre 1, 2, e 3
            if (tipo == 4) {
                figuraAleatoria = rand() % 3 + 1;
            }

            //Gera novas coordenadas até encontrar uma posição válida
            do {
                x = rand() % (ALTURA - 2) + 1;
                y = rand() % (LARGURA - 2) + 1;
            } while (!posicaoValida(x, y, figuraAleatoria));

            //Desenha a figura
            if (figuraAleatoria == 1) {
                desenhaAsterisco(x, y);
            } else if (figuraAleatoria == 2) {
                desenhaSoma(x, y);
            } else if (figuraAleatoria == 3) {
                desenhaX(x, y);
            } else if (figuraAleatoria == 5) {
                desenhaRaio(x, y);
            }
        }

        imprimeQuadro();

        printf("Deseja gerar um novo quadro com os mesmos valores? (s/n): ");
        scanf(" %c", &opcao);

    } while (opcao == 's' || opcao == 'S');

    return 0;
}
