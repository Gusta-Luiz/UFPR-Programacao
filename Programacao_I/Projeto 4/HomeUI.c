#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  /* Biblioteca de fontes */
#include <allegro5/allegro_image.h> /* Biblioteca de imagens */
#include <allegro5/allegro_ttf.h>   /* Biblioteca de fontes TrueType */

#include "Global.h"
#include "HomeUI.h"

/* Desenha o menu principal, e todas as suas opcoes na janela selecionada */
void HM_draw_menu(GAME_STRUCT *main_struct, GAME_UI *Home_ui){
    /* Titulo principal, Alinhado ao centro da tela */
    al_draw_scaled_bitmap(Home_ui->Background, 0, 0, al_get_bitmap_width(Home_ui->Background), al_get_bitmap_height(Home_ui->Background), 0, 0, main_struct->Width, main_struct->Height, 0);
    //TO-DO: Adicionar um titulo principal...
    /* Opcao de novo jogo, alinhados abaixo do titulo principal */
    al_draw_scaled_bitmap(Home_ui->Image[0], 0, 0, 74, 57, (main_struct->Width/2-200), (main_struct->Height/2-100), 92, 71, 0);
    al_draw_text(Home_ui->Font[0].Font, al_map_rgb(32, 32, 32), (main_struct->Width/2-100), (main_struct->Height/2-80), 0, "Start a New Game");
    /* Opcao de continuar jogo salvo, alinhado abaixo do novo jogo */
    al_draw_scaled_bitmap(Home_ui->Image[0], 74, 0, 74, 57, (main_struct->Width/2-200), (main_struct->Height/2-20), 92, 71, 0);
    al_draw_text(Home_ui->Font[0].Font, al_map_rgb(32, 32, 32), (main_struct->Width/2-100), (main_struct->Height/2), 0, "Continue a Saved Game");
    /* Opcao de sair para o desktop, alinhado abaixo do Continuar jogo */
    al_draw_scaled_bitmap(Home_ui->Image[0], 148, 0, 74, 57, (main_struct->Width/2-200), (main_struct->Height/2+60), 92, 71, 0);
    al_draw_text(Home_ui->Font[0].Font, al_map_rgb(32, 32, 32), (main_struct->Width/2-100), (main_struct->Height/2+80), 0, "Exit to desktop");
    /* Opcao de configuracoes, alinhado ao canto inferior direito, perto do limite da janela */
    al_draw_scaled_bitmap(Home_ui->Image[0], 222, 90, 22, 25, (main_struct->Width-80), (main_struct->Height-80), 44, 50, 0);
    al_draw_text(Home_ui->Font[0].Font, al_map_rgb(20, 20, 20), (main_struct->Width-130), (main_struct->Height-70), 0, "Help");
}

/* Muda a sprite do menu principal de acordo com a opcao em que o mouse se encontra */
void HM_draw_selection(GAME_STRUCT *main_struct, GAME_UI *Home_ui, int option){
    switch(option){
        case 1:
            al_draw_scaled_bitmap(Home_ui->Image[0], 0, 57, 74, 57, (main_struct->Width/2-200), (main_struct->Height/2-100), 92, 71, 0);
            al_draw_text(Home_ui->Font[0].Font, al_map_rgb(64, 64, 64), (main_struct->Width/2-100), (main_struct->Height/2-80), 0, "Start a New Game");
            break;
        case 2:
            al_draw_scaled_bitmap(Home_ui->Image[0], 74, 57, 74, 57, (main_struct->Width/2-200), (main_struct->Height/2-20), 92, 71, 0);
            al_draw_text(Home_ui->Font[0].Font, al_map_rgb(64, 64, 64), (main_struct->Width/2-100), (main_struct->Height/2), 0, "Continue a Saved Game");
            break;
        case 3:
            al_draw_scaled_bitmap(Home_ui->Image[0], 148, 57, 74, 57, (main_struct->Width/2-200), (main_struct->Height/2+60), 92, 71, 0);
            al_draw_text(Home_ui->Font[0].Font, al_map_rgb(64, 64, 64), (main_struct->Width/2-100), (main_struct->Height/2+80), 0, "Exit to desktop");
            break;
        case 4:
            al_draw_scaled_bitmap(Home_ui->Image[0], 244, 90, 22, 25, (main_struct->Width-80), (main_struct->Height-80), 44, 50, 0);
            al_draw_text(Home_ui->Font[0].Font, al_map_rgb(40, 40, 40), (main_struct->Width-130), (main_struct->Height-70), 0, "Help");
            break;
        case 0:
            break;
    }
}

