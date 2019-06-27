//#define _CRT_SECURE_NO_DEPRECATE
#include "juego.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <dos.h>
#include<vector>
#include "Collision.h"
using namespace std;
/*
//////////////////////////////////////////////////
1) Barras de vida. ///
2) Vector balas. ///
- Vector zombies. ///
- Tres tipos de ranking

Poss	Nombre	Oleada	Kills   aim %
-------------------------------------
#1		Lucas	 20		100		 50%
#2		Jorge	 19		90		 40%
#3		Gonzalo	 18		80		 30%
-------------------------------------

- Oleadas. ///
- Colisiones en general.
- Puntaje en pantalla, ronda pantalla. ///
- Daño de zombie y jugador. 
- Menu completo
- Pantalla de game over(Agregar nuevo score).
- Pausa.
/////////////////////////////////////////////////
*/

float angle2, c, d;
Time delay = seconds(3);
survivor pj({ 400,300 }, 1, 1), & ref = pj;
zombie zombie2({ 200, 300 }, 1, 100);
Vector2f pjCenter, mousePosWindow, aimDir, aimDirNorm;
bullet b1;
bool deletebala = false;
bool spr_zombie_flag = false;
int cantz = 5;
vector<zombie>::const_iterator iter;
vector<zombie> vecz;
int contronda = 1;
bool flag = true;
int tipomenu=0;
Event escribirNombre;
sf::String playerInput;
sf::Text playerText;



juego::juego(Vector2f resolucion, String titulo)
{
	
		ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
		ventana1->setFramerateLimit(60);

		fps = 1 / 60.f;


		eventos = new Event;
		reloj1 = new Clock();
		tiempo1 = new Time();
		tiempo2 = 0.f;


		//PRIMERA RONDA
		for (int i = 0; i < cantz; i++)
		{
			int random3 = rand() % 800;
			//int random4 = rand() % 600;
			int randomx = rand() % 10 + random3;
			int randomy = rand() % 20 + 0;
			vecz.push_back(zombie2);
			vecz[i].set_posicion(Vector2f(randomx, randomy));
			vecz[i].set_spr_zombie_posicion(Vector2f(randomx, randomy));
		}
		/////*****/////

		cargar_graficos(resolucion);
		cargar_sonidos();
		cargar_fuentes();
		ventana1->draw(spr_mira);

		ventana1->setMouseCursorVisible(false);

		
		cancion_menu.play();

		while (!(Keyboard::isKeyPressed(Keyboard::Enter))) {
			ventana1->clear();

			ventana1->draw(spr_intro1);
			ventana1->draw(titulo_intro);

			ventana1->draw(titulo_enter);

			ventana1->display();

			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				game_over = true;
				tipomenu = 1;
				//cancion_menu.stop();
				//cancion_juego.play();
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

				ventana1->draw(spr_fondo);
				if (!deletebala)
					ventana1->draw(b1.spr_bala);
				else
					deletebala = false;

				///MOVIMIENTO SURVIVOR CON TECLADO
				pj.movimiento_teclado();
				///survivor mira direccion al mouse
				pj.mirarAlMouse(ventana1);
				
				//////******//////

				int contz = 0, muertes = 0;
				for (iter = vecz.begin(); iter != vecz.end(); iter++)
				{
					c = vecz[contz].get_posicion().x - pj.get_posicion().x;
					d = vecz[contz].get_posicion().y - pj.get_posicion().y;
					angle2 = (-atan2(c, d) * 180.f / 3.14) - 170.f;

					vecz[contz].rotar(angle2);
					vecz[contz].update(pj.get_spr_survivor().getPosition());
					vecz[contz].mover(Vector2f(vecz[contz].get_velocidad().x, vecz[contz].get_velocidad().y));
					ventana1->draw(vecz[contz].get_spr_zombie());



					if (Collision::CircleTest(b1.get_spr_bala(), vecz[contz].get_spr_zombie())) {
						b1.set_posicion(pj.get_posicion());
						b1.spr_bala.setPosition(pj.get_posicion());
						b1.spr_bala.setColor(Color(255, 255, 255, 0));
						b1.set_velocidad(Vector2f(0, 0));
						deletebala = true;
						vecz[contz].set_currHp(vecz[contz].get_currHp() - b1.get_str());
					}

					if (vecz[contz].get_currHp() <= 0)
					{
						vecz[contz].set_posicion(Vector2f(810, 610));
						vecz[contz].set_spr_zombie_posicion(Vector2f(810, 610));
						muertes++;
					}

					if (Collision::PixelPerfectTest(vecz[contz].get_spr_zombie(), pj.get_spr_survivor())) 
					{
						game_over = true;
						tipomenu = 1;
					}

					contz++;



				}
				if (muertes == cantz) {
					contronda++;
					vecz.clear();
					cantz += 2;
					for (int i = 0; i < cantz; i++)
					{
						int random1 = rand() % 800;
						int random2 = rand() % 600;
						int randomx = rand() % 10 + random1;
						int randomy = rand() % 10 + random2;
						vecz.push_back(zombie2);
						vecz[i].set_posicion(Vector2f(randomx, randomy));
						vecz[i].set_spr_zombie_posicion(Vector2f(randomx, randomy));
					}
					//POR ACA IRIA LA CARGA DE SCORES
					FILE* p;
					p = fopen("Scores.dat", "ab");
					if (p == NULL) { exit(1); }
					fclose(p);
				}

				///procesar colision pj - ventana
				pj.colisionVentana(resolucion);


				/////////======================////////////////////

				///update bala
				text_ronda.setString(" RONDA   " + to_string(contronda));
				///MOVIMIENTO BALA
				b1.mover(Vector2f(b1.get_velocidad().x, b1.get_velocidad().y));


				///dibujo pj y mira al mouse
				ventana1->draw(pj.get_spr_survivordisparo());
				ventana1->draw(pj.get_spr_survivor());
				///dibujo arbol
				ventana1->draw(spr_fondoarbol);
				///dibujo mira
				ventana1->draw(spr_mira);
				///dibujo texto ronda
				ventana1->draw(text_ronda);
				///display
				ventana1->display();

				//////////////////////////////////////////////////////////////
			}
		}
	
	while (game_over)
	{
		ventana1->clear();
		
		ventana1->setMouseCursorVisible(true);
		switch (tipomenu)
		{
		case 1:
			ventana1->draw(spr_intro1);
			ventana1->draw(text_jugar);
			ventana1->draw(text_score);
			ventana1->draw(text_salir);
			ventana1->display();
			if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(*ventana1).x && Mouse::getPosition(*ventana1).y)
			{
				IntRect playButtonRect(text_jugar.getPosition().x, text_jugar.getPosition().y, text_jugar.getGlobalBounds().width, text_jugar.getGlobalBounds().height);
				bool banderita = true;
				if (playButtonRect.contains(sf::Mouse::getPosition(*ventana1)))
				{
					cancion_menu.stop();
					cancion_juego.play();
					tipomenu = 0;
					game_over = false;
					ventana1->setMouseCursorVisible(false);
					gameloop(resolucion);
					
				}
			}
			break;
		
			
		
		}

			/*
			Event event;
			sf::String playerInput;
			sf::Text playerText;

				if (event.type == sf::Event::TextEntered)
				{
					playerInput += event.text.unicode;
					playerText.setString(playerInput);
				}
			ventana1->draw(playerText);
			*/
	}

}

