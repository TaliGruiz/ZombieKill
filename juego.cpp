#define _CRT_SECURE_NO_DEPRECATE
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
1) Barras de vida.
2) Vector balas.
- Vector zombies.
- Tres tipos de ranking

Poss	Nombre	Oleada	Kills	Tiempo	Disparos	Aciertos
------------------------------------------------------------
#1		Lucas	 20		100		20:00	500			50
#2		Jorge	 19		90		18:00
#3		Gonzalo	 18		80		16:00
------------------------------------------------------------

- Oleadas.
- Colisiones en genaral.
- Puntaje en pantalla, ronda pantalla.
- Daño de zombie y jugador.
- Menu completo
- Pantalla de game over(Agregar nuevo score).
- Mejora del arma al final de cada oleada.
- Pausa.
- Nuevo fondo (Podria llegar a cambiar por oleadas.)
-
/////////////////////////////////////////////////

*/
float angle2, c, d;
Time delay = seconds(3);
survivor pj({ 0,0 }, 1, 1), & ref = pj;
//zombie zombie1({ 200, 300 }, 1, 20, 100);
zombie zombie2({ 200, 300 }, 1, 100);
Vector2f pjCenter, mousePosWindow, aimDir, aimDirNorm;
bullet b1;
bool deletebala = false;
bool spr_zombie_flag = false;
int cantz = 5;
vector<zombie>::const_iterator iter;
vector<zombie> vecz;
int contronda = 1;

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
			if (!deletebala)
				ventana1->draw(b1.spr_bala);
			else
				deletebala = false;
			
			///dibujo pj y mira al mouse
			ventana1->draw(pj.get_spr_survivordisparo());
			ventana1->draw(pj.get_spr_survivor());
			pj.mirarAlMouse(ventana1);


			//////******//////

			///Dibujo Zombie
					///zombie mira a survivor

			int contz = 0,muertes=0;
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

			

			///Dibujo el Crosshair
			ventana1->draw(spr_mira);
			ventana1->draw(text_ronda);

			///procesar colision pj-ventana
			pj.colisionVentana(resolucion);
			
			///MOVIMIENTO SURVIVOR CON TECLADO
			pj.movimiento_teclado();

			///Zombie sigue al survivor
	
			///MOVIMIENTO BALA
			b1.mover(Vector2f(b1.get_velocidad().x, b1.get_velocidad().y));
			
			
			/////////======================////////////////////
			
			//update bala
			
			text_ronda.setString(" RONDA   " + to_string(contronda));
			text_ronda.setFont(zombienumfont);
			text_ronda.setPosition(Vector2f(650, 10));
			text_ronda.setFillColor(Color::Color(255, 0, 0, 150));
			text_ronda.setCharacterSize(20);
			text_ronda.setOutlineColor(Color::Color(0, 0, 0, 255));
			text_ronda.setOutlineThickness(1.5);

			ventana1->display();
			
			//////////////////////////////////////////////////////////////
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

	if (!zombienumfont.loadFromFile("fuentes/Scary Halloween Font.ttf"))
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

	text_fondo.loadFromFile("imagenes/fondo.jpeg");
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
