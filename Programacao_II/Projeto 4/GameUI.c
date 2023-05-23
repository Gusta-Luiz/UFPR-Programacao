#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  /* Biblioteca de fontes */
#include <allegro5/allegro_image.h> /* Biblioteca de imagens */
#include <allegro5/allegro_ttf.h>   /* Biblioteca de fontes TrueType */

#include "Global.h"
#include "Gamelib.h"
#include "GameUI.h"

/* Desenha a interface do jogo na tela */
void GG_draw_menu(GAME_STRUCT *main_body, GAME_UI *junimo_ui, GRID_STRUCT *grid) {
    if (grid->Level % 2 == 0)
        al_draw_scaled_bitmap(junimo_ui->Image[4], 0, 0, al_get_bitmap_width(junimo_ui->Background), al_get_bitmap_height(junimo_ui->Background), 0, 0, main_body->Width, main_body->Height, 0);
    else
        al_draw_scaled_bitmap(junimo_ui->Background, 0, 0, al_get_bitmap_width(junimo_ui->Background), al_get_bitmap_height(junimo_ui->Background), 0, 0, main_body->Width, main_body->Height, 0);    
}

/* Desenha o grid na sua devida posicao, e suas frutas uma por uma, especiais ou nao */
void GG_draw_grid(GRID_STRUCT *grid, GAME_UI *junimo_ui) {
    for (int i = 0; i < grid->NxN; i++) {
        for (int j = 0; j < grid->NxN; j++) {
            al_draw_scaled_bitmap(junimo_ui->Image[0], grid->fruit[i][j].type*18, 0, 18, 18, grid->Width+(i*grid->imgX), grid->Height+(j*grid->imgY), 43, 43, 0);
            if (grid->fruit[i][j].special == 1)
                al_draw_scaled_bitmap(junimo_ui->Image[1], 0, 0, 9, 9, grid->Width+(i*grid->imgX)+25, grid->Height+(j*grid->imgY)+22, 18, 18, 0);
            else if (grid->fruit[i][j].special == 2)
                al_draw_scaled_bitmap(junimo_ui->Image[1], 9, 0, 9, 9, grid->Width+(i*grid->imgX)+25, grid->Height+(j*grid->imgY)+22, 18, 18, 0);
        }
    }
}

/* Funcao que reconhece se o mouse clicou em alguma fruta do grid */
GRID_FRUIT *GG_check_click(GRID_STRUCT *grid, int mouseX, int mouseY) {
    int x = mouseX;
    int y = mouseY;
    /* Verifica se o clique foi dentro do grid, se sim retorna o local da fruta */
    if (x > grid->Width && x < grid->Width+(grid->NxN*grid->imgX) && y > grid->Height && y < grid->Height+(grid->NxN*grid->imgY)) {
        int i = (x - grid->Width) / grid->imgX;
        int j = (y - grid->Height) / grid->imgY;
        return &grid->fruit[i][j];
    }
    /* Se nao, retorna nada */
    GRID_FRUIT *null = NULL;
    return null;
}

/* Desenha a silhueta para indicar qual fruta foi selecionada, de acordo com onde o mouse é pressionado na tela */
void GG_draw_mouse_selection(GRID_STRUCT *grid, GAME_UI *junimo_ui, GRID_FRUIT *fruit) {
    if (fruit != NULL) {
        int i = fruit->x;
        int j = fruit->y;
        al_draw_scaled_bitmap(junimo_ui->Image[2], 0, 0, 18, 18, grid->Width+(i*grid->imgX), grid->Height+(j*grid->imgY)-2, 47, 46, 0);
    }
    return;
}

