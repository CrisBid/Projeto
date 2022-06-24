#include <stdio.h>
#include <iostream>
#include <malloc.h>
#include "allegro5/allegro.h"
#include <allegro5/allegro_native_dialog.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
//#include "Codigo/Tijolinho.h"
#include "Codigo/Mapa.h"
#include "Codigo/Matriz.h"
#include "Codigo/Display.h"
#include "Codigo/Pacman.h"
#include "Codigo/Placar.h"

#include <math.h>

using namespace std;

const float FPS = 30;
const int SCREEN_W = 964;//Tab Interno 630 = 21*30
const int SCREEN_H = 750;//Tab Interno x   = x*30


int main() {

    Matriz CMatriz;

    Mapa mapa;

    Pacman player;

    Placar atualPlacar;

    Display Tela;

    sMatriz *ptrmatriz = NULL;

    ptrmatriz = (sMatriz*)malloc(sizeof(sMatriz));
    if (ptrmatriz)
    {
        CMatriz.loadFileMatriz();

        *ptrmatriz = CMatriz.getMatriz();
    }
    else
    {
        printf("Erro na alocacao");
        free(ptrmatriz);
        exit(1);
    }

    ALLEGRO_EVENT_QUEUE* event_queue = NULL; //Fila de Eventos
    ALLEGRO_TIMER* timer = NULL;//Timer
    ALLEGRO_BITMAP* image;

    float darth_x = 160;
    float darth_y = 60;

    //Vetor de Teclas
    bool teclas[255] = { false };

    if (!al_init()) {
        fprintf(stderr, "Falha ao inicial Allegro!\n");
        return -1;
    }
    al_init_image_addon();//Função de Imagem
    al_install_keyboard();//Funcoes Teclado

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }


    Tela.setDisplay(SCREEN_W, SCREEN_H); // 21- 31

    image = al_load_bitmap("Images/mapa.png");

    mapa.setMapa(ptrmatriz);

    ALLEGRO_BITMAP* darth;
    int darthL = 30, darthA = 30;//Largura e Altura
    darth = al_load_bitmap("Images/Poro/Poro 1.png");//200x600
    if (!darth) {
        fprintf(stderr, "Falha ao Criar Personagem\n");
        Tela.~Display();
        al_destroy_timer(timer);
        return -1;
    }

    player.desenhaPacman();
    //al_draw_bitmap_region(darth, 0, 0, darthL, darthA, darth_x, darth_y, 0);

    //Eventos
    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_bitmap(darth);
        Tela.~Display();
        al_destroy_timer(timer);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(Tela.getDisplay()));//Evento da Tela

    al_register_event_source(event_queue, al_get_timer_event_source(timer));//Evento de tempo

    al_register_event_source(event_queue, al_get_keyboard_event_source());//Evento de Teclado

    al_start_timer(timer);

    bool re_desenha = true;
    bool termina = false;

    int sprite = 0, fator = 1;
    int tempo, miliseg = 200;

    int placar = 0;
    int proximaIntrucao = 0;
    
    bool colisaoR = false;
    bool colisaoL = false;
    bool colisaoT = false;
    bool colisaoB = false;

    bool espacoLivre = true;
    bool espacoLivreR = true;
    bool espacoLivreL = true;
    bool espacoLivreT = true;
    bool espacoLivreB = true;

    int colisaoXR = 0;
    int colisaoYR = 0;
    int colisaoXL = 0;
    int colisaoYL = 0;
    int colisaoXT = 0;
    int colisaoYT = 0;

    int colisaoYPirula = 0;
    int colisaoXPirula = 0;

    int colisaoYC = 0;
    int colisaoXC = 0;
    int colisaoYCN = 0;
    int colisaoXCN = 0;

    int colisaoYE = 0;
    int colisaoXE = 0;
    int colisaoYEN = 0;
    int colisaoXEN = 0;

    int colisaoYD = 0;
    int colisaoXD = 0;
    int colisaoYDN = 0;
    int colisaoXDN = 0;

    int colisaoXB = 0;
    int colisaoYB = 0;
    int colisaoXBN = 0;
    int colisaoYBN = 0;

    bool top = false;
    bool right = false;
    bool bottom = false;
    bool left = false;
    int lado = 0;


    while (!termina)
    {

        player.posicaoPacman();
        player.colisaoPacmanPirula(ptrmatriz);

        atualPlacar.set_placar(player.getAtualPlacar());
        
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        tempo = al_get_timer_count(timer);

        if (ev.type == ALLEGRO_EVENT_TIMER) {

            //Timer para trocar o bitmap
            if (tempo == (FPS * miliseg) / 1000) {
                al_set_timer_count(timer, 0);
                sprite = sprite + fator;    
                if (sprite == 0) fator = 1;
                if (sprite == 2) fator = -1;
            }

            //Recebe o comando e guarda ele na variavel ate q ele seja possivel de ser executado

            if (teclas[ALLEGRO_KEY_UP])
            {
                proximaIntrucao = ALLEGRO_KEY_UP;
            }
            if (teclas[ALLEGRO_KEY_DOWN])
            {
                proximaIntrucao = ALLEGRO_KEY_DOWN;
            }
            if (teclas[ALLEGRO_KEY_LEFT])
            {
                proximaIntrucao = ALLEGRO_KEY_LEFT;
            }
            if (teclas[ALLEGRO_KEY_RIGHT])
            {
                proximaIntrucao = ALLEGRO_KEY_RIGHT;
            }

            //Verifica se o camando pode ser executado e define as variaveis para que isso aconteça

            //Top
            if (proximaIntrucao == ALLEGRO_KEY_UP && player.colisaoPacmanTop(ptrmatriz) == true)
            {
                top = true;
                bottom = false;
                left = false;
                right = false;
                lado = 3;
            }
            //Bottom
            if (proximaIntrucao == ALLEGRO_KEY_DOWN && player.colisaoPacmanBottom(ptrmatriz) == true)
            {
                bottom = true;
                top = false;
                left = false;
                right = false;
                lado = 1;
            }
            if (proximaIntrucao == ALLEGRO_KEY_LEFT && player.colisaoPacmanLeft(ptrmatriz) == true)
            {
                left = true;
                top = false;
                bottom = false;
                right = false;
                lado = 2;
            }
            if (proximaIntrucao == ALLEGRO_KEY_RIGHT && player.colisaoPacmanRight(ptrmatriz) == true)
            {
                right = true;
                top = false;
                bottom = false;
                left = false;
                lado = 0;
            }

            //Executa a movimentação

            if (top == true && player.colisaoPacmanTop(ptrmatriz) == true) { //Movimetação para Cima
                player.setPacmanY(player.getPacmanY() - 2.0);
                //darth_y -= 2.0;
            }

            if (bottom == true && player.colisaoPacmanBottom(ptrmatriz) == true) { //Movimentação para Baixo
                player.setPacmanY(player.getPacmanY() + 2.0);
                //darth_y += 2.0;
            }

            if (left == true && player.colisaoPacmanLeft(ptrmatriz) == true) { //Movimentação para Esquerda
                player.setPacmanX(player.getPacmanX() - 2.0);
                //darth_x -= 2.0;
            }

            if (right == true && player.colisaoPacmanRight(ptrmatriz) == true) { //Movimentação para Direita
                player.setPacmanX(player.getPacmanX() + 2.0);
                //darth_x += 2.0;
            }

            re_desenha = true;
        }

        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            teclas[ev.keyboard.keycode] = true;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            teclas[ev.keyboard.keycode] = false;
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                termina = true;

        }

        if (re_desenha && al_is_event_queue_empty(event_queue)) { //Redesenha se a fila de eventos esta vazia
            re_desenha = false;
            //Limpa a tela e Redesenha
            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_bitmap(image, 0, 0, 0); //Desenha a imagem de fundo

            //Chamada dos elemtos do mapa
            mapa.~Mapa(); //Destrutor dos elemtos do mapa
            mapa.setMapa(ptrmatriz); //Contrutor dos elemtos do mapa

            atualPlacar.desenhaPlacar();

            //Desenha o pacman
            player.~Pacman();
            player.desenhaPacman();

            //al_draw_bitmap_region(player.getPacman() , /*lado**/0, /*sprite**/0, 30, 30, player.getPacmanX(), player.getPacmanY(), 0);

            //al_draw_bitmap_region(darth, /*lado**/0 * darthL, /*sprite**/0* darthA, darthL, darthA, darth_x, darth_y, 0);

            al_flip_display();
        }
    }

    free(ptrmatriz); //Desaloca o ponteiro que aponta para a matriz
    al_destroy_bitmap(darth); //Destroi o Pacaman
    al_destroy_timer(timer); //Destroi o Timer
    al_destroy_bitmap(image); //Destroi a Imagem
    al_destroy_event_queue(event_queue); //Destroi a Fila de Eventos


    return 0;
}
