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

#define CANT_OPCIONES_MENU 3
#define CANT_ZOMBIES 5
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

	//dibujar menu
	void menu_dibujar_principal();
    void menu_dibujar_pressenter();
	void menu_dibujar_escribirNombre();
	void menu_dibujar_efectoblanco(IntRect, IntRect , IntRect);
	// / / / / / ***** \ \ \ \ \ \ \

	juego(Vector2f resolucion, String titulo);
	void gameloop(Vector2f);
	void cargar_graficos(Vector2f);
	void cargar_sonidos();
	void procesar_eventos();
	void cargar_fuentes();
	void cargar_intro();
	void cargar_menu();
	Font get_scaryfont() { return scaryfont; }
	

private:
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
	Text titulo_enter;
	Text text_ronda;
	Text text_jugar;
	Text text_score;
	Text text_salir;
	Text menutext[CANT_OPCIONES_MENU];
	Text hasMuerto;

	String playerInput;
	Text playername;
	///Event
	Event* eventos;
	
	///game over
	bool game_over = false;
	///menu loop
	bool menuloop = true;
};