/* Checa se o mouse esta sobre uma opcao do menu, e a retorna */
int HM_check_mouse(GAME_STRUCT *main_struct, int mouse_x, int mouse_y){
    if(mouse_x >= (main_struct->Width/2-200) && mouse_x <= (main_struct->Width/2-200)+92){
        if(mouse_y >= (main_struct->Height/2-100) && mouse_y <= (main_struct->Height/2-100)+71)
            return 1;   /* Novo jogo */
        else if(mouse_y >= (main_struct->Height/2-20) && mouse_y <= (main_struct->Height/2-20)+71)
            return 2;   /* Continuar jogo */
        else if(mouse_y >= (main_struct->Height/2+60) && mouse_y <= (main_struct->Height/2+60)+71)
            return 3;   /* Sair */
    }
    else if(mouse_x >= (main_struct->Width-80) && mouse_x <= (main_struct->Width-80)+44){
            if(mouse_y >= (main_struct->Height-80) && mouse_y <= (main_struct->Height-80)+50)
                return 4;   /* Configuracoes */
    }
    return 0;   /* Nenhuma opcao */
}

/* Cria um vetor de <count> passaros que voarao pelo menu principal */
GAME_HOME_BIRDS *HM_create_birds(GAME_STRUCT *main_struct, int count){
    GAME_HOME_BIRDS *birds_vet = malloc(sizeof(GAME_HOME_BIRDS) * count);
    for (int i = 0; i < count; i++){
        birds_vet[i].id = rand() % 6+1;                         /* Tipo de passaro */
        birds_vet[i].y = rand() % (main_struct->Height-100);    /* Posicao Y (ALtura) */
        birds_vet[i].direction = rand() % 2;                    /* Posicao Z (esquerda x direita)*/
        birds_vet[i].speed = rand() % 3+1;                      /* Velocidade do passarinho */
        birds_vet[i].frame = 0;                                 /* Frame atual */
        if (birds_vet[i].direction == 0)                        
            birds_vet[i].x = main_struct->Width;                /* Posicao X (Largura) */
        else
            birds_vet[i].x = -33;                               /* Posicao X (Largura) */
    }
    if(birds_vet == NULL){
        printf("ERRO HomeUI.c: \nErro ao alocar memoria para os passaros do menu principal\n");
        exit(1);
    }
    return birds_vet;
}

/* Libera a memoria alocada para o vetor de passaros */
void HM_destroy_birds(GAME_HOME_BIRDS *birds_vet){
    free(birds_vet);
    birds_vet = NULL;
    if (birds_vet != NULL){
        printf("ERRO HomeUI.c: \nErro ao liberar memoria dos passaros do menu principal\n");
        exit(1);
    }
}

