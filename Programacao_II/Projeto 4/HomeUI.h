#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  /* Biblioteca de fontes */
#include <allegro5/allegro_image.h> /* Biblioteca de imagens */
#include <allegro5/allegro_ttf.h>   /* Biblioteca de fontes TrueType */

typedef struct config_home_birds_t GAME_HOME_BIRDS;

struct config_home_birds_t {
    int id;                 /* tipo do passaro */
    int x, y;               /* posicao do passaro */
    int speed;              /* velocidade do passaro */
    int direction;          /* direcao do passaro */
    float frame;            /* frame atual do passaro */
};

/* Desenha o menu principal, e todas as suas opcoes na janela selecionada */
void HM_draw_menu(GAME_STRUCT *main_struct, GAME_UI *Home_ui);
/* Muda a sprite do menu principal de acordo com a opcao em que o mouse se encontra */
void HM_draw_selection(GAME_STRUCT *main_struct, GAME_UI *Home_ui, int option);
/* Checa se o mouse esta sobre uma opcao do menu, e a retorna */
int HM_check_mouse(GAME_STRUCT *main_struct, int mouse_x, int mouse_y);
/* Cria um vetor de <count> passaros que voarao pelo menu principal */
GAME_HOME_BIRDS *HM_create_birds(GAME_STRUCT *main_struct, int count);
/* Verifica e realiza a animacao de fundo de todos os passaros no vetor */
void HM_draw_birds(GAME_STRUCT *window, ALLEGRO_BITMAP *img_birds, GAME_HOME_BIRDS birds_vet[], int count);
/* Libera a memoria alocada para o vetor de passaros */
void HM_destroy_birds(GAME_HOME_BIRDS *birds_vet);
/* Loop principal do menu inicial */
void HM_home_loop(GAME_STRUCT *main_struct, GAME_UI *Help_ui);
