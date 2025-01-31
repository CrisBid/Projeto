﻿#include "Aleatorios.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include<time.h>

using namespace std;

Aleatorios::Aleatorios()
{
    inimigo = NULL;

    //Altura e Largura da Sprite
    inimigos_altura = 30;
    inimigos_largura = 30;

    //Variaveis de Dire��o
    top = false;
    right = false;
    bottom = false;
    left = false;
    lado = 0;

    //Variaveis de Randomiza��o

    for (size_t i = 0; i < 2; i++)
    {
        opcao3[i] = 0;
    }

    aleatorio2 = 0;
    aleatorio3 = 0;

    Instrucao = 0;

}

Aleatorios::Aleatorios(int x, int y) :Inimigos(x, y)
{
    inimigo = NULL;

    //Altura e Largura da Sprite
    inimigos_altura = 30;
    inimigos_largura = 30;

    //Variaveis de Dire��o
    top = false;
    right = false;
    bottom = false;
    left = false;
    lado = 0;

    //Variaveis de Randomiza��o

    for (size_t i = 0; i < 2; i++)
    {
        opcao3[i] = 0;
    }

    aleatorio2 = 0;
    aleatorio3 = 0;

    Instrucao = 0;


}

void Aleatorios::posicaoInimigos() {
    Inimigos::posicaoPlayer();
}

bool Aleatorios::colisaoInimigos(sMatriz* matriz) {
    return Inimigos::colisaoPlayer(matriz);
}

bool Aleatorios::colisaoInimigosTop(sMatriz* matriz) {
    return Inimigos::colisaoPlayerTop(matriz);
}
bool Aleatorios::colisaoInimigosBottom(sMatriz* matriz) {
    return Inimigos::colisaoPlayerBottom(matriz);
}
bool Aleatorios::colisaoInimigosRight(sMatriz* matriz) {
    return Inimigos::colisaoPlayerRight(matriz);
}
bool Aleatorios::colisaoInimigosLeft(sMatriz* matriz) {
    return Inimigos::colisaoPlayerLeft(matriz);
}

float Aleatorios::getInimigosX() {
    return Inimigos::getPlayerX();
}
float Aleatorios::getInimigosY() {
    return Inimigos::getPlayerY();
}
void Aleatorios::setInimigosX(float x) {
    Inimigos::setPlayerX(x);
}
void Aleatorios::setInimigosY(float y) {
    Inimigos::setPlayerY(y);
}

void Aleatorios::sorteioDirecao(sMatriz* matriz, float pacX, float pacY) {

    int flag = 0;
    int posibilidades = 0;

    int direcoes[4];

    for (int i = 0; i < 4; i++)
    {
        direcoes[i] = 0;
    }

    if (left == true)
    {

        //Left
        if (colisaoInimigosLeft(matriz) == true)
        {
            direcoes[posibilidades] = ALLEGRO_KEY_LEFT;
            posibilidades++;
        }
        //Top
        if (colisaoInimigosTop(matriz) == true)
        {
            direcoes[posibilidades] = ALLEGRO_KEY_UP;
            posibilidades++;
        }
        //Botton
        if (colisaoInimigosBottom(matriz) == true)
        {
            direcoes[posibilidades] = ALLEGRO_KEY_DOWN;
            posibilidades++;
        }

        srand(time(NULL));

        if (posibilidades > 0)
        {
            flag = rand() % posibilidades;

            Instrucao = direcoes[flag];
        }

    }

    else if (right == true)
    {

        //Right
        if (colisaoInimigosRight(matriz) == true)
        {
            direcoes[posibilidades] = ALLEGRO_KEY_RIGHT;
            posibilidades++;
        }
        //Top
        if (colisaoInimigosTop(matriz) == true)
        {
            direcoes[posibilidades] = ALLEGRO_KEY_UP;
            posibilidades++;
        }
        //Botton
        if (colisaoInimigosBottom(matriz) == true)
        {
            direcoes[posibilidades] = ALLEGRO_KEY_DOWN;
            posibilidades++;
        }

        srand(time(NULL));

        if (posibilidades > 0)
        {
            flag = rand() % posibilidades;

            Instrucao = direcoes[flag];
        }

    }

    else if (top == true)
    {

        //Left
        if (colisaoInimigosLeft(matriz) == true)
        {
            direcoes[posibilidades] =  ALLEGRO_KEY_LEFT;
            posibilidades++;
        }
        //Right
        if (colisaoInimigosRight(matriz) == true)
        {
            direcoes[posibilidades] = ALLEGRO_KEY_RIGHT;
            posibilidades++;
        }
        //Top
        if (colisaoInimigosTop(matriz) == true)
        {
            direcoes[posibilidades] = ALLEGRO_KEY_UP;
            posibilidades++;
        }

        srand(time(NULL));

        if (posibilidades > 0)
        {
            flag = rand() % posibilidades;

            Instrucao = direcoes[flag];
        }
        
    }

    else if (bottom == true)
    {

        //Left
        if (colisaoInimigosLeft(matriz) == true)
        {
            direcoes[posibilidades] = ALLEGRO_KEY_LEFT;
            posibilidades++;
        }
        //Right
        if (colisaoInimigosRight(matriz) == true)
        {
            direcoes[posibilidades] = ALLEGRO_KEY_RIGHT;
            posibilidades++;
        }
        //Botton
        if (colisaoInimigosBottom(matriz) == true)
        {
            direcoes[posibilidades] = ALLEGRO_KEY_DOWN;
            posibilidades++;
        }

        srand(time(NULL));

        if (posibilidades > 0)
        {
            flag = rand() % posibilidades;

            Instrucao = direcoes[flag];
        }

    }

    else
    {
        //Left
        if (colisaoInimigosLeft(matriz) == true)
        {
            direcoes[posibilidades] = ALLEGRO_KEY_LEFT;
            posibilidades++;
        }
        //Right
        if (colisaoInimigosRight(matriz) == true)
        {
            direcoes[posibilidades] = ALLEGRO_KEY_RIGHT;
            posibilidades++;
        }
        //Top
        if (colisaoInimigosTop(matriz) == true)
        {
            direcoes[posibilidades] = ALLEGRO_KEY_UP;
            posibilidades++;
        }
        //Botton
        if (colisaoInimigosBottom(matriz) == true)
        {
            direcoes[posibilidades] = ALLEGRO_KEY_DOWN;
            posibilidades++;
        }

        srand(time(NULL));

        if (posibilidades > 0)
        {
            flag = rand() % posibilidades;

            Instrucao = direcoes[flag];
        }
        

    }
    
   /*

    int direcoesLeft[] = { ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_LEFT };

    int direcoesRight[] = { ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_RIGHT };

    int direcoesTop[] = { ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_UP };

    int direcoesBottom[] = { ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_DOWN };

    int flag = 0;

    srand(time(NULL));

    flag = rand() % 4;

    Instrucao = direcoes[flag];

    */

}

