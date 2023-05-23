#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  /* Biblioteca de fontes */
#include <allegro5/allegro_image.h> /* Biblioteca de imagens */
#include <allegro5/allegro_ttf.h>   /* Biblioteca de fontes TrueType */
#include "Gamelib.h"

/* Cria o corpo principal do jogo, contendo a janela principal, o timer e a lista de eventos
 * Configura o titulo e o icone da janela, e registra a tela, timer, teclado e mouse na fila de eventos
 * --O timer deve ser iniciado antes do loop principal  */
GAME_STRUCT *GL_create_body(int width, int height, int fps, char *icon) {
    GAME_STRUCT *body = (GAME_STRUCT *) malloc(sizeof(GAME_STRUCT));
    /* Cria a tela com os parametros especificados */
    body->Width = width;
    body->Height = height;
    body->Display = al_create_display(width, height);
    al_set_window_position(body->Display, 200, 100);
    al_set_window_title(body->Display, "Junimo Rush by Gusta");
    al_set_display_icon(body->Display, al_load_bitmap(icon));
    /* Cria o timer */
    body->FPS = fps;
    body->Timer = al_create_timer(1.0 / fps);
    /* Cria a fila de eventos e adiciona a tela, timer, o teclado e o mouse */
    body->Event = al_create_event_queue();
    al_register_event_source(body->Event, al_get_display_event_source(body->Display));
    al_register_event_source(body->Event, al_get_timer_event_source(body->Timer));
    al_register_event_source(body->Event, al_get_keyboard_event_source());
    al_register_event_source(body->Event, al_get_mouse_event_source());
    return body;
}

/* Libera a memoria alocada para o corpo principal do jogo */
void GL_destroy_body(GAME_STRUCT *body) {
    al_destroy_display(body->Display);
    al_destroy_timer(body->Timer);
    al_destroy_event_queue(body->Event);
    free(body);
    body = NULL;
    return;
}

/* Cria uma interface do jogo, como o menu principal, menu de opcoes, etc... 
 * Aloca os dados necessarios e cria uma struct para a interface */
GAME_UI *GL_create_ui(char *background, char *image1, char *image2, char *image3, char *font1, char *font2){
    GAME_UI *interface = (GAME_UI *) malloc(sizeof(GAME_UI));
    interface->Background = al_load_bitmap(background);
    if (image1 != NULL) interface->Image1 = al_load_bitmap(image1);
    else interface->Image1 = NULL;
    if (image2 != NULL) interface->Image2 = al_load_bitmap(image2);
    else interface->Image2 = NULL;
    if (image3 != NULL) interface->Image3 = al_load_bitmap(image3);
    else interface->Image3 = NULL;
    if (font1 != NULL) interface->Font1 = al_load_font(font1, 40, 0);
    else interface->Font1 = NULL;
    if (font2 != NULL) interface->Font2 = al_load_font(font2, 30, 0);
    else interface->Font2 = NULL;
    return interface;
}

/* Destroi a struct da interface e libera seus dados de modo correto */
void GL_destroy_ui(GAME_UI *interface) {
    if (interface->Background != NULL) al_destroy_bitmap(interface->Background);
    if (interface->Image1 != NULL) al_destroy_bitmap(interface->Image1);
    if (interface->Image2 != NULL) al_destroy_bitmap(interface->Image2);
    if (interface->Image3 != NULL) al_destroy_bitmap(interface->Image3);
    if (interface->Font1 != NULL) al_destroy_font(interface->Font1);
    if (interface->Font2 != NULL) al_destroy_font(interface->Font2);
    free(interface);
    interface = NULL;
    return;
}

/* Cria a struct com os dados enviados, para objetos que serao animados no jogo */
GAME_ANIMATED *GL_create_animated(int width, int height, int speed) {
    GAME_ANIMATED *animated = (GAME_ANIMATED *) malloc(sizeof(GAME_ANIMATED));
    animated->Width = width;
    animated->Height = height;
    animated->Speed = speed;
    animated->X = 0;
    animated->Y = 0;
    animated->Curr_Frame = 0;
    return animated;
}

/* Realiza a animacao de transicao entre menus */
void GL_transition(GAME_STRUCT *main_body, GAME_UI *Source_ui, GAME_UI *Destination_ui, ALLEGRO_BITMAP *img_clouds){
    int position = main_body->Width;
    /* Anima a transicao para encobrir a tela */
    while (position > -200){
        /* Desenha o background do menu de origem por tras das nuvens */
        al_draw_scaled_bitmap(Source_ui->Background, 0, 0, al_get_bitmap_width(Source_ui->Background), al_get_bitmap_height(Source_ui->Background), 0, 0, main_body->Width, main_body->Height, 0);
        al_draw_bitmap(img_clouds, position, 0, 0);
        al_flip_display();
        position -= 20;
    }
    /* Finaliza a animacao para revelar a nova tela */
    while (position > -1200){
        /* Desenha o background do menu de destino por tras das nuvens */
        al_draw_scaled_bitmap(Destination_ui->Background, 0, 0, al_get_bitmap_width(Destination_ui->Background), al_get_bitmap_height(Destination_ui->Background), 0, 0, main_body->Width, main_body->Height, 0);
        al_draw_bitmap(img_clouds, position, 0, 0);
        al_flip_display();
        position -= 20;
    }
}