void juego::cargar_fuentes() 
{
	
	if (!zombiefont.loadFromFile("fuentes/zombiefont.ttf"))
	{
		cout << "No se pudo cargar la fuente" << endl;
	}
	else { cout << "Se cargo la fuente" << endl; }

	if (!zombienumfont.loadFromFile("fuentes/Scary Halloween Font.ttf"))
	{
		cout << "No se pudo cargar la fuente" << endl;
	}
	else { cout << "Se cargo la fuente" << endl; }

	text_ronda.setFont(zombienumfont);
	text_ronda.setPosition(Vector2f(650, 10));
	text_ronda.setFillColor(Color::Color(255, 0, 0, 150));
	text_ronda.setCharacterSize(20);
	text_ronda.setOutlineColor(Color::Color(0, 0, 0, 255));
	text_ronda.setOutlineThickness(1.5);

	text_jugar.setString("JUGAR");
	text_jugar.setFont(zombiefont);
	text_jugar.setPosition(Vector2f(350, 50));
	text_jugar.setFillColor(Color::Color(255, 0, 0, 170));
	text_jugar.setCharacterSize(50);
	text_jugar.setOutlineColor(Color::Color(0, 0, 0, 255));
	text_jugar.setOutlineThickness(1.5);

	text_score.setString("RANKING");
	text_score.setFont(zombiefont);
	text_score.setPosition(Vector2f(350, 250));
	text_score.setFillColor(Color::Color(255, 0, 0, 170));
	text_score.setCharacterSize(50);
	text_score.setOutlineColor(Color::Color(0, 0, 0, 255));
	text_score.setOutlineThickness(1.5);

	text_salir.setString("SALIR");
	text_salir.setFont(zombiefont);
	text_salir.setPosition(Vector2f(350, 450));
	text_salir.setFillColor(Color::Color(255, 0, 0, 170));
	text_salir.setCharacterSize(50);
	text_salir.setOutlineColor(Color::Color(0, 0, 0, 255));
	text_salir.setOutlineThickness(1.5);

	String playerInput;
	Text playerText;
	playerText.setFont(zombiefont);
	playerText.setPosition(400, 300);
	playerText.setCharacterSize(50);
	
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
	spr_blanco.setScale(resolucion.x / text_blanco.getSize().x, resolucion.y / text_blanco.getSize().y);
	spr_blanco.setColor(Color(255, 255, 255, 255));

	text_fondo.loadFromFile("imagenes/fondo.png");
	spr_fondo.setTexture(text_fondo);
	spr_fondo.setScale(resolucion.x / text_fondo.getSize().x, resolucion.y / text_fondo.getSize().y);

	text_fondoarbol.loadFromFile("imagenes/fondoarbol.png");
	spr_fondoarbol.setTexture(text_fondoarbol);
	spr_fondo.setScale(resolucion.x / text_fondoarbol.getSize().x, resolucion.y / text_fondoarbol.getSize().y);
	
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
	cancion_juego.setVolume(70);

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
					pj.color_aprietodisparo();
					sonidoDisparo.play();
				
					if (Mouse::isButtonPressed(Mouse::Left)) {
						sonidoDisparo.setPitch(3);
						sonidoDisparo.play();
						sonidoDisparo.setVolume(50);
						b1.spr_bala.setColor(Color(255, 255, 255, 255));
						b1.update(pj.get_posicion(),Mouse::getPosition(*ventana1));
					}
				break;
			}
		break;

		case Event::MouseButtonReleased:
			switch (eventos->key.code) 
			{
				case Mouse::Left:
					pj.color_sueltodisparo();
				break;
			}
		
		break;
			
		}
	}

}
