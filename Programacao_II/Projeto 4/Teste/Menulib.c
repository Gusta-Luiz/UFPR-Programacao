#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  /* Biblioteca de fontes */
#include <allegro5/allegro_image.h> /* Biblioteca de imagens */
#include <allegro5/allegro_ttf.h>   /* Biblioteca de fontes TrueType */
#include "Global.h"
#include "Menulib.h"

/* Desenha o menu principal, na janela selecionada */
void MM_draw_menu(GAME_STRUCT *main_body, GAME_UI *Home_ui){
    /* Titulo principal, Alinhado ao centro da tela */
    al_draw_scaled_bitmap(Home_ui->Background, 0, 0, 2561, 1440, 0, 0, main_body->Width, main_body->Height, 0);
    al_draw_bitmap_region(Home_ui->Image1, 0, 0, 400, 187, (main_body->Width/2-200), 30, 0);
    /* Opcao de novo jogo, alinhados abaixo do titulo principal */
    al_draw_bitmap_region(Home_ui->Image1, 0, 187, 74, 59, (main_body->Width/2-200), 220, 0);
    al_draw_text(Home_ui->Font2, al_map_rgb(32, 32, 32), (main_body->Width/2-120), 230, 0, "Start a New Game");
    /* Opcao de continuar jogo salvo, alinhado abaixo do novo jogo */
    al_draw_bitmap_region(Home_ui->Image1, 74, 187, 74, 59, (main_body->Width/2-200), 290, 0);
    al_draw_text(Home_ui->Font2, al_map_rgb(32, 32, 32), (main_body->Width/2-120), 300, 0, "Continue Saved Game");
    /* Opcao de sair para o desktop, alinhado abaixo do Continuar jogo */
    al_draw_bitmap_region(Home_ui->Image1, 222, 187, 74, 59, (main_body->Width/2-200), 360, 0);
    al_draw_text(Home_ui->Font2, al_map_rgb(32, 32, 32), (main_body->Width/2-120), 370, 0, "Exit to desktop");
    /* Opcao de configuracoes, alinhado ao canto inferior direito, perto do limite da janela */
    al_draw_scaled_bitmap(Home_ui->Image1, 347, 418, 25, 25, (main_body->Width-80), (main_body->Height-80), 50, 50, 0);
    al_draw_text(Home_ui->Font2, al_map_rgb(20, 20, 20), (main_body->Width-130), (main_body->Height-70), 0, "Help");
}

/* Muda a sprite do menu principal de acordo com a opcao em que o mouse se encontra */
void MM_draw_selected_option(GAME_STRUCT *main_body, GAME_UI *Home_ui, int option){
    switch(option){
        case 1: /* Sair para o desktop */
            al_draw_bitmap_region(Home_ui->Image1, 222, 246, 74, 59, (main_body->Width/2-200), 360, 0);
            break;
        case 2: /* Novo jogo */
            al_draw_bitmap_region(Home_ui->Image1, 0, 246, 74, 59, (main_body->Width/2-200), 220, 0);
            break;
        case 3: /* Continuar jogo */
            al_draw_bitmap_region(Home_ui->Image1, 74, 246, 74, 59, (main_body->Width/2-200), 290, 0);
            break;
        case 4: /* Configuracoes */
            al_draw_scaled_bitmap(Home_ui->Image1, 372, 418, 25, 25, (main_body->Width-74), (main_body->Height-80), 50, 50, 0);
            break;
        case 0: /* Nenhuma opcao */
            break;
    }
}

/* Checa se o mouse esta sobre uma opcao do menu */
int MM_check_mouse(GAME_STRUCT *main_body, int mouse_x, int mouse_y){
    if(mouse_x >= (main_body->Width/2-200) && mouse_x <= (main_body->Width/2-126)){
        if(mouse_y >= 360 && mouse_y <= 419) return 1;     /* Sair para o desktop */
        else if(mouse_y >= 220 && mouse_y <= 279) return 2;          /* Novo jogo */
        else if(mouse_y >= 290 && mouse_y <= 349) return 3;     /* Continuar jogo */
    } else if(mouse_x >= (main_body->Width-80) && mouse_x <= (main_body->Width-30)) 
        if(mouse_y >= (main_body->Height-80) && mouse_y <= (main_body->Height-30)) return 4; /* Configuracoes */
    return 0;
}

