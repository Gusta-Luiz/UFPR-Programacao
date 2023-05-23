#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  /* Biblioteca de fontes */
#include <allegro5/allegro_image.h> /* Biblioteca de imagens */
#include <allegro5/allegro_ttf.h>   /* Biblioteca de fontes TrueType */
#include "Gamelib.h"
#include "Menulib.h"
#include "GameLoop.h"

int main() {
    srand(time(NULL));          /* Inicializa o gerador de numeros aleatorios */
    al_init();                  /* Inicializa a Allegro */
    al_init_font_addon();       /* Inicializa a biblioteca de fontes do allegro */
    al_init_image_addon();      /* Inicializa a biblioteca de imagens, para os assets do jogo */
    al_init_ttf_addon();        /* Inicializa a biblioteca ttf, de fontes TrueType */
    al_install_keyboard();      /* Adiciona o suporte ao teclado */
    al_install_mouse();         /* Adiciona o suporte ao mouse */

    int cfg_width = 960;
    int cfg_height = 540;
    int cfg_fps = 60;

    /*--------------- Imagens e Fontes usadas no jogo ---------------*/
    /* Icone do jogo  */
    char *img_Body_icon       = "./Contents/Images/Icon.png";
    /* Menu principal */
    char *img_Home_background = "./Contents/Images/HomeBg.png";
    char *img_Home_options    = "./Contents/Images/HomeOptions.png";
    /* Tela de jogo   */
    char *img_Game_background = "./Contents/Images/GameBg.jpg";
    char *img_Game_fruits     = "./Contents/Images/Fruits.png";
    char *img_Game_block      = "./Contents/Images/BlockSelect.png";
    /* Fontes */
    char *font_big            = "./Contents/Fonts/Stardew.ttf";
    char *font_medium         = "./Contents/Fonts/StardewMain.ttf";
    /* Imagens que serao animadas */
    ALLEGRO_BITMAP *img_cloud = al_load_bitmap("./Contents/Images/Clouds.png");
    ALLEGRO_BITMAP *img_birds = al_load_bitmap("./Contents/Images/Birds.png");

    /*--------------- Janela Principal ---------------*/
    /* Aloca e cria a janela principal, o timer, e a lista de eventos
     * A lista ja contem a tela, timer, teclado e mouse inseridos */
    GAME_STRUCT *main_body = GL_create_body(cfg_width, cfg_height, cfg_fps, img_Body_icon);
    if (main_body == NULL) {
        printf("ERRO: ao criar o corpo principal do jogo!");
        return 0;
    }

    /*--------------- Menu principal e inicio do jogo ---------------*/
    /* Cria a struct que armazena dados do menu principal do jogo */
    GAME_UI *Home_ui = GL_create_ui(img_Home_background, img_Home_options, NULL, NULL, font_big, font_medium);
    if (Home_ui == NULL) {
        printf("ERRO: ao criar a struct do menu principal!");
        return 0;
    }
    /* Cria a struct que armazena dados da tela de jogo */
    GAME_UI *Junimo_ui = GL_create_ui(img_Game_background, NULL, img_Game_fruits, img_Game_block, NULL, NULL);
    if (Junimo_ui == NULL) {
        printf("ERRO: ao criar a struct da tela de jogo!");
        return 0;
    }

    /*--------------- Configuracoes para animacoes ---------------*/
    /* Carrega os dados necessarios e cria a struct dos passaros */
    MENU_BIRDS *Birds = (MENU_BIRDS*) malloc(sizeof(MENU_BIRDS));
    

    /*--------------- Loop Principal ---------------*/
    MM_MainMenu_loop(main_body, Home_ui, birds);
    
    /*--------------- Fim do jogo, Liberar memoria ---------------*/
    al_clear_to_color(al_map_rgb(0,0,0));
    /* Janela, timer e lista de eventos */
    GL_destroy_body(main_body);
    /* Menus e interfaces */
    GL_destroy_ui(Home_ui);
    GL_destroy_ui(Junimo_ui);
    /* Passaros, e imagens "soltas" */
    free(bird1);
    free(bird2);
    al_destroy_bitmap(img_birds);
    al_destroy_bitmap(img_cloud);

    return 0;
}
