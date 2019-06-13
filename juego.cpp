#include "juego.h"
#include <iostream>
#include <dos.h>
#include<vector>
using namespace std;

float angle2, c, d;
Time delay = seconds(3);
survivor pj({ 0,0 }, 1, 1), & ref = pj;
zombie zombie1({ 200, 300 }, 1, 20, 100);
Vector2f pjCenter, mousePosWindow, aimDir, aimDirNorm;


juego::juego(Vector2f resolucion, String titulo)
{
	bool flag = false;
	ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	ventana1->setFramerateLimit(60);


	game_over = false;
	fps = 1 / 60.f;


	eventos = new Event;
	reloj1 = new Clock();
	tiempo1 = new Time();
	tiempo2 = 0.f;

	///bala1 = new bala();


	ventana1->setMouseCursorVisible(false);

	cargar_graficos(resolucion);
	cargar_sonidos();
	cargar_fuentes();
	cancion_menu.play();
	while(!(Keyboard::isKeyPressed(Keyboard::Enter))){
	ventana1->clear();

	ventana1->draw(spr_intro1);
	ventana1->draw(titulo_intro);
	
	ventana1->draw(titulo_enter);

	ventana1->display();
	
	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		cancion_menu.stop();
		cancion_juego.play();
		cancion_juego.setLoop(true);
		gameloop(resolucion);
		
	}
	}
}

void juego::gameloop(Vector2f resolucion)
{
	while (!game_over)
	{
		*tiempo1 = reloj1->getElapsedTime();
		 
		if (tiempo1->asSeconds() > tiempo2 + fps)
		{
			tiempo2 = tiempo1->asSeconds();

			ventana1->clear();


			procesar_eventos();

			///ventana1->draw(spr_intro1);

			ventana1->draw(spr_fondo);

			///dibujo pj y mira al mouse
			ventana1->draw(pj.get_spr_survivordisparo());
			ventana1->draw(pj.get_spr_survivor());
			pj.mirarAlMouse(ventana1);
			//////******//////

			///Dibujo Zombie
			ventana1->draw(zombie1.get_spr_zombie());

			///Dibujo el Crosshair
			ventana1->draw(spr_mira);


			///zombie mira a survivor
			c = zombie1.get_posicion().x - pj.get_posicion().x;
			d = zombie1.get_posicion().y - pj.get_posicion().y;
			angle2 = (-atan2(c, d) * 180.f / 3.14) - 170.f;
			zombie1.rotar(angle2);
			
			///procesar colision pj-ventana
			pj.colisionVentana(resolucion);

			///MOVIMIENTO SURVIVOR CON TECLADO
			pj.movimiento_teclado();

			///Zombie sigue al survivor
			zombie1.update(pj.get_posicion());
			zombie1.mover(Vector2f(zombie1.get_velocidad().x, zombie1.get_velocidad().y));
			
			bullet b1;
			vector<bullet> balas;

			balas.push_back(bullet(b1));
			

			for (size_t i = 0; i < balas.size(); i++) 
			{
				ventana1 -> draw(balas[i].shape);
			}

			/////*****/////*****/////
			//update bala
			pjCenter = pj.get_posicion();
			mousePosWindow = Vector2f(Mouse::getPosition(*ventana1));
			aimDir = mousePosWindow - pjCenter;
			aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				b1.shape.setPosition(pjCenter);
				b1.currVelocity = aimDirNorm * b1.maxSpeed;

				balas.push_back(bullet(b1));
			}

			for (size_t i = 0; i < balas.size(); i++) 
			{
				balas[i].shape.move(balas[i].currVelocity);
			}

			ventana1->display();

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
	
	titulo_intro.setString("ZOMBIE \n \t KILLA");
	titulo_intro.setFont(zombiefont);
	titulo_intro.setPosition(Vector2f(269, 97));
	titulo_intro.setFillColor(Color::Color(255, 0, 0, 170));
	titulo_intro.setCharacterSize(100);
	titulo_intro.setOutlineColor(Color::Color(0, 0, 0, 255));
	titulo_intro.setOutlineThickness(1.5);

	titulo_enter.setString("Press \n Enter");
	titulo_enter.setFont(zombiefont);
	titulo_enter.setPosition(Vector2f(350, 450));
	titulo_enter.setFillColor(Color::Color(255, 0, 0, 150));
	titulo_enter.setCharacterSize(50);
	titulo_enter.setOutlineColor(Color::Color(0, 0, 0, 255));
	titulo_enter.setOutlineThickness(1.5);
	
}

void juego::cargar_graficos(Vector2f resolucion)
{
	text_intro1.loadFromFile("imagenes/titulo.jpg");
	spr_intro1.setTexture(text_intro1);
	spr_intro1.setScale(resolucion.x / text_intro1.getSize().x, resolucion.y / text_intro1.getSize().y);
	
	text_blanco.loadFromFile("imagenes/blanco.jpg");
	spr_blanco.setTexture(text_blanco);
	spr_blanco.setColor(Color(255, 255, 255, 0));

	text_fondo.loadFromFile("imagenes/fondo.jpg");
	spr_fondo.setTexture(text_fondo);
	spr_fondo.setScale(resolucion.x / text_fondo.getSize().x, resolucion.y / text_fondo.getSize().y);
	
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
	

	if (!cancion_menu.openFromFile("sonidos/cancion.wav"))
	{
		cout << "No se pudo cargar el efecto cancion." << endl;
	}
	cancion_menu.setVolume(50);

	if (!cancion_juego.openFromFile("sonidos/tormenta.ogg"))
	{
		cout << "No se pudo cargar el efecto cancion." << endl;
	}
	cancion_juego.setVolume(20);

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
					pj.color_aprietodisparo();
					sonidoDisparo.play();
				
					



					if (Mouse::isButtonPressed(Mouse::Left)) {
						sonidoDisparo.setLoop(true);
						sonidoDisparo.setPitch(7);
						sonidoDisparo.play();
						sonidoDisparo.setVolume(3);
					}
				break;
			}
		break;

		case Event::MouseButtonReleased:
			switch (eventos->key.code) 
			{
				case Mouse::Left:
					pj.color_sueltodisparo();
					sonidoDisparo.setLoop(false);
				break;
			}
		
		break;
			
		}
	}

}
