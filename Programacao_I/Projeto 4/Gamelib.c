#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  /* Biblioteca de fontes */
#include <allegro5/allegro_image.h> /* Biblioteca de imagens */
#include <allegro5/allegro_ttf.h>   /* Biblioteca de fontes TrueType */

#include "Global.h"
#include "Gamelib.h"

/* Cria a struct de uma fruta do jogo, de tipo (aparencia) aleatoria de acordo com o nivel atual do jogador e a salva no grid */
GRID_FRUIT *GGL_create_fruit(GRID_STRUCT *grid) {
    GRID_FRUIT *newFruit = (GRID_FRUIT *) malloc(sizeof(GRID_FRUIT));
    newFruit->type = rand() % grid->fruit_types;
    newFruit->special = 0;
    newFruit->x = 0;
    newFruit->y = 0;
    return newFruit;
}

/* Cria o grid principal, com valores predefinidos, e o preenche com frutas aleatorias */
GRID_STRUCT *GGL_create_grid() {
    GRID_STRUCT *grid = (GRID_STRUCT *) malloc(sizeof(GRID_STRUCT));
    grid->NxN = 8;
    grid->Width = 487;
    grid->Height = 88;
    grid->imgX = 48.5;
    grid->imgY = 46.5;
    grid->fruit_types = 5;
    grid->Score = 0;
    grid->Level = 1;
    /* Inicializa o grid com a matriz de frutas aleatorias */
    grid->fruit = (GRID_FRUIT **) malloc(grid->NxN * sizeof(GRID_FRUIT *));
    for (int i = 0; i < grid->NxN; i++) {
        grid->fruit[i] = (GRID_FRUIT *) malloc(grid->NxN * sizeof(GRID_FRUIT));
        for (int j = 0; j < grid->NxN; j++) {
            grid->fruit[i][j] = *GGL_create_fruit(grid);
            grid->fruit[i][j].x = i;
            grid->fruit[i][j].y = j;
        }
    }
    return grid;
}

/* Libera a memoria utilizada pelo grid e pelas frutas */
void GGL_destroy_grid(GRID_STRUCT *grid) {
    for (int i = 0; i < grid->NxN; i++) {
        free(grid->fruit[i]);
    }
    free(grid->fruit);
    free(grid);
}

/* Troca a posicao de duas frutas do grid */
void GGL_swap_fruit(GRID_STRUCT *grid, GRID_FRUIT *fruit1, GRID_FRUIT *fruit2) {
    int F1_x = fruit1->x;
    int F1_y = fruit1->y;
    int F2_x = fruit2->x;
    int F2_y = fruit2->y;
    /* Troca as frutas de lugar no grid */
    GRID_FRUIT temp = grid->fruit[F1_x][F1_y];
    grid->fruit[F1_x][F1_y] = grid->fruit[F2_x][F2_y];
    grid->fruit[F2_x][F2_y] = temp;
    /* Atualiza os valores de x e y das frutas */
    grid->fruit[F1_x][F1_y].x = F1_x;
    grid->fruit[F1_x][F1_y].y = F1_y;
    grid->fruit[F2_x][F2_y].x = F2_x;
    grid->fruit[F2_x][F2_y].y = F2_y;
    return;
}

