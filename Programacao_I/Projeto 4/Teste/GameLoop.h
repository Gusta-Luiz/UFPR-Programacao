#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  /* Biblioteca de fontes */
#include <allegro5/allegro_image.h> /* Biblioteca de imagens */
#include <allegro5/allegro_ttf.h>   /* Biblioteca de fontes TrueType */

typedef struct config_fruit_t GRID_FRUIT;
typedef struct config_grid_t GRID_CONFIG;

/* Struct responsavel pelas frutas do jogo, contendo suas informacoes */
struct config_fruit_t {
    int type;               /* Tipo da fruta, ou cor */
    int special;            /* Fruta e ou nao especial */
    int x,y;                /* Posicao X e Y da fruta no grid */ 
};

/* Struct do grid principal, onde as frutas serao colocadas */
struct config_grid_t {
    int NxN;                 /* Quantidade de frutas em cada linha e coluna */
    int Width,Height;        /* Largura e Altura do inicio do grid */
    float imgX,imgY;         /* Lagura e Altura + espacamento da imagem de cada fruta */
    GRID_FRUIT **fruit;      /* Frutas do grid */
    int fruit_types;         /* Quantidade de tipos de frutas */
    int Score;               /* Pontuacao do jogador */
    int Level;               /* Level do jogador, utilizado tambem como multiplicador */
};

/* Desenha a interface do menu de jogo, onde acontece o jogo em si */
void GG_draw_menu(GAME_STRUCT *main_body, GAME_UI *junimo_ui);

/* Cria a struct de uma fruta do jogo, de tipo (aparencia) aleatoria de acordo com o nivel atual do jogador e a salva no grid */
GRID_FRUIT *GG_create_fruit(GRID_CONFIG *grid);

/* Desenha o grid com suas frutas na tela */
void GG_draw_grid(GRID_CONFIG *grid, GAME_UI *junimo_ui);

/* Cria o grid principal, com valores predefinidos, e o preenche com frutas aleatorias */
GRID_CONFIG *GG_create_grid();

/* Libera a memoria utilizada pelo grid e pelas frutas */
void GG_destroy_grid(GRID_CONFIG *grid);

/* Funcao principal do jogo, onde o loop principal e executado */
int GG_game_loop(GAME_STRUCT *main_body, GAME_UI *junimo_ui);