#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  /* Biblioteca de fontes */
#include <allegro5/allegro_image.h> /* Biblioteca de imagens */
#include <allegro5/allegro_ttf.h>   /* Biblioteca de fontes TrueType */

#ifdef Main
    enum {MENU, GAME, LOAD, EXIT} state;
#else
    extern enum {MENU, GAME, LOAD, EXIT} state;
#endif

/*--------------- Imagens e Fontes usadas no jogo ---------------*/
/* Icone do jogo  */
#define img_Body_icon        "./Contents/Images/Icon.png"
/* Menu principal */ 
#define img_Home_background  "./Contents/Images/HomeBg.png"
#define img_Home_options     "./Contents/Images/HomeOptions.png"
/* Tela de jogo   */ 
#define img_Game_background  "./Contents/Images/GameBg.jpg"
#define img_Game_background2 "./Contents/Images/GameBg2.jpg"
#define img_Game_fruits      "./Contents/Images/Fruits.png"
#define img_Game_block       "./Contents/Images/BlockSelect.png"
#define img_Game_specials    "./Contents/Images/Specials.png"
#define img_Game_match       "./Contents/Images/MatchAnimation.png"
/* Tela de ajuda */
#define img_Help_background  "./Contents/Images/HelpBg.png"
/* Fontes */ 
#define font_Global_title    "./Contents/Fonts/Title.ttf"
#define font_Global_defalt   "./Contents/Fonts/Defalt.ttf"
/* Imagens que serao animadas */
#define img_Global_clouds    "./Contents/Images/Clouds.png"
#define img_Global_birds     "./Contents/Images/Birds.png"
#define img_Global_movie     "./Contents/Images/Movie.png"

typedef struct config_mainbody_t GAME_STRUCT;
typedef struct config_gui_t GAME_UI;
typedef struct config_gui_font_t GAME_UI_FONT;

/* Struct contendo os dados para a criacao da janela principal, timer e lista de eventos do jogo */
struct config_mainbody_t {
    ALLEGRO_EVENT_QUEUE *Event;  /* Lista de eventos */
    ALLEGRO_DISPLAY *Display;    /* janela principal */
    ALLEGRO_TIMER *Timer;        /* Timer para controle de FPS */
    int Width, Height;           /* Largura e altura da janela */
    int Frames;                  /* Quantidade de frames por segundo */
};

/* Struct que contem os arquivos e dados usados em alguma interface grafica do jogo */
struct config_gui_t {
    ALLEGRO_BITMAP *Background;  /* Imagem estatica de fundo do menu */
    ALLEGRO_BITMAP **Image;      /* Vetor com espacos para imagens ou sprites */
    GAME_UI_FONT *Font;          /* Espacos para fontes */
    int Image_count;             /* Quantidade de imagens no vetor */
    int Font_count;              /* Quantidade de fontes no vetor */
};

struct config_gui_font_t {
    ALLEGRO_FONT *Font;          /* Fonte */
    int Size;                    /* Tamanho da fonte */
};

/* Cria o (ou libera) corpo principal do jogo, contendo a janela principal, o timer e a lista de eventos
 * --O timer deve ser iniciado antes do loop principal  */
GAME_STRUCT *GL_create_body(int width, int height, int frames);
void GL_destroy_body(GAME_STRUCT *body);

/*------------------ Funcoes para a Interface Grafica ------------------*/

/* Cria uma interface do jogo, como o menu principal, menu de opcoes, etc... 
 * e carrega os dados necessarios */
GAME_UI *GL_create_ui(char *background);
void GL_destroy_ui(GAME_UI *interface);

/* Carrega uma imagem e seus dados em uma estrutura e a retorna
 * Manter Width e Height em 0 para imagens unicas */
void GL_load_image(GAME_UI *ui_dest, char *path);

/* Carrega uma fonte e seus dados em uma estrutura e a salva na interface */
void GL_load_font(GAME_UI *ui_dest, char *path, int size);
void GL_destroy_font(GAME_UI_FONT *font);

/* Realiza a animacao de transicao entre menus, utilizando uma sprite de nuvens 
 * Flag == 0: Realiza a transicao por completo
 * Flag == 1: realiza a primeira metade
 * Flag == 2: Realiza a segunda e ultima metade */
void GL_transition(GAME_STRUCT *main_struct, ALLEGRO_BITMAP *Source_bg, ALLEGRO_BITMAP *Destination_bg, int flag);

/* Desenha a tela de ajuda e seus componentes */
void GL_draw_help(GAME_STRUCT *main_struct, GAME_UI* Help_ui);

#endif 