/*--------------- Funcoes para criacao e animacao dos passaros ---------------*/
/* Realiza a animacao de fundo do passaro, funcao percorrida a cada frame */
void MM_animate_bird(GAME_STRUCT *window, MENU_ALLBIRDS *birds, int bird_id){
    /* Se o pasaro chegou ao fim da tela, cria um novo com valores aleatorios */
    if (birds->birds_list[bird_id] == NULL){
        birds->birds_list[bird_id] = MM_create_bird(window);
    }
    /* Anima o passaro */
    /* Da Esquerda para a Direita */
    if (bird->Direction == 0){
        if (bird->Curr_Frame < 0.5)
            al_draw_scaled_bitmap(img_birds, 32, 16*bird->id, 16, 16, bird->X, bird->Y, 32, 32, 0);
        else if (bird->Curr_Frame < 1)
            al_draw_scaled_bitmap(img_birds, 48, 16*bird->id, 16, 16, bird->X, bird->Y, 32, 32, 0);
        bird->X -= bird->Speed;
    }
    /* Da Direita para a Esquerda */
    if (bird->Direction == 1){
        if (bird->Curr_Frame < 0.5)
            al_draw_scaled_bitmap(img_birds, 32, 16*bird->id, 16, 16, bird->X, bird->Y, 32, 32, ALLEGRO_FLIP_HORIZONTAL);
        else if (bird->Curr_Frame < 1)
            al_draw_scaled_bitmap(img_birds, 48, 16*bird->id, 16, 16, bird->X, bird->Y, 32, 32, ALLEGRO_FLIP_HORIZONTAL);
        bird->X += bird->Speed;
    }
    /* Reset da animacao */
    if (bird->Curr_Frame > 1)
        bird->Curr_Frame = 0;
    else
        bird->Curr_Frame += 0.05;
}

/* Tela do menu principal, onde o jogador pode escolher entre opcoes ou sair do jogo */
void MM_MainMenu_loop(GAME_STRUCT *game_struct, GAME_UI *Main_ui ){
    MENU_BIRDS *birds = (MENU_BIRDS*)malloc(sizeof(MENU_BIRDS));
    MM_create_birds(game_struct, Main_ui->Image1, 2);
    
    /* Variaveis utilizadas para controle do menu */
    int exit = 0;
    int redraw = 0;
    int mouse_option = 0;
    ALLEGRO_EVENT event;
    /* Inicializa o relogio, e o loop */
    al_start_timer(game_struct->Timer);
    while (!exit) {
        al_wait_for_event(game_struct->Event, &event);
        /* Caso nada aconteca, o menu é redesenhado a cada 1/60 de segundo, para manter as animacoes */
        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = 1;
        }
        /* Caso seja pressionado o "X" para fechar a janela */
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { 
            exit = 1;
        }
        /* Verifica a posicao do mouse, caso esteja em uma opcao, a destaca com outra sprite */
        else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) { 
            mouse_option = MM_check_mouse(game_struct, event.mouse.x, event.mouse.y);
            redraw = 1;
        }
        /* Verifica se o mouse foi pressionado em alguma opcao do menu, e realiza a acao necessaria */
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            mouse_option = MM_check_mouse(game_struct, event.mouse.x, event.mouse.y);
            if (mouse_option != 0){
                /* Retorna a opcao selecionada */
                exit = mouse_option;
                redraw = 0;
            }
            redraw = 1;
        }

        if (redraw && al_is_event_queue_empty(game_struct->Event)) {
            /* Desenha todas as imagens que devem ser mostradas na tela, e a atualiza */
            MM_draw_menu(game_struct, Main_ui);
            MM_draw_selection(game_struct, Main_ui, mouse_option);
            MM_draw_bird(game_struct, img_birds, bird2);
            MM_draw_bird(game_struct, img_birds, bird1);
            al_flip_display();
            redraw = 0;
        }
    }
    /* Retorna o valor de saida do menu */
    return exit;
}