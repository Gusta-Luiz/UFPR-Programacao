#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  /* Biblioteca de fontes */
#include <allegro5/allegro_image.h> /* Biblioteca de imagens */
#include <allegro5/allegro_ttf.h>   /* Biblioteca de fontes TrueType */

typedef struct config_fruit_t GRID_FRUIT;
typedef struct config_grid_t GRID_STRUCT;

/* Struct responsavel pelas frutas do jogo, contendo suas informacoes */
struct config_fruit_t {
    int type;               /* Tipo da fruta, ou cor */
    int special;            /* Fruta e ou nao especial */
    int x,y;                /* Posicao da fruta no grid */
};

/* Struct do grid principal, onde as frutas serao colocadas */
struct config_grid_t {
    int NxN;                 /* Quantidade de frutas em cada linha e coluna */
    int Width,Height;        /* Largura e Altura do inicio do grid */
    float imgX,imgY;         /* Lagura e Altura + espacamento da imagem de cada fruta */
    GRID_FRUIT **fruit;      /* Frutas do grid */
    int fruit_types;         /* Quantidade de tipos diferentes de frutas */
    int Score;               /* Pontuacao do jogador */
    int Level;               /* Level do jogador, utilizado tambem como multiplicador */
};

/* Cria uma fruta de tipo aleatorio */
GRID_FRUIT *GGL_create_fruit(GRID_STRUCT *grid);
/* Cria o grid 8x8 que armazena todas as frutas */
GRID_STRUCT *GGL_create_grid();
/* Libera a memoria utilizada pelo grid e pelas frutas */
void GGL_destroy_grid(GRID_STRUCT *grid);
/* Troca a posicao de duas frutas do grid */
void GGL_swap_fruit(GRID_STRUCT *grid, GRID_FRUIT *fruit1, GRID_FRUIT *fruit2);
/* Checa se uma fruta faz parte de uma combinacao de 3 ou mais do mesmo tipo
 * Se sim, retorna um vetor com todas as frutas que compoem a combinacao */
int GGL_check_match(GRID_STRUCT *grid, GRID_FRUIT *fruit);

/* Detecta o tipo de conjunto formado e faz as mudancas necessarias */
void GGL_match_type(GRID_STRUCT *grid, GRID_FRUIT *match, int type);
/* Sinaliza as frutas que devem ser removidas de acordo com o tipo especial da fruta enviada */
void GGL_clear_match(GRID_STRUCT *grid, GRID_FRUIT *match, int match_size, int special_fruit);
void GGL_clear_more(GRID_STRUCT *grid, GRID_FRUIT *fruit);
/* Remove as frutas que fazem parte da combinacao, e move todas as outras para baixo */ 
void GGL_rearrange_fruits(GRID_STRUCT *grid);
/* Checa todo o grid para ver se ha combinacoes formadas */
int GGL_check_grid(GRID_STRUCT *grid, int flag);
/* Checa a pontuação do jogador e atualiza o level */
int GGL_check_score(GRID_STRUCT *grid);
 