/* Troca duas frutas de posicao, e desenha a transicao entre elas */
void GG_draw_swap(GRID_STRUCT *grid, GAME_UI *junimo_ui, GRID_FRUIT *fruit1, GRID_FRUIT *fruit2) {
    /* Se as frutas sao iguais, ou estao a mais de uma posicao de distancia, nao faz nada */
    if (fruit1 == fruit2 || abs(fruit1->x - fruit2->x) > 1 || abs(fruit1->y - fruit2->y) > 1) {
        return;
    }
    /* Decide quais as cordenadas que deverao ser afetadas pela animacao */
    int Swap_X1 = 0;
    int Swap_X2 = 0;
    int Swap_Y1 = 0;
    int Swap_Y2 = 0;
    /* Se as frutas estao na mesmsa linha */
    if (fruit1->x == fruit2->x) {
        /* Decide se a fruta 1 deve ser movida para cima ou para baixo */
        if (fruit1->y > fruit2->y) {
            Swap_Y1 = -1;
            Swap_Y2 = 1;
        } else {
            Swap_Y1 = 1;
            Swap_Y2 = -1;
        }
    /* Se as frutas estao na mesma coluna */
    } else if (fruit1->y == fruit2->y) {
        /* Decide se a fruta 1 deve ser movida para a esquerda ou para a direita */
        if (fruit1->x > fruit2->x) {
            Swap_X1 = -1;
            Swap_X2 = 1;
        } else {
            Swap_X1 = 1;
            Swap_X2 = -1;
        }
    /* Se as frutas nao estao na mesma linha ou coluna, nao faz nada */
    } else {
        return;
    }
    for (int i = 0; i < 43; i+=3){
        /* Desenha a animacao de troca, e de selecao das frutas */
        GG_draw_mouse_selection(grid, junimo_ui, fruit1);
        GG_draw_mouse_selection(grid, junimo_ui, fruit2);
        al_draw_scaled_bitmap(junimo_ui->Image[0], grid->fruit[fruit1->x][fruit1->y].type*18, 0, 18, 18, grid->Width+(fruit1->x*grid->imgX)+(i*Swap_X1), grid->Height+(fruit1->y*grid->imgY)+(i*Swap_Y1), 43, 43, 0);
        al_draw_scaled_bitmap(junimo_ui->Image[0], grid->fruit[fruit2->x][fruit2->y].type*18, 0, 18, 18, grid->Width+(fruit2->x*grid->imgX)+(i*Swap_X2), grid->Height+(fruit2->y*grid->imgY)+(i*Swap_Y2), 43, 43, 0);
        al_flip_display();
    }
    /* Troca as frutas de posicao */
    GGL_swap_fruit(grid, fruit1, fruit2);
    return;
}

/* Desenha a animacao de match de frutas para cada combinacao */
void GG_draw_match(GRID_STRUCT *grid, GAME_UI *junimo) {
    /* Desenha a animacao de match com 8 frames para cada fruta que for removida com tipo -1 */
    for (int i = 0; i < grid->NxN; i++) {
        for (int j = 0; j < grid->NxN; j++) {
            if (grid->fruit[i][j].type == -1) {
                for (int k = 0; k < 8; k++) {
                    al_draw_scaled_bitmap(junimo->Image[3], k*16, 0, 16, 16, grid->Width+(i*grid->imgX), grid->Height+(j*grid->imgY), 43, 43, 0);
                    al_flip_display();
                    al_rest(0.02);
                }
            }
        }
    }
}

/* Desenha na tela a maioria das informacoes necessarias */
void GG_draw (GRID_STRUCT *grid, GAME_UI *junimo_ui, GAME_STRUCT *main_struct, GRID_FRUIT *selection1, GRID_FRUIT *selection2, float fps){
    GG_draw_menu(main_struct, junimo_ui, grid);
    GG_draw_mouse_selection(grid, junimo_ui, selection1);
    GG_draw_mouse_selection(grid, junimo_ui, selection2);
    GG_draw_grid(grid, junimo_ui);
    al_draw_textf(junimo_ui->Font[0].Font, al_map_rgb(0, 0, 0), 60, 80, 0, "FPS: %f", fps);
    al_draw_textf(junimo_ui->Font[0].Font, al_map_rgb(0, 0, 0), 60, 130, 0, "Points: %d", grid->Score);
    al_draw_textf(junimo_ui->Font[0].Font, al_map_rgb(0, 0, 0), 60, 180, 0, "Level (Multiplier): x%d", grid->Level);
    al_draw_textf(junimo_ui->Font[0].Font, al_map_rgb(0, 0, 0), 60, 230, 0, "Goal: %d", grid->Level * grid->Level * 1000);
}