/* Verifica e realiza a animacao de fundo de todos os passaros no vetor */
void HM_draw_birds(GAME_STRUCT *window, ALLEGRO_BITMAP *img_birds, GAME_HOME_BIRDS birds_vet[], int count){
    /* Verifica se algum passaro ja saiu da tela, se sim atualiza os valores dele */
    for (int i = 0; i < count; i++){
        if (birds_vet[i].x < -33 || birds_vet[i].x > window->Width){
            birds_vet[i].id = rand() % 6+1;                         /* Tipo de passaro */
            birds_vet[i].y = rand() % (window->Height-100);         /* Posicao Y (ALtura) */
            birds_vet[i].direction = rand() % 2;                    /* Posicao Z (esquerda x direita)*/
            birds_vet[i].speed = rand() % 3+1;                      /* Velocidade do passarinho */
            birds_vet[i].frame = 0;                            /* Frame atual */
            if (birds_vet[i].direction == 0)                        
                birds_vet[i].x = window->Width;                     /* Posicao X (Largura) */
            else
                birds_vet[i].x = -33;                               /* Posicao X (Largura) */
        }
    /* Inicia a animacao do passaro */
    /* Da Esquerda para a Direita */
    if (birds_vet[i].direction == 0){
        if (birds_vet[i].frame < 0.5)
            al_draw_scaled_bitmap(img_birds, 32, 16*birds_vet[i].id, 16, 16, birds_vet[i].x, birds_vet[i].y, 32, 32, 0);
        else if (birds_vet[i].frame < 1)
            al_draw_scaled_bitmap(img_birds, 48, 16*birds_vet[i].id, 16, 16, birds_vet[i].x, birds_vet[i].y, 32, 32, 0);
        birds_vet[i].x -= birds_vet[i].speed;
    }
    /* Da Direita para a Esquerda */
    else if (birds_vet[i].direction == 1){
        if (birds_vet[i].frame < 0.5)
            al_draw_scaled_bitmap(img_birds, 32, 16*birds_vet[i].id, 16, 16, birds_vet[i].x, birds_vet[i].y, 32, 32, ALLEGRO_FLIP_HORIZONTAL);
        else if (birds_vet[i].frame < 1)
            al_draw_scaled_bitmap(img_birds, 48, 16*birds_vet[i].id, 16, 16, birds_vet[i].x, birds_vet[i].y, 32, 32, ALLEGRO_FLIP_HORIZONTAL);
        birds_vet[i].x += birds_vet[i].speed;
    }
    /* Reset da animacao */
    if (birds_vet[i].frame >= 1)
        birds_vet[i].frame = 0;
    birds_vet[i].frame += 0.06;
    }
}

