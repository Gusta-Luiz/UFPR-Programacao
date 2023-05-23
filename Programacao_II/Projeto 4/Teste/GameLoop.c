#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  /* Biblioteca de fontes */
#include <allegro5/allegro_image.h> /* Biblioteca de imagens */
#include <allegro5/allegro_ttf.h>   /* Biblioteca de fontes TrueType */
#include "Gamelib.h"
#include "GameLoop.h"

/* Desenha a interface do jogo na tela */
void GG_draw_menu(GAME_STRUCT *main_body, GAME_UI *junimo_ui) {
    al_draw_scaled_bitmap(junimo_ui->Background, 0, 0, al_get_bitmap_width(junimo_ui->Background), al_get_bitmap_height(junimo_ui->Background), 0, 0, main_body->Width, main_body->Height, 0);    
}

/* Cria a struct de uma fruta do jogo, de tipo (aparencia) aleatoria de acordo com o nivel atual do jogador e a salva no grid */
GRID_FRUIT *GG_create_fruit(GRID_CONFIG *grid) {
    GRID_FRUIT *newFruit = (GRID_FRUIT *) malloc(sizeof(GRID_FRUIT));
    newFruit->type = rand() % grid->fruit_types;
    newFruit->special = 0;
    return newFruit;
}

/* Cria o grid principal, com valores predefinidos, e o preenche com frutas aleatorias */
GRID_CONFIG *GG_create_grid() {
    GRID_CONFIG *grid = (GRID_CONFIG *) malloc(sizeof(GRID_CONFIG));
    grid->NxN = 8;
    grid->Width = 487;
    grid->Height = 88;
    grid->imgX = 48.5;
    grid->imgY = 46.5;
    grid->fruit_types = 5;
    grid->Score = 0;
    grid->Level = 1;
    /* Inicializa o grid com frutas aleatorias */
    grid->fruit = (GRID_FRUIT **) malloc(grid->NxN * sizeof(GRID_FRUIT *));
    for (int i = 0; i < grid->NxN; i++) {
        grid->fruit[i] = (GRID_FRUIT *) malloc(grid->NxN * sizeof(GRID_FRUIT));
        for (int j = 0; j < grid->NxN; j++) {
            grid->fruit[i][j] = *GG_create_fruit(grid);
            grid->fruit[i][j].x = i;
            grid->fruit[i][j].y = j;
        }
    }
    return grid;
}

/* Desenha o grid com suas frutas na tela */
void GG_draw_grid(GRID_CONFIG *grid, GAME_UI *junimo_ui) {
    for (int i = 0; i < grid->NxN; i++) {
        for (int j = 0; j < grid->NxN; j++) {
            al_draw_scaled_bitmap(junimo_ui->Image2, grid->fruit[i][j].type*18, 0, 18, 18, grid->Width+(i*grid->imgX), grid->Height+(j*grid->imgY), 43, 43, 0);
        }
    }
}

/* Libera a memoria utilizada pelo grid e pelas frutas */
void GG_destroy_grid(GRID_CONFIG *grid) {
    for (int i = 0; i < grid->NxN; i++) {
        free(grid->fruit[i]);
    }
    free(grid->fruit);
    free(grid);
}

