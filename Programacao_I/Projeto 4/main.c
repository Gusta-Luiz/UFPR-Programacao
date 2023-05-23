#define Main

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  /* Biblioteca de fontes */
#include <allegro5/allegro_image.h> /* Biblioteca de imagens */
#include <allegro5/allegro_ttf.h>   /* Biblioteca de fontes TrueType */

#include "Global.h"                 /* Biblioteca de funcoes globais, iniciadas por GL_ */
#include "HomeUI.h"                 /* Biblioteca de funcoes do menu principal, iniciadas por HM_ */
#include "Gamelib.h"                /* Biblioteca de funcoes do jogo, iniciadas por GGL_ */  
#include "GameUI.h"                 /* Biblioteca de funcoes do jogo, iniciadas por GG_ */

/* Constantes globais */
#define FPS 60
#define WIDTH 960
#define HEIGHT 540

int main()  {
    /*--------------- Inicializacao do Programa ---------------*/
    srand(time(NULL));          /* Inicializa o gerador de numeros aleatorios */
    al_init();                  /* Inicializa a Allegro */
    al_init_font_addon();       /* Inicializa a biblioteca de fontes do allegro */
    al_init_image_addon();      /* Inicializa a biblioteca de imagens, para os assets do jogo */
    al_init_ttf_addon();        /* Inicializa a biblioteca ttf, de fontes TrueType */
    al_install_keyboard();      /* Adiciona o suporte ao teclado */
    al_install_mouse();         /* Adiciona o suporte ao mouse */

    /*--------------- Imagens e Fontes usadas no jogo ---------------*/
    GAME_STRUCT *main_struct = GL_create_body(WIDTH, HEIGHT, FPS);

    /*------------------------- Tela de ajuda ---------------------------*/
    GAME_UI *Help_ui = GL_create_ui(img_Help_background);
    GL_load_image(Help_ui, img_Help_background);
    GL_load_font(Help_ui, font_Global_title, 100);
    GL_load_font(Help_ui, font_Global_defalt, 30);
    GL_load_font(Help_ui, font_Global_defalt, 20);

    /*--------------- Loops principais do jogo ---------------*/
    state = MENU;
    for (;;) {
        switch(state)
        {
            case MENU: HM_home_loop(main_struct, Help_ui);
                break;
            case GAME: GG_game_loop(main_struct, Help_ui);
                break;
            case LOAD: GG_game_loop(main_struct, Help_ui);
                break;
            case EXIT: 
                break;
        }
        if (state == EXIT) break;
    }

    /*--------------- Libera a memoria alocada ---------------*/
    GL_destroy_body(main_struct);
    return 0;
}