/* Loop principal do menu inicial */
void HM_home_loop(GAME_STRUCT *main_struct, GAME_UI *Help_ui){
    /*--------------- Imagens/Fontes e outros assets utilizados ---------------*/
    GAME_UI *Home_ui = GL_create_ui("./Contents/Images/HomeBg.png");
    GL_load_image(Home_ui, img_Home_options);
    GL_load_font(Home_ui, font_Global_defalt, 30);

    /* Realiza o inicio da transicao */
    GL_transition(main_struct, Home_ui->Background, Home_ui->Background, 2);

    /*---------------- Inicializa os assets para a animacao -----------------*/
    int num_birds = 3;
    GAME_HOME_BIRDS *Birds_vet = HM_create_birds(main_struct, num_birds);
    ALLEGRO_BITMAP *img_birds = al_load_bitmap(img_Global_birds);
    ALLEGRO_BITMAP *img_movie = al_load_bitmap(img_Global_movie);

    /*---------------------- Variaveis e inicializacao ------------------------*/
    int option = 0, exit = 0, click = 0, redraw = 1;
    int secret = 0;
    al_start_timer(main_struct->Timer);
    ALLEGRO_EVENT event;

    /*--------------------------- Loop principal -----------------------------*/
    for(;;){
        al_wait_for_event(main_struct->Event, &event);
        /* A cada 1/60 de segundo redesenha o menu, e anda com as animacoes */
        if(event.type == ALLEGRO_EVENT_TIMER){
            redraw = 1;
        }
        /* Verifica se o usuario fechou a janela */
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            exit = 3;
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
            option = HM_check_mouse(main_struct, event.mouse.x, event.mouse.y);
            redraw = 1;
        }
        /* Verifica se o usuario apertou alguma tecla, e navega no menu */
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_UP: 
                    if (option > 0) option--;
                    break;
                case ALLEGRO_KEY_DOWN:
                    if (option < 4) option++; 
                    break;
                case ALLEGRO_KEY_ENTER:
                    if      (option == 1) exit = 1; /* Novo jogo */
                    else if (option == 2) exit = 2; /* Carregar jogo */
                    else if (option == 3) exit = 3; /* Sair */
                    else if (option == 4) 
                        while (1) {
                            GL_draw_help(main_struct, Help_ui);
                            al_flip_display();
                            al_wait_for_event(main_struct->Event, &event);
                            /* Caso o usuario aperte ESC, o jogo volta para o menu */
                            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                                    break;
                                }
                            }
                        }
                    break;
                case ALLEGRO_KEY_F1:
                    while (1) {
                        GL_draw_help(main_struct, Help_ui);
                        al_flip_display();
                        al_wait_for_event(main_struct->Event, &event);
                        /* Caso o usuario aperte ESC, o jogo volta para o menu */
                        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                                break;
                            }
                        }
                    }
                    break;
            }
            redraw = 1;
        }
        /* Escrever a palavra "gusta" mostra o easter egg' */
        else if(event.type == ALLEGRO_EVENT_KEY_CHAR){
            if ((event.keyboard.keycode == ALLEGRO_KEY_G) && (secret == 0)) {
                secret++;
            } else if (event.keyboard.keycode == ALLEGRO_KEY_U && secret == 1) {
                secret++;
            } else if (event.keyboard.keycode == ALLEGRO_KEY_S && secret == 2) {
                secret++;
            } else if (event.keyboard.keycode == ALLEGRO_KEY_T && secret == 3) {
                secret++;
            } else if (event.keyboard.keycode == ALLEGRO_KEY_A && secret == 4) {
                secret++;
            } else {
                secret = 0;
            }
            if (secret == 5) {
                 /* Desenha a pequena aninacao de easter egg */
                for (float j = 0; j < 129; j+=64.5){
                    for (float i = 0; i < 478; i+=95.6) {
                        al_draw_scaled_bitmap(img_movie, i, j, 95.6, 64.5, 0, 0, main_struct->Width, main_struct->Height, 0);
                        al_flip_display();
                        al_rest(0.8);
                    }
                }
            }
        }
        /* verifica se o usuario clicou em alguma opcao do menu */
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            click = HM_check_mouse(main_struct, event.mouse.x, event.mouse.y);
            if      (click == 1) exit = 1; /* Novo jogo */
            else if (click == 2) exit = 2; /* Carregar jogo */
            else if (click == 3) exit = 3; /* Sair */
            else if (click == 4){ /* Ajuda/configs */
                while (1) {
                        GL_draw_help(main_struct, Help_ui);
                        al_flip_display();
                        al_wait_for_event(main_struct->Event, &event);
                        /* Caso o usuario aperte ESC, o jogo volta para o menu */
                        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                                break;
                            }
                        }
                }
            }
        }
        /* Redesenha o menu */
        if(redraw && al_is_event_queue_empty(main_struct->Event)){
            redraw = 0;
            HM_draw_menu(main_struct, Home_ui);
            HM_draw_selection(main_struct, Home_ui, option);
            HM_draw_birds(main_struct, img_birds, Birds_vet, num_birds);
            al_flip_display();
        }
        /* Sai do loop se o usuario apertou alguma opcao */
        if (exit != 0) break;
    }
    /*-------------------------- Finaliza a tela -----------------------------*/
    /* Realiza o inicio da transicao */
    GL_transition(main_struct, Home_ui->Background, Home_ui->Background, 1);
    al_stop_timer(main_struct->Timer);
    al_flush_event_queue(main_struct->Event);

    /*-------------------------- Libera memoria ------------------------------*/
    al_destroy_bitmap(img_birds);
    HM_destroy_birds(Birds_vet);

    /*--------------------------- Define o estado ----------------------------*/
    printf("Sucessfully exited the Home menu -> code: %d\n", exit);
    if      (exit == 1) state = GAME; /* Novo jogo */
    else if (exit == 2) state = LOAD; /* Carregar jogo */
    else if (exit == 3) state = EXIT; /* Sair */
    return;
}
