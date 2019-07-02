#pragma once
#include<iostream>
#include "math.h"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "SFML\System.hpp"
#include "menu.h"
#include "score.h"
#include "bala.h"
#include "zombie.h"
#include "survivor.h"
#include "Collision.h"
#include <vector>
#include "zombie.h"
#include <string>

#define CANT_OPCIONES_MENU 3
#define CANT_ZOMBIES 3
#define CANT_DIFICULTAD 3
#define CANT_TEXT_RANKING 6


using namespace sf;
using namespace std;


class juego
{
public:
	//MENU
	void menu_pressenter(Vector2f);
	void menu_escribirNombre(Vector2f);
	void menu_principal(Vector2f);
	void menu_ranking();
	void menu_dificultad(Vector2f);

	//dibujar menu
	void menu_dibujar_principal();
	void menu_dibujar_pressenter();
	void menu_dibujar_game_over();
	void menu_dibujar_escribirNombre();
	void menu_dibujar_efectoblanco(IntRect, IntRect, IntRect);
	void menu_dibujar_efectoblanco_dificulad(IntRect, IntRect, IntRect);
	void menu_dibujar_dificultad();
	void menu_dibujar_ranking(IntRect);
	// / / / / / ***** \ \ \ \ \ \ \

	juego(Vector2f resolucion, String titulo);
	void gameloop(Vector2f, int);
	void cargar_graficos(Vector2f);
	void cargar_sonidos();
	void procesar_eventos();
	void cargar_fuentes();
	void cargar_intro();
	void cargar_menu();
	Font get_scaryfont() { return scaryfont; }

	///func general
	score* ordenar_ranking() 
	{
		score obj, * vecobj, aux;
		int posy = 40;
		int pos = 0, cantreg = 0, i=0, j, posmin;
		while (obj.leerdedisco(pos++)) cantreg++;
		vecobj = new score[cantreg];
		pos = 0;
		while (obj.leerdedisco(pos++))
		{
			vecobj[i] = obj;
			i++;
		}

		for (i = 0; i < cantreg - 1; i++) {
			posmin = i;
			for (j = i + 1; j < cantreg; j++)
			{
				if (vecobj[j] > vecobj[posmin])
				{
					posmin = j;
				}
				aux = vecobj[i];
				vecobj[i] = vecobj[posmin];
				vecobj[posmin] = aux;
			}
		}

		ventana1->display();

		return vecobj;
	}


	void mostrar_vector(score* vecobj)
	{
		int posy = 40;
		score obj;
		int pos = 0, cantreg = 0, i;
		while (obj.leerdedisco(pos++)) cantreg++;
		for (i = 0; i < cantreg; i++)
		{

			txt_jugadores[0].setPosition(Vector2f(50, posy));
			txt_jugadores[1].setPosition(Vector2f(100, posy));
			txt_jugadores[2].setPosition(Vector2f(200, posy));
			txt_jugadores[3].setPosition(Vector2f(300, posy));
			txt_jugadores[4].setPosition(Vector2f(400, posy));
			txt_jugadores[5].setPosition(Vector2f(500, posy));

			txt_jugadores[0].setString(to_string(i + 1));
			txt_jugadores[1].setString(vecobj[i].get_nombre());
			txt_jugadores[2].setString(to_string(vecobj[i].get_rondas()));
			txt_jugadores[3].setString(to_string(vecobj[i].get_tiros()));
			txt_jugadores[4].setString(to_string(vecobj[i].get_tirosacertados()));
			txt_jugadores[5].setString(to_string(vecobj[i].get_accuracy()));
			
			ventana1->draw(txt_jugadores[0]);
			ventana1->draw(txt_jugadores[1]);
			ventana1->draw(txt_jugadores[2]);
			ventana1->draw(txt_jugadores[3]);
			ventana1->draw(txt_jugadores[4]);
			ventana1->draw(txt_jugadores[5]);

			posy += 40;
		}
	}
private:
	score ranking;
	RenderWindow* ventana1;
	Event clickearMenu;
	Clock* reloj1;
	Time* tiempo1;
	float tiempo2;
	float fps;
	///rank
	score rank;

	///Sprites and textures
	Texture text_fondo;
	Sprite spr_fondo;

	Texture text_fondoarbol;
	Sprite spr_fondoarbol;

	Texture text_mira;
	Sprite spr_mira;

	Texture text_puntero1;
	Sprite spr_puntero1;

	Texture text_puntero2;
	Sprite spr_puntero2;

	///Sounds
	SoundBuffer BuffDisparo;
	Sound sonidoDisparo;
	Music cancion_menu;
	Music cancion_juego;
	SoundBuffer BuffendRound;
	Sound Sonido_endRound;
	///intro
	Texture text_intro1;
	Sprite spr_intro1;

	///blanco
	Texture text_blanco;
	Sprite spr_blanco;

	///fuentes
	Font zombiefont;
	Font scaryfont;
	///textos
	Text titulo_intro;
	Text titulo_ingrese_nombre;
	Text titulo_game_over;
	Text titulo_creators;
	Text titulo_enter;
	Text text_ronda;
	Text text_jugar;
	Text text_score;
	Text text_salir;
	Text menutext [CANT_OPCIONES_MENU];
	Text text_dif [CANT_DIFICULTAD];
	Text txt_rank[CANT_TEXT_RANKING];
	Text hasMuerto;
	Text text_atras;
	Text text_selecdif;
	Text txt_jugadores[6];

	string playerInput;

	Text playername;
	
	///Event
	Event* eventos;
	
	///game over
	bool game_over = false;
	///menu loop
	bool menuloop = true;
};