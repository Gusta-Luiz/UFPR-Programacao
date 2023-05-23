#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  /* Biblioteca de fontes */
#include <allegro5/allegro_image.h> /* Biblioteca de imagens */
#include <allegro5/allegro_ttf.h>   /* Biblioteca de fontes TrueType */

#include "Global.h"

/* Cria o corpo principal do jogo, contendo a janela principal, o timer e a lista de eventos
 * --O timer deve ser iniciado antes do loop principal  */
GAME_STRUCT *GL_create_body(int width, int height, int frames) {
    /* Cria a tela com os parametros especificados */
    GAME_STRUCT *body = (GAME_STRUCT *) malloc(sizeof(GAME_STRUCT));
    body->Width = width;
    body->Height = height;
    body->Display = al_create_display(width, height);
    al_set_window_position(body->Display, 200, 100);
    al_set_window_title(body->Display, "Fruit Valley by Gusta");
    al_set_display_icon(body->Display, al_load_bitmap(img_Body_icon));
    /* Cria o timer */
    body->Frames = frames;
    body->Timer = al_create_timer(1.0/frames);
    /* Cria a fila de eventos e adiciona a tela, timer, o teclado e o mouse */
    body->Event = al_create_event_queue();
    al_register_event_source(body->Event, al_get_display_event_source(body->Display));
    al_register_event_source(body->Event, al_get_timer_event_source(body->Timer));
    al_register_event_source(body->Event, al_get_keyboard_event_source()); 
    al_register_event_source(body->Event, al_get_mouse_event_source());
    /* Testa se ocorreu algum erro */
    if (!body || !body->Display || !body->Timer || !body->Event) {
        printf("Global.c -> \nERRO: ao criar o corpo principal do jogo!\n");
        exit(1);
    }
    return body;
}

/* Libera a memoria alocada para o corpo principal do jogo */
void GL_destroy_body(GAME_STRUCT *body) {
    al_destroy_event_queue(body->Event);
    al_destroy_display(body->Display);
    al_destroy_timer(body->Timer);
    free(body);
    body = NULL;
    return;
}

/* Cria uma interface do jogo, como o menu principal, menu de opcoes, etc... 
 * e carrega os dados necessarios */
GAME_UI *GL_create_ui(char *background) {
    GAME_UI *interface = (GAME_UI *) malloc(sizeof(GAME_UI));
    interface->Background = al_load_bitmap(background);
    interface->Image_count = 0;
    interface->Font_count = 0;
    /* Testa se ocorreu algum erro */
    if (!interface || !interface->Background) {
        printf("Global.c -> \nERRO: ao criar a interface!\n");
        exit(1);
    }
    return interface;
}

/* Destroi a struct da interface e libera seus dados de modo correto */
void GL_destroy_ui(GAME_UI *interface) {
    int i;
    for (i = 0; i < interface->Image_count; i++) {
        al_destroy_bitmap(interface->Image[i]);
    }
    for (i = 0; i < interface->Font_count; i++) {
        GL_destroy_font(&interface->Font[i]);
    }
    al_destroy_bitmap(interface->Background);
    free(interface);
    interface = NULL;
    /* Testa se ocorreu algum erro */
    if (interface != NULL) {
        printf("ERRO Global.c: \nErro ao limpar a interface!\n");
        exit(1);
    }
    return;
}

/* Carrega uma imagem e seus dados em uma estrutura e a salva na interface */
void GL_load_image(GAME_UI *ui_dest, char *path) {
    if (ui_dest->Image_count == 0)
        ui_dest->Image = (ALLEGRO_BITMAP **) malloc(sizeof(ALLEGRO_BITMAP *));
    else
        ui_dest->Image = (ALLEGRO_BITMAP **) realloc(ui_dest->Image, sizeof(ALLEGRO_BITMAP *) * (ui_dest->Image_count + 1));
    ui_dest->Image[ui_dest->Image_count] = al_load_bitmap(path);
    ui_dest->Image_count++;
    return;
}

/* Carrega uma fonte e seus dados em uma estrutura e a salva na interface */
void GL_load_font(GAME_UI *ui_dest, char *path, int size) {
    if (ui_dest->Font_count == 0)
        ui_dest->Font = (GAME_UI_FONT *) malloc(sizeof(GAME_UI_FONT));
    else
        ui_dest->Font = (GAME_UI_FONT *) realloc(ui_dest->Font, sizeof(GAME_UI_FONT) * (ui_dest->Font_count + 1));
    ui_dest->Font[ui_dest->Font_count].Font = al_load_font(path, size, 0);
    ui_dest->Font_count++;
    return;
}

