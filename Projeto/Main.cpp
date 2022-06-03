#include <stdio.h>
#include <iostream>
#include "allegro5/allegro.h"
#include <allegro5/allegro_native_dialog.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"

using namespace std;

const float FPS = 60;
const int SCREEN_W = 964;//Tab Interno 630 = 21*30
const int SCREEN_H = 750;//Tab Interno x   = x*30

int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;

   ALLEGRO_EVENT_QUEUE *event_queue = NULL; //Fila de Eventos
   
   //Temporizador
   ALLEGRO_TIMER *timer = NULL;

   //Ponteiros de Audio
   //ALLEGRO_SAMPLE *sample=NULL, *sample2=NULL;
   //ALLEGRO_SAMPLE_INSTANCE *instance = NULL, *instance2 = NULL;

   float darth_x = 165;
   float darth_y = 60;

   int darthL = 30, darthA = 30;//Largura e Altura

   //Vetor de Teclas
   bool teclas[255] = {false};
      

   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   if (!al_init_image_addon()) {
       al_show_native_message_box(display, "Error", "Error", "Falha ao iniciar o al_init_image_addon!",
           NULL, ALLEGRO_MESSAGEBOX_ERROR);
       return 0;
   }


   al_install_keyboard();//Funcoes Teclado
   al_init_image_addon();//Imagens
   al_init_font_addon();//Font
   al_init_ttf_addon();//Arquivo ttf

   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
   
   //Funcoes de Audio
   /*al_install_audio();
   al_init_acodec_addon();
   al_reserve_samples(2);//Quantidade de Audios
	
   sample = al_load_sample( "imperial_march.wav" );
   sample2 = al_load_sample( "vader.wav" );

   instance = al_create_sample_instance(sample);
   instance2 = al_create_sample_instance(sample2);

   al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());
   al_attach_sample_instance_to_mixer(instance2, al_get_default_mixer());

   if (!sample){
      printf( "Audio clip sample not loaded!\n" ); 
      return -1;
   }

   if (!sample2){
      printf( "Audio clip sample not loaded!\n" ); 
      return -1;
   }*/

   //Tela
   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }

   //Imagem

   ALLEGRO_BITMAP* image = NULL; //Imagem

   image = al_load_bitmap("src/Images/mapa.png");

   if (!image) {
       fprintf(stderr, "failed to create image bitmap!\n");
       al_destroy_display(display);
       al_destroy_timer(timer);
       return -1;
   }

   al_draw_bitmap(image, 0, 0, 0); //Desenha a imagem

   ALLEGRO_FONT* font20 = al_load_font("src/Fonts/Roboto-Regular.ttf", 20, NULL);

   ALLEGRO_BITMAP  *darth;

   darth = al_load_bitmap("src/Images/pacman.png");//200x600
   if(!darth) {
      fprintf(stderr, "failed to create darth bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
   //al_draw_bitmap(darth, darth_x, darth_y, 0);
   al_draw_bitmap_region(darth, 0, 0, darthL, darthA, darth_x, darth_y, 0);

   /* Explicacao da Funcao - Desenha apenas uma regiao da imagem
   void al_draw_bitmap_region(ALLEGRO_BITMAP *bitmap,float sx, float sy, float sw, float sh, float dx, float dy, int flags)
	 Draws a region of the given bitmap to the target bitmap.
		sx - x da regiao na imagem
		sy - y da regiao na imagem
		sw - Largura da regiao na imagem
		sh - Altura da regiao na imagem
		dx - posicao x na tela
		dy - posicao y na tela
   */


   //Eventos
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(darth);
      al_destroy_bitmap(image);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   al_register_event_source(event_queue, al_get_display_event_source(display));//Evento da Tela

   al_register_event_source(event_queue, al_get_timer_event_source(timer));//Evento de tempo

   al_register_event_source(event_queue, al_get_keyboard_event_source());//Evento de Teclado

   



   al_start_timer(timer);
   //al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

   bool re_desenha = true;
   bool termina = false;

   bool teclaD = true;//So para Desenhar o DarthVader sempre

   int sprite = 0, fator = 1;
   int tempo, miliseg = 200;

   bool top = false;
   bool right = false;
   bool booton = false;
   bool left = false;
   int lado = 0;

   while(!termina)
   {
      //printf("%.2f %.2f\n", darth_x, darth_y);
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
      
      tempo = al_get_timer_count(timer);

      if(ev.type == ALLEGRO_EVENT_TIMER) {
        
        if(tempo == (FPS*miliseg)/1000) {//Quando tempo == FPS equivale a 1 segundo, assim a cada x milisegundos ele muda a sprite
           al_set_timer_count(timer, 0);//Volta ao tempo 0
           sprite = sprite + fator; //0 1 2 3 2 1 0     
           if(sprite == 0) fator = 1;
           if(sprite == 2) fator = -1;
        } 

        
        

	/*if (teclas[ALLEGRO_KEY_O]) {
	   al_stop_sample_instance(instance);
	}   
	if(teclas[ALLEGRO_KEY_I]){
	   al_play_sample_instance(instance);
	}	
    */
	if (teclas[ALLEGRO_KEY_D] && !teclaD) {
	   teclaD = true;
	   //al_play_sample(sample2, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);//al_play_sample_instance(instance2);
	}
    if (teclas[ALLEGRO_KEY_UP])
    {
        top = true;
        booton = false;
        left = false;
        right = false;
        lado = 3;
    }
    if (teclas[ALLEGRO_KEY_DOWN])
    {
        booton = true;
        top = false;
        left = false;
        right = false;
        lado = 1;
    }
    if (teclas[ALLEGRO_KEY_LEFT])
    {
        left = true;
        top = false;
        booton = false;
        right = false;
        lado = 2;
    }
    if (teclas[ALLEGRO_KEY_RIGHT])
    {
        right = true;
        top = false;
        booton = false;
        left = false;
        lado = 0;
    }
	    if(top == true && darth_y >= 60) {
            darth_y -= 2.0;
        }

         if(booton == true && darth_y <= 680 - darthA) {
            darth_y += 2.0;
         }

         if(left == true && darth_x >= 165) {
            darth_x -= 2.0; 
         }

         if(right == true && darth_x <= 795 - darthL) {

            darth_x += 2.0;
         }

         re_desenha = true;
      }

      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { //Tecla X Apertada
        teclas[ev.keyboard.keycode] = true;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) { //Tecla X Liberada
         teclas[ev.keyboard.keycode] = false;
         
         if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) 
	        termina = true;
      }

      if(re_desenha && al_is_event_queue_empty(event_queue)) { //Redesenha se a fila de eventos esta vazia
         re_desenha = false;
         //Limpa a tela e Redesenha
         al_clear_to_color(al_map_rgb(0,0,100));
	 if(teclaD)
            //al_draw_bitmap(darth, darth_x, darth_y, 0);
            al_draw_bitmap(image, 0, 0, 0);
            al_draw_bitmap_region(darth, lado*darthL, sprite*darthA, darthL, darthA, darth_x, darth_y, 0);

         al_flip_display();
      }
      al_draw_text(font20, al_map_rgb(255, 0, 0), 50, 50, NULL, "Ola Mundo");
   }

   //Destroi componentes

   al_destroy_bitmap(darth);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_bitmap(image); //Destroi a imagem
   //al_destroy_sample(sample);
   //al_destroy_sample_instance(instance);
   //al_destroy_sample(sample2);
   //al_destroy_sample_instance(instance2);
   al_destroy_event_queue(event_queue);

   return 0;
}