/* Checa se uma fruta faz parte de uma combinacao de 3 ou mais do mesmo tipo */
int GGL_check_match(GRID_STRUCT *grid, GRID_FRUIT *fruit) {
    /* Se a fruta nao existe, retorna 0 */
    if (fruit == NULL || fruit->type == -1) return 0;
    /* Criamos um vetor de frutas que sera retornado, e adicionamos a fruta central nele */
    int match_size_x = 1;
    GRID_FRUIT *match_x = (GRID_FRUIT *) malloc(match_size_x * sizeof(GRID_FRUIT));
    match_x[0] = *fruit;
    /* Checamos as frutas a esquerda da fruta central */
    for (int i = fruit->x - 1; i >= 0; i--) {
        if (grid->fruit[i][fruit->y].type == fruit->type) {
            match_size_x++;
            match_x = (GRID_FRUIT *) realloc(match_x, match_size_x * sizeof(GRID_FRUIT));
            match_x[match_size_x - 1] = grid->fruit[i][fruit->y];
        } else break;
    }
    /* Checamos as frutas a direita da fruta central */
    for (int i = fruit->x + 1; i < grid->NxN; i++) {
        if (grid->fruit[i][fruit->y].type == fruit->type) {
            match_size_x++;
            match_x = (GRID_FRUIT *) realloc(match_x, match_size_x * sizeof(GRID_FRUIT));
            match_x[match_size_x - 1] = grid->fruit[i][fruit->y];
        } else break;
    }
    /* Checamos as frutas acima e abaixo da fruta central */
    int match_size_y = 1;
    GRID_FRUIT *match_y = (GRID_FRUIT *) malloc(match_size_y * sizeof(GRID_FRUIT));
    match_y[0] = *fruit;
    /* Checamos as frutas acima da fruta central */
    for (int i = fruit->y - 1; i >= 0; i--) {
        if (grid->fruit[fruit->x][i].type == fruit->type) {
            match_size_y++;
            match_y = (GRID_FRUIT *) realloc(match_y, match_size_y * sizeof(GRID_FRUIT));
            match_y[match_size_y - 1] = grid->fruit[fruit->x][i];
        } else break;
    }
    /* Checamos as frutas abaixo da fruta central */
    for (int i = fruit->y + 1; i < grid->NxN; i++) {
        if (grid->fruit[fruit->x][i].type == fruit->type) {
            match_size_y++;
            match_y = (GRID_FRUIT *) realloc(match_y, match_size_y * sizeof(GRID_FRUIT));
            match_y[match_size_y - 1] = grid->fruit[fruit->x][i];
        } else break;
    }
    /* Agora checamos as combinacoes obtidas */
    int special_fruit = -1;
    /* Se a combinacao de frutas for de 3 ou mais, retorna o vetor de frutas */
    if (match_size_x >= 3 && match_size_y >= 3) {
        /* Retorna o vetor com todos as combinacoes da coluna + linha */
        GRID_FRUIT *match = (GRID_FRUIT *) malloc((match_size_x + match_size_y -1) * sizeof(GRID_FRUIT));
        for (int i = 0; i < match_size_x; i++) {
            match[i] = match_x[i];
        }
        /* Comecando em 1 para nao repetir a fruta central */
        for (int i = 1; i < match_size_y; i++) {
            match[match_size_x + i-1] = match_y[i];
        }
        special_fruit = 2;
        GGL_clear_match(grid, match, match_size_x + match_size_y-1, special_fruit);
        free(match);
        free(match_x);
        free(match_y);
        return 1;
    }
    else if (match_size_x >= 3) {
        if (match_size_x == 4)          /* Se a combinacao for de 4 frutas na horizontal */
            special_fruit = 1;
        else if (match_size_x >= 5)     /* Se a combinacao for de 5 frutas na horizontal */
            special_fruit = 3;
        else {                          /* Se a combinacao for de 3 frutas na horizontal */
            special_fruit = 0;
        }
        GGL_clear_match(grid, match_x, match_size_x, special_fruit);
        free(match_x);
        free(match_y);
        return 1;
    }
    else if (match_size_y >= 3) {
        if (match_size_y == 4)          /* Se a combinacao for de 4 frutas na vertical */
            special_fruit = 1;
        else if (match_size_y >= 5)     /* Se a combinacao for de 5 frutas na vertical */
            special_fruit = 3;
        else {                          /* Se a combinacao for de 3 frutas na vertical */
            special_fruit = 0;
        }
        GGL_clear_match(grid, match_y, match_size_y, special_fruit);
        free(match_x);
        free(match_y);
        return 1;
    }
    /* Se nao houver combinacoes, retorna 0 */
    return 0;
}

/* Sinaliza as frutas que devem ser removidas de acordo com o tipo especial da fruta enviada */
void GGL_clear_match(GRID_STRUCT *grid, GRID_FRUIT *match, int match_size, int special_fruit) {
    int ini;
    /* Realiza a "limpeza" de acordo com o tipo especial de cada fruta combinada */
    if (special_fruit > 0) {
        ini = 1;
        grid->fruit[match[0].x][match[0].y].special = special_fruit;
        if (special_fruit == 3) {
            grid->fruit[match[0].x][match[0].y].type = 7;
        }
    } else 
        ini = 0;
    for (int i = ini; i < match_size; i++) {
        GGL_clear_more(grid, &match[i]);
    }
}

