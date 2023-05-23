#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  /* Biblioteca de fontes */
#include <allegro5/allegro_image.h> /* Biblioteca de imagens */
#include <allegro5/allegro_ttf.h>   /* Biblioteca de fontes TrueType */

/* Desenha a interface do jogo na tela */
void GG_draw_menu(GAME_STRUCT *main_body, GAME_UI *junimo_ui, GRID_STRUCT *grid);
/* Desenha o grid na sua devida posicao, e suas frutas uma por uma, especiais ou nao */
void GG_draw_grid(GRID_STRUCT *grid, GAME_UI *junimo_ui);
/* Funcao que reconhece se o mouse clicou em alguma fruta do grid */
GRID_FRUIT *GG_check_click(GRID_STRUCT *grid, int mouseX, int mouseY);
/* Desenha a silhueta para indicar qual fruta foi selecionada, de acordo com onde o mouse é pressionado na tela */
void GG_draw_mouse_selection(GRID_STRUCT *grid, GAME_UI *junimo_ui, GRID_FRUIT *fruit);
/* Troca duas frutas de posicao, e desenha a transicao entre elas */
void GG_draw_swap(GRID_STRUCT *grid, GAME_UI *junimo_ui, GRID_FRUIT *fruit1, GRID_FRUIT *fruit2);
/* Desenha na tela a maioria das informacoes necessarias */
void GG_draw (GRID_STRUCT *grid, GAME_UI *junimo_ui, GAME_STRUCT *main_struct, GRID_FRUIT *selection1, GRID_FRUIT *selection2, float fps);
/* Funcao principal, onde é executado o toda a gameplay do jogo */
void GG_game_loop (GAME_STRUCT *main_struct, GAME_UI* Help_ui);