/* Funcao principal, onde é executado o toda a gameplay do jogo */
void GG_game_loop (GAME_STRUCT *main_struct, GAME_UI* Help_ui) {
    /*------------ Imagens/Fontes e outros assets utilizados ------------*/
    GAME_UI *junimo_ui = GL_create_ui(img_Game_background);
    GL_load_image(junimo_ui, img_Game_fruits);   /* Image[0] */
    GL_load_image(junimo_ui, img_Game_specials);    
    GL_load_image(junimo_ui, img_Game_block);
    GL_load_image(junimo_ui, img_Game_match);
    GL_load_image(junimo_ui, img_Game_background2);
    GL_load_font(junimo_ui, font_Global_defalt, 30);

    /* Realiza o fim da transicao */
    GL_transition(main_struct, junimo_ui->Background, junimo_ui->Background, 2);

    /*------------------- Inicializa o grid de frutas -------------------*/
    GRID_STRUCT *grid = GGL_create_grid();
    int check = 1;
    while (check) {
        GGL_rearrange_fruits(grid);
        check = GGL_check_grid(grid, 1);
    }

    /*--------------------- Inicializa o menu de jogo -------------------*/
    GG_draw_menu(main_struct, junimo_ui, grid);
    GG_draw_grid(grid, junimo_ui);
    al_flip_display();

    /*---------------------- Variaveis e inicializacao ------------------*/
    GRID_FRUIT *selection1 = NULL, *selection2 = NULL;
    int exit, match1, match2, redraw = 1;
    al_start_timer(main_struct->Timer);
    double old_time = al_get_time();
    exit = 0;

    /*---------------------- Loop principal do jogo ---------------------*/
    for (;;) {
        ALLEGRO_EVENT event;
        al_wait_for_event(main_struct->Event, &event);
        /* A cada 1/60 de segundo redesenha o menu, e anda com as animacoes */
        if(event.type == ALLEGRO_EVENT_TIMER){
            redraw = 1;
        }
        /* Verifica se o usuario fechou a janela */
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            exit = 3;
        }
        /* Caso o usuario clique com o mouse, o jogo verifica se ele clicou em alguma fruta */
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            /* Checa se a primeira fruta ja foi selecionada ou nao, se sim, entao seleciona a fruta 2 */
            if (selection1 == NULL)
                selection1 = GG_check_click(grid, event.mouse.x, event.mouse.y);
            else if (selection2 == NULL)
                selection2 = GG_check_click(grid, event.mouse.x, event.mouse.y);
            /* Se as duas frutas ja foram selecionadas, entao realiza a troca */
            if (selection1 != NULL && selection2 != NULL) {
                GG_draw_swap(grid, junimo_ui, selection1, selection2);
                match1 = GGL_check_match(grid, selection1);
                match2 = GGL_check_match(grid, selection2);
                /* Se a menos uma das frutas nao formam combinacoes, entao troca elas de volta */
                if (!match1 && !match2)
                    GG_draw_swap(grid, junimo_ui, selection1, selection2);
                else
                    check = 1;
                selection1 = NULL;
                selection2 = NULL;
            }
            redraw = 1;
        }
        /* Caso o usuario aperte alguma tecla, o jogo verifica se ele apertou ESC ou F1 */
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                exit = 1;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_F1) {
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

        /* Pega o tempo atual e calcula o fps */
        double new_time = al_get_time();
        double delta = new_time - old_time;
        double fps = 1/(delta*1000);
        old_time = new_time;

        /* Checa todo o grid por combinacoes ja feitas e realiza as animacoes e desenhos */
        while (check) {
            GG_draw(grid, junimo_ui, main_struct, selection1, selection2, fps);
            al_rest(0.1);
            GG_draw_match(grid, junimo_ui);
            al_flip_display();
            /* Re organiza o grid */
            GGL_rearrange_fruits(grid);
            GG_draw(grid, junimo_ui, main_struct, selection1, selection2, fps);
            al_rest(0.1);
            GG_draw_match(grid, junimo_ui);
            al_flip_display();
            check = (GGL_check_grid(grid, 0));
        }

        /* Redesenha o menu e sua estrutura */
        if (redraw && al_is_event_queue_empty(main_struct->Event)) {
            GG_draw(grid, junimo_ui, main_struct, selection1, selection2, fps);
            al_flip_display();
            redraw = 0;
        }

        /* Checa se o usuario passou de fase, e se sim, embaralha as frutas */
        if (grid->Score >= 1000) {
            if (GGL_check_score(grid)){
                GL_transition(main_struct, junimo_ui->Background, junimo_ui->Background, 0);
                check = 1;
                while (check) {
                    GGL_rearrange_fruits(grid);
                    check = GGL_check_grid(grid, 1);
                }
            }
        }

        if (exit != 0) break;
    }

    /*-------------------- Finaliza o loop principal --------------------*/
    /* Realiza o inicio da transicao */
    GL_transition(main_struct, junimo_ui->Background, junimo_ui->Background, 1);
    al_stop_timer(main_struct->Timer);
    al_flush_event_queue(main_struct->Event);

    /*-------------------------- Libera memoria -------------------------*/
    GL_destroy_ui(junimo_ui);
    GGL_destroy_grid(grid);
    free(selection1);
    free(selection2);

    /*--------------------------- Define o estado ------------------------*/
    printf("Sucessfully exited the Game loop -> code: %d\n", exit);
    if      (exit == 1) state = MENU; /* Retorna ao menu */
    else if (exit == 2) state = LOAD; /* Carregar jogo */
    else if (exit == 3) state = EXIT; /* Sair */
    return;
}