#include "juego.h"
#include "survivor.h"
#include <iostream>
#include <SFML/Audio.hpp>

/*
SoundBuffer BuffDisparo;
BuffDisparo.loadFromFile("sonidos/shot.wav");
Sound sonidoDisparo;
sonidoDisparo.setBuffer(BuffDisparo);
sonidoDisparo.play();
*/

using namespace std;
bool jugadorUp, jugadorDown, jugadorRight, jugadorLeft;
Vector2i mouse;
float angle;
Vector2f survPos,survDispPos;
float a, b;


juego::juego(Vector2f resolucion, String titulo)
{
	
	game_over = false;
	eventos = new Event;

	fps = 144;

	ventana1 = new RenderWindow (VideoMode(resolucion.x, resolucion.y), titulo);
	ventana1->setFramerateLimit(fps);
	ventana1->setMouseCursorVisible(false);
	cargar_graficos();

	///cargo intro
	Music cancion;
	cancion.openFromFile("sonidos/cancion.wav");
	cancion.play();

	gameloop();
}

void juego::gameloop()
{
	survivor jugadorObj;
	spr_survivor.setRotation(0);
	spr_survivordisp.setRotation(0);
	while (!game_over)
	{

		ventana1->clear();

		procesar_eventos();
		
		survDispPos;
		///survivor sigue al mouses
		survPos = spr_survivor.getPosition();
		a = survPos.x - mouse.x;
		b = survPos.y - mouse.y;

		mouse = Mouse::getPosition(*ventana1);
		angle = (-atan2(a, b) * 180 / 3.14) - 97;
		spr_survivor.setRotation(angle);

		///survivor dispara con mouse
	
		spr_survivordisp.setRotation(angle);



		ventana1->draw(spr_fondo);
		ventana1->draw(spr_survivordisp);
		//spr_survirordisp.setColor(Color::Transparent);
		ventana1->draw(spr_mira);
		ventana1->draw(spr_survivor);
		ventana1->display();
		if (Keyboard::isKeyPressed(Keyboard::W)) { jugadorUp = true; }
		if (!Keyboard::isKeyPressed(Keyboard::W)) { jugadorUp = false; }
		if (Keyboard::isKeyPressed(Keyboard::S)) { jugadorDown = true; }
		if (!Keyboard::isKeyPressed(Keyboard::S)) { jugadorDown = false; }
		if (Keyboard::isKeyPressed(Keyboard::D)) { jugadorRight = true; }
		if (!Keyboard::isKeyPressed(Keyboard::D)) { jugadorRight = false; }
		if (Keyboard::isKeyPressed(Keyboard::A)) { jugadorLeft = true; }
		if (!Keyboard::isKeyPressed(Keyboard::A)) { jugadorLeft = false; }
		jugadorObj.update(jugadorUp, jugadorDown, jugadorRight, jugadorLeft);
		spr_survivor.move(Vector2f(jugadorObj.get_xvel(), jugadorObj.get_yvel()));
		spr_survivordisp.move(Vector2f(jugadorObj.get_xvel(), jugadorObj.get_yvel()));


	}

}

void juego::cargar_graficos()
{

	

	text_fondo.loadFromFile("imagenes/fondo.jpg");
	spr_fondo.setTexture(text_fondo);
	spr_fondo.setScale((float)ventana1->getSize().x / text_fondo.getSize().x, (float)ventana1->getSize().y / text_fondo.getSize().y);
	text_mira.loadFromFile("imagenes/crosshair.png");
	spr_mira.setTexture(text_mira);

	text_zombie.loadFromFile("imagenes/zombieimg.png");
	spr_zombie.setTexture(text_zombie);

	text_survirordisp.loadFromFile("imagenes/survivorshoot.png");
	spr_survivordisp.setTexture(text_survirordisp);
	
	text_survivor.loadFromFile("imagenes/survivor.png");
	spr_survivor.setTexture(text_survivor);

	
}

void juego::procesar_eventos()
{	
	
	//survivor jugadorObj;
	while (ventana1->pollEvent(*eventos))
	{
		

		switch (eventos->type)
		{
		case Event::MouseMoved:
			
			spr_mira.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));
			break;
		
		case Event::MouseButtonPressed:
			switch (eventos->key.code)
			{
				
				case Mouse::Left:
					cout << "APRETASTE EL IZQUIERDO" << endl;
					spr_survivor.setColor(Color(255, 255, 255, 0));
					spr_survivordisp.setColor(Color(255, 255, 255, 255));
				break;

				case Mouse::Right:
					cout << "APRETASTE EL DERECHO" << endl;
				break;
			}
		break;

		case Event::MouseButtonReleased:
			switch (eventos->key.code) 
			{
				case Mouse::Left:
					cout << "SOLTASTE EL IZQUIERDO" << endl;
					spr_survivor.setColor(Color(255, 255, 255, 255));
					spr_survivordisp.setColor(Color(255, 255, 255, 0));
				break;

				case Mouse::Right:
					cout << "SOLTASTE EL DERECHO" << endl;
				break;
			}
		
		break;
			
		}
	}

}