void GL_destroy_font(GAME_UI_FONT *font) {
    al_destroy_font(font->Font);
    free(font);
    font = NULL;
    return;
}

/* Realiza a animacao de transicao entre menus, utilizando uma sprite de nuvens 
 * Flag == 0: Realiza a transicao por completo
 * Flag == 1: realiza a primeira metade
 * Flag == 2: Realiza a segunda e ultima metade */
void GL_transition(GAME_STRUCT *main_struct, ALLEGRO_BITMAP *Source_bg, ALLEGRO_BITMAP *Destination_bg, int flag){
    /* Cria a sprite de nuvens */
    ALLEGRO_BITMAP *img_clouds = al_load_bitmap(img_Global_clouds);
    int img_width = al_get_bitmap_width(img_clouds);
    int position;
    /* Realiza a primeira metade da transicao, acaba quando as nuvens estiverem no meio da tela */
    if (flag == 0 || flag == 1) {
        /* Posiciona as nuvens antes do inicio */
        position = img_width + main_struct->Width / 2 - img_width / 2;
        while (position > main_struct->Width / 2 - img_width / 2){
            /* Desenha o background do menu de origem por tras das nuvens */
            al_draw_scaled_bitmap(Source_bg, 0, 0, al_get_bitmap_width(Source_bg), al_get_bitmap_height(Source_bg), 0, 0, main_struct->Width, main_struct->Height, 0);
            al_draw_bitmap(img_clouds, position, 0, 0);
            al_flip_display();
            /* Muda a posicao das nuvens */
            position -= 20;
        }
    } 
    /* Finaliza a animacao para revelar a nova tela */
    if (flag == 0 || flag == 2) {
        position = main_struct->Width / 2 - img_width / 2;
        while (position > img_width * -1){
            /* Desenha o background do menu de destino por tras das nuvens */
            al_draw_scaled_bitmap(Destination_bg, 0, 0, al_get_bitmap_width(Destination_bg), al_get_bitmap_height(Destination_bg), 0, 0, main_struct->Width, main_struct->Height, 0);
            al_draw_bitmap(img_clouds, position, 0, 0);
            al_flip_display();
            /* Muda a posicao das nuvens */
            position -= 20;
        }
    }
    /* Libera memoria alocada */
    al_destroy_bitmap(img_clouds);
    return;
}

/* Desenha a tela de ajuda e seus componentes */
void GL_draw_help(GAME_STRUCT *main_struct, GAME_UI* Help_ui){
    al_draw_scaled_bitmap(Help_ui->Background, 0, 0, al_get_bitmap_width(Help_ui->Background), al_get_bitmap_height(Help_ui->Background), 0, 0, main_struct->Width, main_struct->Height, 0);
    al_draw_text(Help_ui->Font[0].Font, al_map_rgb(32, 32, 32), 490, 105, ALLEGRO_ALIGN_CENTRE, "Help");
    al_draw_text(Help_ui->Font[1].Font, al_map_rgb(32, 32, 32), 490, 180, ALLEGRO_ALIGN_CENTRE, "Press ESC to return to the menu");
    /* Regras */
    al_draw_text(Help_ui->Font[2].Font, al_map_rgb(32, 32, 32), 220, 220, 0, "-> Select 2 fruits to swap them");
    al_draw_text(Help_ui->Font[2].Font, al_map_rgb(32, 32, 32), 220, 250, 0, "-> Match 3 or more fruits to score");
    al_draw_text(Help_ui->Font[2].Font, al_map_rgb(32, 32, 32), 220, 280, 0, "-> Match 4 to get a special fruit, simbolized by a skull");
    al_draw_text(Help_ui->Font[2].Font, al_map_rgb(32, 32, 32), 220, 310, 0, "     -> The special fruit will clear all the fruits around it");
    al_draw_text(Help_ui->Font[2].Font, al_map_rgb(32, 32, 32), 220, 340, 0, "-> Match 5 on a 'T', 'L' or 'Cross' shape to get a star fruit");
    al_draw_text(Help_ui->Font[2].Font, al_map_rgb(32, 32, 32), 220, 370, 0, "     -> The star fruit will clear all fruits on the same row and column");
    /* Creditos centralizados abaixo da tela */
    al_draw_text(Help_ui->Font[1].Font, al_map_rgb(255, 255, 255), 490, 480, ALLEGRO_ALIGN_CENTRE, "Developed by: Luiz Gustavo Dalmaz");
    al_draw_text(Help_ui->Font[1].Font, al_map_rgb(16, 16, 16), 490, 21, ALLEGRO_ALIGN_CENTRE, "Original arts, and inspired by: 'ConcernedApe'");
}