void GGL_clear_more(GRID_STRUCT *grid, GRID_FRUIT *fruit){
    switch (grid->fruit[fruit->x][fruit->y].special) {
        case 0: /* Fruta normal */
            grid->fruit[fruit->x][fruit->y].type = -1;
            grid->Score += 10 * grid->Level;
        break;
        case 1: /* Fruta especial 1: Remove todas as frutas em um raio de 1 espaco */
            fruit->special = 0;
            for (int j = fruit->x - 1; j <= fruit->x + 1; j++) {
                for (int k = fruit->y - 1; k <= fruit->y + 1; k++) {
                    if (j >= 0 && j < grid->NxN && k >= 0 && k < grid->NxN) {
                        GGL_clear_more(grid, &grid->fruit[j][k]);
                    }
                }
            }
        break;
        case 2: /* Fruta especial 2: Remove todas as frutas na mesma linha e coluna */
            fruit->special = 0;
            for (int j = 0; j < grid->NxN; j++) {
                GGL_clear_more(grid, &grid->fruit[fruit->x][j]);
                GGL_clear_more(grid, &grid->fruit[j][fruit->y]);
            }
        break;
        case 3: /* Fruta especial 3: Remove todas as frutas que compartilham o mesmo tipo */
            fruit->special = 0;
            for (int j = 0; j < grid->NxN; j++) {
                for (int k = 0; k < grid->NxN; k++) {
                    if (grid->fruit[j][k].type == fruit->type) {
                        GGL_clear_more(grid, &grid->fruit[j][k]);
                    }
                }
            }
        break;
    }
}

/* Remove as frutas que fazem parte da combinacao, e move todas as outras para baixo */ 
void GGL_rearrange_fruits(GRID_STRUCT *grid) {
    /* Detecta todas as frutas com tipo == -1 e as move para o topo usando GGL_swap_fruit */
    for (int i = 0; i < grid->NxN; i++) {
        for (int j = 0; j < grid->NxN; j++) {
            if (grid->fruit[i][j].type == -1) {
                /* Move todas as frutas acima da fruta vazia para baixo, a nao ser que nao haja frutas acima */
                for (int k = j; k > 0; k--) {
                    GGL_swap_fruit(grid, &grid->fruit[i][k], &grid->fruit[i][k-1]);
                }
                /* Gera uma nova fruta no topo */
                grid->fruit[i][0].type = rand() % grid->fruit_types;
                grid->fruit[i][0].special = 0;
                grid->fruit[i][0].x = i;
                grid->fruit[i][0].y = 0;
            }
        }
    }
}

/* Checa todo o grid para ver se ha combinacoes formadas */
int GGL_check_grid(GRID_STRUCT *grid, int flag) {
    int score = grid->Score;
    /* Checa todas as posicoes com GGL_check_match */
    for (int i = 0; i < grid->NxN; i++) {
        for (int j = 0; j < grid->NxN; j++) {
            GGL_check_match(grid, &grid->fruit[i][j]);
        }
    }
    /* Se houver combinacoes formadas, retorna 1 */
    if (grid->Score > score) {
        if (flag == 1) {
            grid->Score = score;
        }
        return 1;
    }
    return 0; 
}

/* Checa a pontuação do jogador e atualiza o level */
int GGL_check_score(GRID_STRUCT *grid) {
    /* Cada nivel tem a meta 3x maior que o anterior */
    if (grid->Score >= grid->Level * grid->Level * 1000) {
        grid->Level++;
        if (grid->Level == 3)
            grid->fruit_types = 6;
        else if (grid->Level == 5)
            grid->fruit_types = 7;
        /* Embaralha todo o grid, mantendo os tipos */
        for (int i = 0; i < grid->NxN; i++) {
            for (int j = 0; j < grid->NxN; j++) {
                int x = rand() % grid->NxN;
                int y = rand() % grid->NxN;
                GGL_swap_fruit(grid, &grid->fruit[i][j], &grid->fruit[x][y]);
            }
        }
        return 1;
    }
    return 0;
}