void Aleatorios::movimentacaoInimigos(sMatriz* matriz) {
    //Verifica se o camando pode ser executado e define as variaveis para que isso aconte�a

    //Top
    if (Instrucao == ALLEGRO_KEY_UP && colisaoInimigosTop(matriz) == true && bottom != true && top != true)
    {
        top = true;
        bottom = false;
        left = false;
        right = false;
        lado = 2;
    }
    //Bottom
    if (Instrucao == ALLEGRO_KEY_DOWN && colisaoInimigosBottom(matriz) == true && top != true && bottom != true)
    {
        bottom = true;
        top = false;
        left = false;
        right = false;
        lado = 3;
    }
    //Left
    if (Instrucao == ALLEGRO_KEY_LEFT && colisaoInimigosLeft(matriz) == true && right != true && left != true)
    {
        left = true;
        top = false;
        bottom = false;
        right = false;
        lado = 1;
    }
    //Right
    if (Instrucao == ALLEGRO_KEY_RIGHT && colisaoInimigosRight(matriz) == true && left != true && right != true)
    {
        right = true;
        top = false;
        bottom = false;
        left = false;
        lado = 0;
    }
}

void Aleatorios::execusaoMovInimigos(sMatriz* matriz, bool status) {

    if (status == false)
    {
        //Executa a movimenta��o

        if (top == true && colisaoInimigosTop(matriz) == true) { //Movimeta��o para Cima
            setInimigosY(getInimigosY() - 2.0);
            //darth_y -= 2.0;
        }

        if (bottom == true && colisaoInimigosBottom(matriz) == true) { //Movimenta��o para Baixo
            setInimigosY(getInimigosY() + 2.0);
            //darth_y += 2.0;
        }

        if (left == true && colisaoInimigosLeft(matriz) == true) { //Movimenta��o para Esquerda
            setInimigosX(getInimigosX() - 2.0);
            //darth_x -= 2.0;
        }

        if (right == true && colisaoInimigosRight(matriz) == true) { //Movimenta��o para Direita
            setInimigosX(getInimigosX() + 2.0);
            //darth_x += 2.0;
        }
    }
}

void Aleatorios::desenhaInimigos(int sprite, int tipo) {
    inimigo = al_load_bitmap("Images/Teemo/TeemoSprite.png");

    al_draw_bitmap_region(inimigo, tipo * inimigos_largura, 0 * inimigos_altura, inimigos_largura, inimigos_altura, Inimigos::getPlayerX(), Inimigos::getPlayerY(), 0);
}

ALLEGRO_BITMAP* Aleatorios::getInimigos() {
    return inimigo;
}

void Aleatorios::Destrutor()
{
    al_destroy_bitmap(inimigo); //Destroi a tela
}


Aleatorios::~Aleatorios()
{
    al_destroy_bitmap(inimigo); //Destroi a tela
}

