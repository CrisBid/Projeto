#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include "Tijolinho.h"

#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;

Tijolinho::Tijolinho() {

	//Iniciali��o do objeto dos Tijolos
	tijolo = NULL;
	tijolo = al_load_bitmap("Images/bloco.png");
	if (!tijolo) {
		printf("ERRO NO BLOCO");
	}
	else {
		printf("\nBloco criado com sucesso\n");
	}
}



void Tijolinho::setTijolos(sMatriz *matriz) {
	for (int i = 0; i < matriz->matriz_altura; i++) //Cri��o do mapa a partir da matriz
	{
		for (int j = 0; j < matriz->matriz_largura; j++)
		{
			if (matriz->dados_matriz[i][j]==1)
			{
				//al_draw_bitmap(blocopng, 130+(10 * j), 60+(10 * i), 0);
				al_draw_bitmap_region(tijolo, 0, 0, 10, 10, 150 + (10 * j), 50 + (10 * i), 0);
			}
		}
	}
	al_flip_display();

}
 
Tijolinho::~Tijolinho() {
	al_destroy_bitmap(tijolo);// destroi os tijolos
}
