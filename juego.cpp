#include "juego.h"
#include "survivor.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <dos.h>


using namespace std;
bool jugadorUp, jugadorDown, jugadorRight, jugadorLeft;
Vector2i mouse;
float angle;
Vector2f survPos,survDispPos;
float a, b;
Time delay = seconds(3);


juego::juego(Vector2f resolucion, String titulo)
{
	bool flag = false;
	ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	ventana1->setFramerateLimit(144);

	game_over = false;
	fps = 1 / 60.f;


	eventos = new Event;
	reloj1 = new Clock();
	tiempo1 = new Time();
	tiempo2 = 0.f;

	///bala1 = new bala();

	
	ventana1->setMouseCursorVisible(false);

	cargar_graficos();
	cargar_sonidos();
	cargar_fuentes();
	gameloop();
}

void juego::gameloop()
{
	survivor jugadorObj;
	spr_survivor.setRotation(0);
	spr_survivordisp.setRotation(0);
	while (!game_over)
	{
		*tiempo1 = reloj1->getElapsedTime();
		 
		if (tiempo1->asSeconds() > tiempo2 + fps)
		{
			tiempo2 = tiempo1->asSeconds();

			ventana1->clear();


			procesar_eventos();

			survDispPos;
			///survivor sigue al mouse
			survPos = spr_survivor.getPosition();
			a = survPos.x - mouse.x;
			b = survPos.y - mouse.y;

			mouse = Mouse::getPosition(*ventana1);
			angle = (-atan2(a, b) * 180 / 3.14) - 97;
			spr_survivor.setRotation(angle);
			///survivor dispara sigue al mouse
			spr_survivordisp.setRotation(angle);


			///ventana1->draw(spr_intro1);


			ventana1->draw(spr_fondo);
			ventana1->draw(spr_survivordisp);
			//spr_survirordisp.setColor(Color::Transparent);
			ventana1->draw(spr_survivor);

			ventana1->draw(spr_zombie);

			ventana1->draw(spr_mira);


			//bala1->actualizar(tiempo2);
			//ventana1->draw(bala1->get_sprite());
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
			spr_survivor.move(Vector2f(jugadorObj.get_velocidad_x(), jugadorObj.get_velocidad_y()));
			spr_survivordisp.move(Vector2f(jugadorObj.get_velocidad_x(), jugadorObj.get_velocidad_y()));

		}
	}

}

void juego::cargar_fuentes() 
{
	if (!zombiefont.loadFromFile("fuentes/zombiefont.ttf"))
	{
		cout << "No se pudo cargar la fuente" << endl;
	}
	else { cout << "Se cargo la fuente" << endl; }
	
	titulo.setString("ZOMBIE \n \t KILLA");
	titulo.setFont(zombiefont);
	titulo.setPosition(Vector2f(330, 450));
	titulo.setFillColor(Color::Color(255, 0, 0, 170));
	titulo.setCharacterSize(50);
	titulo.setOutlineColor(Color::Color(0, 0, 0, 255));
	titulo.setOutlineThickness(1.5);
	
}
void juego::cargar_graficos()
{
	text_intro1.loadFromFile("imagenes/titulo.jpg");
	spr_intro1.setTexture(text_intro1);
	spr_intro1.setScale((float)ventana1->getSize().x / text_intro1.getSize().x, (float)ventana1->getSize().y / text_intro1.getSize().y);
	
	text_blanco.loadFromFile("imagenes/blanco.jpg");
	spr_blanco.setTexture(text_blanco);
	//spr_blanco.setScale((float)ventana1->getSize().x / text_blanco.getSize().x, (float)ventana1->getSize().y / text_blanco.getSize().y);
	spr_blanco.setColor(Color(255, 255, 255, 0));

	text_fondo.loadFromFile("imagenes/fondo.jpg");
	spr_fondo.setTexture(text_fondo);
	spr_fondo.setScale((float)ventana1->getSize().x / text_fondo.getSize().x, (float)ventana1->getSize().y / text_fondo.getSize().y);

	text_zombie.loadFromFile("imagenes/newzombie.png");
	spr_zombie.setTexture(text_zombie);

	text_survirordisp.loadFromFile("imagenes/survivorshoot.png");
	spr_survivordisp.setTexture(text_survirordisp);
	
	text_survivor.loadFromFile("imagenes/survivor.png");
	spr_survivor.setTexture(text_survivor);

	text_mira.loadFromFile("imagenes/crosshair.png");
	spr_mira.setTexture(text_mira);
	spr_mira.setColor(Color(0, 255, 0, 255));
}
void juego::cargar_sonidos()
{
	if (!BuffDisparo.loadFromFile("sonidos/shot.wav"))
	{
		cout << "No se pudo cargar el efecto disparo." << endl;

	}
	sonidoDisparo.setBuffer(BuffDisparo);
	

	if (!cancion.openFromFile("sonidos/cancion.wav"))
	{
		cout << "No se pudo cargar el efecto cancion." << endl;
	}
	cancion.setVolume(40);

}
void juego::procesar_eventos()
{	
	
	//survivor jugadorObj;
	while (ventana1->pollEvent(*eventos))
	{
		/*
		ACA VA LO DEL PRESIONAR ENTER.
		*/

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
					sonidoDisparo.play();
					
					if (Mouse::isButtonPressed(Mouse::Left)) {
						sonidoDisparo.setLoop(true);
						sonidoDisparo.setPitch(5);
						sonidoDisparo.play();
					}
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
					sonidoDisparo.setLoop(false);
				break;

				case Mouse::Right:
					cout << "SOLTASTE EL DERECHO" << endl;
				break;
			}
		
		break;
			
		}
	}

}
