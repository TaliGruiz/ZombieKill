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
- Tres tipos de ranking///

Poss	Nombre	Oleada	Kills   aim %
-------------------------------------
#1		Lucas	 20		100		 50%
#2		Jorge	 19		90		 40%
#3		Gonzalo	 18		80		 30%
-------------------------------------

- Oleadas. ///
- Colisiones en general.///
- Puntaje en pantalla, ronda pantalla. ///
- Daño de zombie y jugador. 
- Menu completo///
- Pantalla de game over(Agregar nuevo score).///

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
int cantz;
vector<zombie>::const_iterator iter;
vector<zombie> vecz;
int contronda = 1;
bool flag = true;

juego::juego(Vector2f resolucion, String titulo)
{
		ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
		ventana1->setFramerateLimit(60);

		cargar_graficos(resolucion);
		cargar_sonidos();
		cargar_fuentes();
		ventana1->draw(spr_mira);
		ventana1->setMouseCursorVisible(false);
		
		fps = 1 / 60.f;

		eventos = new Event;
		reloj1 = new Clock();
		tiempo1 = new Time();
		tiempo2 = 0.f;
		
		cancion_menu.play();
		cancion_menu.setLoop(true);
		menu_pressenter(resolucion);
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

				//CARGO VECTOR POR PRIMERA VEZ
				if (contronda == 0) 
				{
					for (int i = 0; i < cantz; i++)
					{
						contronda = 1;
						int random3 = rand() % 800;
						int random4 = rand() % 600;
						int randomx = rand() % 10 + random3;
						int randomy = rand() % 20 + 0;
						vecz.push_back(zombie2);
						vecz[i].set_posicion(Vector2f(randomx, randomy));
						vecz[i].set_spr_zombie_posicion(Vector2f(randomx, randomy));
					}
				}

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
						vecz.clear();
						game_over = true;
						cancion_juego.stop();
						cancion_menu.play();
						return;
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
					
				}

				
				/////////======================////////////////////
				
				///procesar colision pj - ventana
				pj.colisionVentana(resolucion);
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

}

void juego::cargar_fuentes() 
{
	
	if (!zombiefont.loadFromFile("fuentes/zombiefont.ttf"))
	{
		cout << "No se pudo cargar la fuente zombie" << endl;
	}
	else { cout << "Se cargo la fuente zombie" << endl; }

	if (!scaryfont.loadFromFile("fuentes/Scary Halloween Font.ttf"))
	{
		cout << "No se pudo cargar la fuente scary" << endl;
	}
	else { cout << "Se cargo la fuente scary" << endl; }

	hasMuerto.setFont(zombiefont);
	hasMuerto.setFillColor(Color::Red);
	hasMuerto.setString("HAS \n \t MUERTO");
	hasMuerto.setPosition(Vector2f(350, 250));
	hasMuerto.setCharacterSize(60);
	hasMuerto.setOutlineColor(Color::Color(0, 0, 0, 255));
	hasMuerto.setOutlineThickness(1.5);

	//Textos menus
	menutext[0].setFont(scaryfont);
	menutext[0].setFillColor(Color::Red);
	menutext[0].setString("JUGAR");
	menutext[0].setPosition(Vector2f(350, 50));
	menutext[0].setCharacterSize(40);
	menutext[0].setOutlineColor(Color::Color(0, 0, 0, 255));
	menutext[0].setOutlineThickness(1.5);

	menutext[1].setFont(scaryfont);
	menutext[1].setFillColor(Color::Red);
	menutext[1].setString("RANKING");
	menutext[1].setPosition(Vector2f(320, 250));
	menutext[1].setCharacterSize(40);
	menutext[1].setOutlineColor(Color::Color(0, 0, 0, 255));
	menutext[1].setOutlineThickness(1.5);

	menutext[2].setFont(scaryfont);
	menutext[2].setFillColor(Color::Red);
	menutext[2].setString("SALIR");
	menutext[2].setPosition(Vector2f(350, 450));
	menutext[2].setCharacterSize(40);
	menutext[2].setOutlineColor(Color::Color(0, 0, 0, 255));
	menutext[2].setOutlineThickness(1.5);

	//Texto Rounds
	text_ronda.setFont(scaryfont);
	text_ronda.setPosition(Vector2f(650, 10));
	text_ronda.setFillColor(Color::Color(255, 0, 0, 150));
	text_ronda.setCharacterSize(20);
	text_ronda.setOutlineColor(Color::Color(0, 0, 0, 255));
	text_ronda.setOutlineThickness(1.5);

	//zombie killa
	titulo_intro.setString("ZOMBIE \n \t KILLA");
	titulo_intro.setFont(zombiefont);
	titulo_intro.setPosition(Vector2f(269, 97));
	titulo_intro.setFillColor(Color::Color(255, 0, 0, 170));
	titulo_intro.setCharacterSize(100);
	titulo_intro.setOutlineColor(Color::Color(0, 0, 0, 255));
	titulo_intro.setOutlineThickness(1.5);

	//press enter
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

	text_puntero1.loadFromFile("imagenes/punterozombie1.png");
	spr_puntero1.setTexture(text_puntero1);
	spr_puntero1.setColor(Color(255, 255, 255, 0));

	text_puntero2.loadFromFile("imagenes/punterozombie2.png");
	spr_puntero2.setTexture(text_puntero2);
	spr_puntero2.setColor(Color(255, 255, 255, 255));

}

