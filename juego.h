#pragma once
#include "math.h"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "SFML\System.hpp"
#include "bala.h"
#include "zombie.h"
#include "survivor.h"
#include "Collision.h"
using namespace sf;



class juego
{
public:
	juego(Vector2f resolucion, String titulo);
	void gameloop(Vector2f);
	void cargar_graficos(Vector2f);
	void cargar_sonidos();
	void procesar_eventos();
	//void procesar_eventos_joystick();
	void cargar_fuentes();
	void cargar_intro();
	void cargar_menu();
private:

	RenderWindow* ventana1;
	Clock* reloj1;
	Time* tiempo1;
	float tiempo2;
	float fps;

	///Sprites and textures
	/*
	Texture text_survivor;
	Sprite spr_survivor;
	*/
	Texture text_fondo;
	Sprite spr_fondo;

	Texture text_mira;
	Sprite spr_mira;
	/*
	Texture text_survirordisp;
	Sprite spr_survivordisp;
	*/
	///Sounds
	SoundBuffer BuffDisparo;
	Sound sonidoDisparo;
	Music cancion_menu;
	Music cancion_juego;
	//intro
	Texture text_intro1;
	Sprite spr_intro1;

	//blanco
	Texture text_blanco;
	Sprite spr_blanco;

	///fuentes
	Font zombiefont;
	Text titulo_intro;
	Text titulo_enter;

	///Event
	Event* eventos;

	///Bala
	//bala* bala1;

	bool game_over;
	//int fps;
	
};