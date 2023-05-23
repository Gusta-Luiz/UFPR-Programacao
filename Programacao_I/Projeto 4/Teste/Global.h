#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  /* Biblioteca de fontes */
#include <allegro5/allegro_image.h> /* Biblioteca de imagens */
#include <allegro5/allegro_ttf.h>   /* Biblioteca de fontes TrueType */

typedef struct config_main_t GAME_STRUCT;
typedef struct config_gui_t GAME_UI;
typedef struct config_animated_t GAME_ANIMATED;

/* Struct contendo os dados para a criacao da janela principal, timer e lista de eventos do jogo */
struct config_main_t {
    ALLEGRO_EVENT_QUEUE *Event;  /* Lista de eventos */
    ALLEGRO_DISPLAY *Display;    /* janela principal */
    ALLEGRO_TIMER *Timer;        /* Timer para controle de FPS */
    int Width, Height;           /* Largura e altura da janela */
    int FPS;                     /* Quantidade de frames por segundo */
};

/* Struct que contem os arquivos e dados usados em alguma interface grafica do jogo */
struct config_gui_t {
    ALLEGRO_BITMAP *Background;  /* Imagem estatica de fundo do menu */
    ALLEGRO_BITMAP *Image1;      /* Espacos para imagens ou sprites */
    ALLEGRO_BITMAP *Image2;
    ALLEGRO_BITMAP *Image3;
    ALLEGRO_FONT   *Font1;       /* Fonte principal utilizada */
    ALLEGRO_FONT   *Font2;       /* Fonte secundaria */
};

/* Cria ou destroi o corpo principal do jogo, contendo a janela principal, o timer e a lista de eventos */
GAME_STRUCT *GL_create_body(int width, int height, int fps, char *icon);
void GL_destroy_body(GAME_STRUCT *body);

/* Cria ou destroi a interface grafica do jogo */
GAME_UI *GL_create_ui(char *background, char *image1, char *image2, char *image3, char *font1, char *font2);
void GL_destroy_ui(GAME_UI *interface);

/* Cria a struct com os dados enviados, para objetos que serao animados no jogo */
GAME_ANIMATED *GL_create_animated(int width, int height, int speed);

/* Realiza a animacao de transicao entre telas, do source para o destination */
void GL_transition(GAME_STRUCT *main_body, GAME_UI *Source_ui, GAME_UI *Destination_ui, ALLEGRO_BITMAP *img_clouds);