void juego::cargar_sonidos()
{
	if (!BuffDisparo.loadFromFile("sonidos/shot.wav"))
	{
		cout << "No se pudo cargar el efecto disparo." << endl;
	}
	sonidoDisparo.setBuffer(BuffDisparo);
	

	if (!cancion_menu.openFromFile("sonidos/twdtheme.ogg"))
	{
		cout << "No se pudo cargar el efecto cancion menu." << endl;
	}
	cancion_menu.setVolume(50);

	if (!cancion_juego.openFromFile("sonidos/tormenta.ogg"))
	{
		cout << "No se pudo cargar el efecto cancion tormenta." << endl;
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

///MENU - MENU Dibujos
void juego::menu_dibujar_principal() 
{
	ventana1->clear();

	spr_puntero1.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));
	spr_puntero2.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));

	ventana1->setMouseCursorVisible(false);
	ventana1->draw(spr_intro1);
	///dibujo las opciones
	ventana1->draw(menutext[0]);
	ventana1->draw(menutext[1]);
	ventana1->draw(menutext[2]);
	///dibujo el puntero
	ventana1->draw(spr_puntero1);
	ventana1->draw(spr_puntero2);
	
	ventana1->display();
}

void juego::menu_dibujar_pressenter() 
{
	ventana1->clear();
	ventana1->draw(spr_intro1);
	ventana1->draw(titulo_intro);
	ventana1->draw(titulo_enter);
	ventana1->display();
}

void juego::menu_dibujar_efectoblanco(IntRect botonjugar, IntRect botonranking, IntRect botonsalir)
{
	if (botonjugar.contains(sf::Mouse::getPosition(*ventana1)))
		menutext[0].setFillColor(Color::White);
	if (!(botonjugar.contains(sf::Mouse::getPosition(*ventana1))))
		menutext[0].setFillColor(Color::Red);
	if (botonranking.contains(sf::Mouse::getPosition(*ventana1)))
		menutext[1].setFillColor(Color::White);
	if (!(botonranking.contains(sf::Mouse::getPosition(*ventana1))))
		menutext[1].setFillColor(Color::Red);
	if (botonsalir.contains(sf::Mouse::getPosition(*ventana1)))
		menutext[2].setFillColor(Color::White);
	if (!(botonsalir.contains(sf::Mouse::getPosition(*ventana1))))
		menutext[2].setFillColor(Color::Red);
}

void juego::menu_pressenter(Vector2f resolucion)
{
	while (!(Keyboard::isKeyPressed(Keyboard::Enter))) {
		menu_dibujar_pressenter();
		if (Keyboard::isKeyPressed(Keyboard::Enter))
			menu_principal(resolucion);
	}
}

void juego::menu_escribirNombre(Vector2f resolucion)
{
	
	ventana1->clear();
	ventana1->draw(spr_intro1);

	Event setname;
	String playerInput;
	Text playerText;
	playerText.setPosition(350, 50);
	playerText.setFillColor(Color::Red);

	while (true)
	{
		if (setname.type == Event::TextEntered)
		{
			if (setname.text.unicode < 128)
			{
				playerInput += static_cast<char>(setname.text.unicode);
				playerText.setString(playerInput);
			}
			ventana1->draw(playerText);

		}
		ventana1->display();
	}
	
}

void juego::menu_principal(Vector2f resolucion)
{
	IntRect botonjugar(menutext[0].getPosition().x, menutext[0].getPosition().y, menutext[0].getGlobalBounds().width, menutext[0].getGlobalBounds().height);
	IntRect botonranking(menutext[1].getPosition().x, menutext[1].getPosition().y, menutext[1].getGlobalBounds().width, menutext[1].getGlobalBounds().height);
	IntRect botonsalir(menutext[2].getPosition().x, menutext[2].getPosition().y, menutext[2].getGlobalBounds().width, menutext[2].getGlobalBounds().height);

	while (true)
	{
		menu_dibujar_principal();
		menu_dibujar_efectoblanco(botonjugar, botonranking, botonsalir);

		if (!Mouse::isButtonPressed(Mouse::Left)) 
		{
			spr_puntero1.setColor(Color(255, 255, 255, 0));
			spr_puntero2.setColor(Color(255, 255, 255, 255));
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			spr_puntero1.setColor(Color(255, 255, 255, 255));
			spr_puntero2.setColor(Color(255, 255, 255, 0));

			if (botonjugar.contains(sf::Mouse::getPosition(*ventana1)))
			{
				contronda = 0;
				cantz = CANT_ZOMBIES;
				cancion_menu.stop();
				cancion_juego.play();
				game_over = false;
				gameloop(resolucion);
			}

			if (botonranking.contains(Mouse::getPosition(*ventana1))) 
			{
				
			}

			if (botonsalir.contains(Mouse::getPosition(*ventana1))) exit(1);
		}
	}
}