/* Funcao que reconhece se o mouse clicou em alguma fruta do grid */
GRID_FRUIT *GG_check_click(GRID_CONFIG *grid, int mouseX, int mouseY) {
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
void GG_draw_mouse_selection(GRID_CONFIG *grid, GAME_UI *junimo_ui, GRID_FRUIT *fruit) {
    if (fruit != NULL) {
        int i = fruit->x;
        int j = fruit->y;
        al_draw_scaled_bitmap(junimo_ui->Image3, 0, 0, 18, 18, grid->Width+(i*grid->imgX), grid->Height+(j*grid->imgY)-2, 47, 46, 0);
    }
    return;
}

/* Troca duas frutas de posicao, e desenha a transicao entre elas */
void GG_draw_swap(GRID_CONFIG *grid, GAME_UI *junimo_ui, GRID_FRUIT *fruit1, GRID_FRUIT *fruit2) {
    /* Se as frutas sao iguais, ou estao a mais de uma posicao de distancia, nao faz nada */
    if (fruit1 == fruit2 || abs(fruit1->x - fruit2->x) > 1 || abs(fruit1->y - fruit2->y) > 1) {
        return;
    }
    /* Salva as cordenadas das frutas a fim de simplicidade */
    int F1_x = fruit1->x;
    int F1_y = fruit1->y;
    int F2_x = fruit2->x;
    int F2_y = fruit2->y;
    /* Decide quais as cordenadas que deverao ser afetadas pela animacao */
    int Swap_X1 = 0;
    int Swap_X2 = 0;
    int Swap_Y1 = 0;
    int Swap_Y2 = 0;
    /* Se as frutas estao na mesmsa linha */
    if (F1_x == F2_x) {
        /* Decide se a fruta 1 deve ser movida para cima ou para baixo */
        if (F1_y > F2_y) {
            Swap_Y1 = -1;
            Swap_Y2 = 1;
        } else {
            Swap_Y1 = 1;
            Swap_Y2 = -1;
        }
    /* Se as frutas estao na mesma coluna */
    } else if (F1_y == F2_y) {
        /* Decide se a fruta 1 deve ser movida para a esquerda ou para a direita */
        if (F1_x > F2_x) {
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
        al_draw_scaled_bitmap(junimo_ui->Image2, grid->fruit[fruit1->x][fruit1->y].type*18, 0, 18, 18, grid->Width+(fruit1->x*grid->imgX)+(i*Swap_X1), grid->Height+(fruit1->y*grid->imgY)+(i*Swap_Y1), 43, 43, 0);
        al_draw_scaled_bitmap(junimo_ui->Image2, grid->fruit[fruit2->x][fruit2->y].type*18, 0, 18, 18, grid->Width+(fruit2->x*grid->imgX)+(i*Swap_X2), grid->Height+(fruit2->y*grid->imgY)+(i*Swap_Y2), 43, 43, 0);
        al_flip_display();
    }
    /* Troca as frutas de lugar no grid */
    GRID_FRUIT temp = grid->fruit[F1_x][F1_y];
    grid->fruit[F1_x][F1_y] = grid->fruit[F2_x][F2_y];
    grid->fruit[F2_x][F2_y] = temp;
    /* Atualiza os valores de x e y das frutas */
    grid->fruit[F1_x][F1_y].x = F1_x;
    grid->fruit[F1_x][F1_y].y = F1_y;
    grid->fruit[F2_x][F2_y].x = F2_x;
    grid->fruit[F2_x][F2_y].y = F2_y;
    return;
}

/* Checa se a combinacoes de 3 ou mais frutas */
int GG_check_match(GRID_CONFIG *grid, GRID_FRUIT *fruit) {
    /* Se a fruta nao existe, retorna 0 */
    if (fruit == NULL) {
        return 0;
    }
    /* Salva as cordenadas da fruta */
    int x = fruit->x;
    int y = fruit->y;
    /* Salva o tipo da fruta */
    int type = fruit->type;
    /* Checa se ha 3 ou mais frutas do mesmo tipo na mesma linha */
    int match = 1;
    for (int i = x-1; i >= 0; i--) {
        if (grid->fruit[i][y].type == type) {
            match++;
        } else {
            break;
        }
    }
    for (int i = x+1; i < grid->NxN; i++) {
        if (grid->fruit[i][y].type == type) {
            match++;
        } else {
            break;
        }
    }
    /* Se houver 3 ou mais frutas do mesmo tipo na mesma linha, retorna 1 */
    if (match = 3) {
        return 1;
    }
    /* Checa se ha 3 ou mais frutas do mesmo tipo na mesma coluna */
    match = 1;
    for (int i = y-1; i >= 0; i--) {
        if (grid->fruit[x][i].type == type) {
            match++;
        } else {
            break;
        }
    }
    for (int i = y+1; i < grid->NxN; i++) {
        if (grid->fruit[x][i].type == type) {
            match++;
        } else {
            break;
        }
    }
    /* Se houver 3 ou mais frutas do mesmo tipo na mesma coluna, retorna 1 */
    if (match >= 3) {
        return 1;
    }
    /* Se nao houver 3 ou mais frutas do mesmo tipo na mesma linha ou coluna, retorna 0 */
    return 0;
}
   

/* Funcao principal do jogo, onde o loop principal e executado */
int GG_game_loop(GAME_STRUCT *main_body, GAME_UI *junimo_ui) {
    GRID_CONFIG *grid = GG_create_grid();
    GG_draw_menu(main_body, junimo_ui);
    GG_draw_grid(grid, junimo_ui);
    int exit = 0;
    int redraw = 0;
    GRID_FRUIT *selection1 = NULL;
    GRID_FRUIT *selection2 = NULL;

    int match1 = 0;
    int match2 = 0;
    /* Libera o timer para o loop principal */
    al_start_timer(main_body->Timer);
    while (!exit) {
        ALLEGRO_EVENT event;
        al_wait_for_event(main_body->Event, &event);

        /* Caso nada aconteca, o menu é redesenhado a cada 1/60 de segundo, para manter as animacoes */
        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = 1;
        }
        /* Caso o usuario clique no botao de fechar a janela, o jogo e encerrado */
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exit = 1;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            /* Checa se a primeira fruta ja foi selecionada ou nao, se sim, entao seleciona a fruta 2 */
            if (selection1 == NULL)
                selection1 = GG_check_click(grid, event.mouse.x, event.mouse.y);
            else if (selection2 == NULL)
                selection2 = GG_check_click(grid, event.mouse.x, event.mouse.y);
            /* Se as duas frutas ja foram selecionadas, entao realiza a troca */
            if (selection1 != NULL && selection2 != NULL) {
                GG_draw_swap(grid, junimo_ui, selection1, selection2);
                match1 = GG_check_match(grid, selection1);
                match2 = GG_check_match(grid, selection2);
                /* Se nenhuma das frutas formam combinacoes, entao troca de volta */
                if (!match1 && !match2) {
                    GG_draw_swap(grid, junimo_ui, selection1, selection2);
                }
                selection1 = NULL;
                selection2 = NULL;
            }
            redraw = 1;
        }

        if (redraw && al_is_event_queue_empty(main_body->Event)) {
            GG_draw_menu(main_body, junimo_ui);
            GG_draw_mouse_selection(grid, junimo_ui, selection1);
            GG_draw_mouse_selection(grid, junimo_ui, selection2);
            GG_draw_grid(grid, junimo_ui);
            al_flip_display();
            redraw = 0;
        }
    }
    /*--------------- Sair da tela de jogo ---------------*/
    al_clear_to_color(al_map_rgb(0, 0, 0));
    /* Limpa a memoria */
    GG_destroy_grid(grid);
    return exit;
}