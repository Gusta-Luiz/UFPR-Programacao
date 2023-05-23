#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  /* Biblioteca de fontes */
#include <allegro5/allegro_image.h> /* Biblioteca de imagens */
#include <allegro5/allegro_ttf.h>   /* Biblioteca de fontes TrueType */

typedef struct config_menu_bird_t MENU_BIRD;
typedef struct config_menu_bird_struct_t MENU_ALLBIRDS;

/* Estrutura que armazena informacoes de um unico passaro */
struct config_menu_bird_t {
    int X, Y;                     /* Posicao (X,Y) */
    int Direction;                /* Direcao em que voa */
    int Speed;                    /* Velocidade que voa */
    int type;                     /* Tipo de passaro */
};

/* Estrutura contendo o vetor de todos os passaros */
struct config_menu_birds_struct_t {
    ALLEGRO_BITMAP *img_birds;    /* Imagem dos passaros */
    MENU_BIRD *birds_list;        /* Lista de passaros */
    int bird_count;               /* Quantidade de passaros */
};

/* Desenha o menu principal e suas opcoes */
void MM_draw_menu(GAME_STRUCT *main_body, GAME_UI *Home_ui);
/* Checa se o mouse esta sobre uma opcao do menu */
int MM_check_mouse(GAME_STRUCT *main_body, int mouse_x, int mouse_y);
/* Atualiza os botoes de opcoes de acordo com o local onde o mouse se encontra */
void MM_draw_selection(GAME_STRUCT *main_body, GAME_UI *Home_ui, int option);
/* Animacao de fundo com um passaro em posicao aleatoria */
void MM_draw_bird(GAME_STRUCT *window, MENU_ALLBIRDS *birds);

/* Tela do menu principal, onde o jogador pode escolher entre opcoes ou sair do jogo */
void MM_MainMenu_loop(GAME_STRUCT *game_struct, GAME_UI *Main_ui );