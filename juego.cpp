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
- Barras de vida. 
- pausa.
- menu - instrucciones.
- quitar consola.
- pantalla completa.
- menu - opciones(cambiar musica, cambiar teclas).
- DISTINTOS SPRITES DE ZOMBIES
- 
- 
- 
- Pantalla de game over.

/////////////////////////////////////////////////
*/

float angle2, c, d;
Time delay = seconds(3);
survivor pj({ 400,300 }, 1, 1), & ref = pj;
zombie zombie2({ 200, 300 }, 1, 100);
Vector2f pjCenter, mousePosWindow, aimDir, aimDirNorm;
vector<zombie>::const_iterator iter;
vector<zombie> vecz;



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

		///Respawn survivor
		pj.set_posicion(Vector2f(400, 300));
		pj.set_spr_survivor_posicion(Vector2f(400, 300));
		pj.set_spr_survivordisparo_posicion(Vector2f(400, 300));

		eventos = new Event;
		reloj1 = new Clock();
		tiempo1 = new Time();
		tiempo2 = 0.f;
		
		cancion_menu.play();
		cancion_menu.setLoop(true);
		menu_pressenter(resolucion);
		
		//ventana1->draw(playername);

}

void juego::gameloop(Vector2f resolucion,int dificultad)
{
	int pos = 0;
	rank_canttiros = 0;
	rank_rondas = 1;
	rank_tirosacertados = 0;
	rank_accuracy = 0;

	int sumarzombies;
	float speedzombie;

	switch (dificultad)
	{
	case 1:
		zombie2.set_hp(60);
		zombie2.set_currHp(60);
		sumarzombies = 2;
		speedzombie = 0.5;
		break;
	
	case 2:
		zombie2.set_hp(100);
		zombie2.set_currHp(100);
		sumarzombies = 3;
		speedzombie = 0.7;
		break;
	
	case 3: 
		zombie2.set_hp(140);
		zombie2.set_currHp(140);
		sumarzombies = 4;
		speedzombie = 1.0;
		break;
	}

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
			
				/*if (Joystick::isConnected(0))
				{
					cout << "Conectado " << endl;
					pj.update_joystick();
				}
				if (!Joystick::isConnected(0))
				{
					
				}
				*/
					
				pj.movimiento_teclado();
			
				//pj.movimiento_teclado(); 
				///survivor mira direccion al mouse
				pj.mirarAlMouse(ventana1);

				//CARGO VECTOR POR PRIMERA VEZ
				if (contronda == 0)
				{
					for (int i = 0; i < cantz; i++)
					{
						contronda = 1;
						int random = rand() % 4 + 1;
						int randomx = rand() % 800;
						int randomy = rand() % 600;
						vecz.push_back(zombie2);
						switch (random) {
						case 1:
							vecz[i].set_posicion(Vector2f(randomx, -80));
							vecz[i].set_spr_zombie_posicion(Vector2f(randomx, -80));
							break;
						case 2:
							vecz[i].set_posicion(Vector2f(880, randomy));
							vecz[i].set_spr_zombie_posicion(Vector2f(880, randomy));
							break;
						case 3:
							vecz[i].set_posicion(Vector2f(randomx, 680));
							vecz[i].set_spr_zombie_posicion(Vector2f(randomx, 680));
							break;
						case 4:
							vecz[i].set_posicion(Vector2f(-80, randomy));
							vecz[i].set_spr_zombie_posicion(Vector2f(-80, randomy));
							break;
						}
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
					vecz[contz].update(pj.get_spr_survivor().getPosition(),speedzombie);
					vecz[contz].mover(Vector2f(vecz[contz].get_velocidad().x, vecz[contz].get_velocidad().y));
					ventana1->draw(vecz[contz].get_spr_zombie());

					if (Collision::CircleTest(b1.get_spr_bala(), vecz[contz].get_spr_zombie())) {
						rank_tirosacertados ++;
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

						rank_accuracy = rank_tirosacertados * 100 / rank_canttiros;
						
						ranking.set_rondas(rank_rondas);
						ranking.set_tiros(rank_canttiros);
						ranking.set_tirosacertados(rank_tirosacertados);
						ranking.set_accuracy(rank_accuracy);
						bool grabo = ranking.grabarendisco();
						if (!grabo)cout << "no grabo" << endl;
						if(grabo)cout << "grabo" << endl;

						vecz.clear();
						game_over = true;
						cancion_juego.stop();
						cancion_menu.play();
						return;
					}

					contz++;

				}
				if (muertes == cantz) {
					rank_rondas ++;

					Sonido_endRound.play();
					contronda++;
					vecz.clear();
					cantz += sumarzombies;
					for (int i = 0; i < cantz; i++)
					{
						int random = rand() % 4 + 1;
						int randomx = rand() % 800;
						int randomy = rand() % 600;
						vecz.push_back(zombie2);
						switch (random) {
						case 1:
							vecz[i].set_posicion(Vector2f(randomx, -80));
							vecz[i].set_spr_zombie_posicion(Vector2f(randomx, -80));
							break;
						case 2:
							vecz[i].set_posicion(Vector2f(880, randomy));
							vecz[i].set_spr_zombie_posicion(Vector2f(880, randomy));
							break;
						case 3:
							vecz[i].set_posicion(Vector2f(randomx, 680));
							vecz[i].set_spr_zombie_posicion(Vector2f(randomx, 680));
							break;
						case 4:
							vecz[i].set_posicion(Vector2f(-80, randomy));
							vecz[i].set_spr_zombie_posicion(Vector2f(-80, randomy));
							break;
						}
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
	int i, posy = 0, posx, contx = 0, x = 0,por;

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

	//Textos jugador rankings
	for (i = 0; i < 60; i++)
	{
		if (i % 6 == 0) posy += 40;

		if (x == 0) posx = 35;
		if (x == 1) posx = 100;
		if (x == 2) posx = 280;
		if (x == 3) posx = 430;
		if (x == 4) posx = 590;
		if (x == 5)
		{
			x = -1;
			posx = 710;
		}

		txt_jugadores[i].setFont(scaryfont);
		txt_jugadores[i].setFillColor(Color::Red);
		txt_jugadores[i].setCharacterSize(20);
		txt_jugadores[i].setOutlineColor(Color::Color(0, 0, 0, 255));
		txt_jugadores[i].setOutlineThickness(1.5);
		txt_jugadores[i].setPosition(Vector2f(posx, posy));

		x++;
	}


	//textos menu dificultad
	text_selecdif.setFont(scaryfont);
	text_selecdif.setFillColor(Color::Red);
	text_selecdif.setString("Seleccionar Dificultad");
	text_selecdif.setPosition(Vector2f(130, 50));
	text_selecdif.setCharacterSize(40);
	text_selecdif.setOutlineColor(Color::Color(0, 0, 0, 255));
	text_selecdif.setOutlineThickness(1.5);
	
	for (i = 0; i < CANT_DIFICULTAD; i++) 
	{
		text_dif[i].setFont(scaryfont);
		text_dif[i].setFillColor(Color::Red);
		text_dif[i].setCharacterSize(40);
		text_dif[i].setOutlineColor(Color::Color(0, 0, 0, 255));
		text_dif[i].setOutlineThickness(1.5);
	}

	text_dif[0].setString("FACIL");
	text_dif[0].setPosition(Vector2f(355, 200));

	text_dif[1].setString("MEDIA");
	text_dif[1].setPosition(Vector2f(345, 350));

	text_dif[2].setString("DIFICIL");
	text_dif[2].setPosition(Vector2f(340, 500));


	//textos ranking
	for (i = 0; i < CANT_TEXT_RANKING; i++) 
	{
		txt_rank[i].setFont(scaryfont);
		txt_rank[i].setFillColor(Color::Red);
		txt_rank[i].setCharacterSize(20);
		txt_rank[i].setOutlineColor(Color::Color(0, 0, 0, 255));
		txt_rank[i].setOutlineThickness(1.5);
	}
	
	txt_rank[0].setString("POS");
	txt_rank[0].setPosition(Vector2f(20, 20));
	
	txt_rank[1].setString("NOMBRE");
	txt_rank[1].setPosition(Vector2f(100, 20));

	txt_rank[2].setString("RONDAS");
	txt_rank[2].setPosition(Vector2f(250, 20));

	txt_rank[3].setString("DISP.TOT");
	txt_rank[3].setPosition(Vector2f(400, 20));

	txt_rank[4].setString("DISP.ACERT");
	txt_rank[4].setPosition(Vector2f(550, 20));

	txt_rank[5].setString("ACC");
	txt_rank[5].setPosition(Vector2f(700, 20));


	text_atras.setFont(scaryfont);
	text_atras.setFillColor(Color::Red);
	text_atras.setCharacterSize(20);
	text_atras.setOutlineColor(Color::Color(0, 0, 0, 255));
	text_atras.setOutlineThickness(1.5);
	text_atras.setString("Atras");
	text_atras.setPosition(Vector2f(20, 560));


	//Textos menu principal

	for (i = 0; i < CANT_OPCIONES_MENU; i++) 
	{
		menutext[i].setFont(scaryfont);
		menutext[i].setFillColor(Color::Red);
		menutext[i].setCharacterSize(40);
		menutext[i].setOutlineColor(Color::Color(0, 0, 0, 255));
		menutext[i].setOutlineThickness(1.5);
	}

	menutext[0].setString("JUGAR");
	menutext[0].setPosition(Vector2f(350, 50));

	menutext[1].setString("RANKING");
	menutext[1].setPosition(Vector2f(320, 250));

	menutext[2].setString("SALIR");
	menutext[2].setPosition(Vector2f(350, 450));

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

	//ingrese nombre

	titulo_ingrese_nombre.setString("INGRESE \n NOMBRE");
	titulo_ingrese_nombre.setFont(zombiefont);
	titulo_ingrese_nombre.setPosition(Vector2f(269, 97));
	titulo_ingrese_nombre.setFillColor(Color::Color(255, 0, 0, 170));
	titulo_ingrese_nombre.setCharacterSize(100);
	titulo_ingrese_nombre.setOutlineColor(Color::Color(0, 0, 0, 255));
	titulo_ingrese_nombre.setOutlineThickness(1.5);

	//press enter
	titulo_enter.setString("Press \n Enter");
	titulo_enter.setFont(zombiefont);
	titulo_enter.setPosition(Vector2f(350, 450));
	titulo_enter.setFillColor(Color::Color(255, 0, 0, 150));
	titulo_enter.setCharacterSize(50);
	titulo_enter.setOutlineColor(Color::Color(0, 0, 0, 255));
	titulo_enter.setOutlineThickness(1.5);

	//game over
	titulo_game_over.setString("GAME OVER");
	titulo_game_over.setPosition(Vector2f(269, 40));
	titulo_game_over.setFillColor(Color::Color(255, 0, 0, 170));
	titulo_game_over.setFont(zombiefont);
	titulo_game_over.setCharacterSize(80);
	titulo_game_over.setOutlineColor(Color::Color(0, 0, 0, 255));
	titulo_game_over.setOutlineThickness(1.8);


	//creators
	titulo_creators.setString("CREADORES \n\n Lucas Abbiatici \n\n Jorge Bravo \n\n Gonzalo Ruiz");
	titulo_creators.setFont(zombiefont);
	titulo_creators.setPosition(Vector2f(350, 200));
	titulo_creators.setFillColor(Color::Color(255, 0, 0, 150));
	titulo_creators.setCharacterSize(30);
	titulo_creators.setOutlineColor(Color::Color(0, 0, 0, 255));
	titulo_creators.setOutlineThickness(1.5);
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

	text_fondozombie[0].loadFromFile("fondozombie/fondozombie (1).jpg");
	text_fondozombie[1].loadFromFile("fondozombie/fondozombie (2).jpg");
	text_fondozombie[2].loadFromFile("fondozombie/fondozombie (3).jpg");
	text_fondozombie[3].loadFromFile("fondozombie/fondozombie (4).jpg");
	text_fondozombie[4].loadFromFile("fondozombie/fondozombie (5).jpg");
	text_fondozombie[5].loadFromFile("fondozombie/fondozombie (6).jpg");
	text_fondozombie[6].loadFromFile("fondozombie/fondozombie (7).jpg");
	text_fondozombie[7].loadFromFile("fondozombie/fondozombie (8).jpg");
	text_fondozombie[8].loadFromFile("fondozombie/fondozombie (9).jpg");
	text_fondozombie[9].loadFromFile("fondozombie/fondozombie (10).jpg");
	text_fondozombie[10].loadFromFile("fondozombie/fondozombie (11).jpg");
	text_fondozombie[11].loadFromFile("fondozombie/fondozombie (12).jpg");
	text_fondozombie[12].loadFromFile("fondozombie/fondozombie (13).jpg");
	text_fondozombie[13].loadFromFile("fondozombie/fondozombie (14).jpg");
	text_fondozombie[14].loadFromFile("fondozombie/fondozombie (15).jpg");
	text_fondozombie[15].loadFromFile("fondozombie/fondozombie (16).jpg");
	text_fondozombie[16].loadFromFile("fondozombie/fondozombie (17).jpg");
	text_fondozombie[17].loadFromFile("fondozombie/fondozombie (18).jpg");
	text_fondozombie[18].loadFromFile("fondozombie/fondozombie (19).jpg");
	text_fondozombie[19].loadFromFile("fondozombie/fondozombie (20).jpg");
	text_fondozombie[20].loadFromFile("fondozombie/fondozombie (21).jpg");
	text_fondozombie[21].loadFromFile("fondozombie/fondozombie (22).jpg");
	text_fondozombie[22].loadFromFile("fondozombie/fondozombie (23).jpg");
	text_fondozombie[23].loadFromFile("fondozombie/fondozombie (24).jpg");
	text_fondozombie[24].loadFromFile("fondozombie/fondozombie (25).jpg");
	text_fondozombie[25].loadFromFile("fondozombie/fondozombie (26).jpg");
	text_fondozombie[26].loadFromFile("fondozombie/fondozombie (27).jpg");
	text_fondozombie[27].loadFromFile("fondozombie/fondozombie (28).jpg");
	text_fondozombie[28].loadFromFile("fondozombie/fondozombie (29).jpg");
	text_fondozombie[29].loadFromFile("fondozombie/fondozombie (30).jpg");
	text_fondozombie[30].loadFromFile("fondozombie/fondozombie (31).jpg");
	text_fondozombie[31].loadFromFile("fondozombie/fondozombie (32).jpg");
	text_fondozombie[32].loadFromFile("fondozombie/fondozombie (33).jpg");
	text_fondozombie[33].loadFromFile("fondozombie/fondozombie (34).jpg");
	text_fondozombie[34].loadFromFile("fondozombie/fondozombie (35).jpg");
	text_fondozombie[35].loadFromFile("fondozombie/fondozombie (36).jpg");
	text_fondozombie[36].loadFromFile("fondozombie/fondozombie (37).jpg");
	text_fondozombie[37].loadFromFile("fondozombie/fondozombie (38).jpg");
	text_fondozombie[38].loadFromFile("fondozombie/fondozombie (39).jpg");
	text_fondozombie[39].loadFromFile("fondozombie/fondozombie (40).jpg");
	text_fondozombie[40].loadFromFile("fondozombie/fondozombie (41).jpg");
	text_fondozombie[41].loadFromFile("fondozombie/fondozombie (42).jpg");
	text_fondozombie[42].loadFromFile("fondozombie/fondozombie (43).jpg");
	text_fondozombie[43].loadFromFile("fondozombie/fondozombie (44).jpg");
	text_fondozombie[44].loadFromFile("fondozombie/fondozombie (45).jpg");
	text_fondozombie[45].loadFromFile("fondozombie/fondozombie (46).jpg");
	text_fondozombie[46].loadFromFile("fondozombie/fondozombie (47).jpg");
	text_fondozombie[47].loadFromFile("fondozombie/fondozombie (48).jpg");
	text_fondozombie[48].loadFromFile("fondozombie/fondozombie (49).jpg");
	text_fondozombie[49].loadFromFile("fondozombie/fondozombie (50).jpg");
	text_fondozombie[50].loadFromFile("fondozombie/fondozombie (51).jpg");
	text_fondozombie[51].loadFromFile("fondozombie/fondozombie (52).jpg");
	text_fondozombie[52].loadFromFile("fondozombie/fondozombie (53).jpg");
	text_fondozombie[53].loadFromFile("fondozombie/fondozombie (54).jpg");
	text_fondozombie[54].loadFromFile("fondozombie/fondozombie (55).jpg");
	text_fondozombie[55].loadFromFile("fondozombie/fondozombie (56).jpg");
	text_fondozombie[56].loadFromFile("fondozombie/fondozombie (57).jpg");
	text_fondozombie[57].loadFromFile("fondozombie/fondozombie (58).jpg");
	text_fondozombie[58].loadFromFile("fondozombie/fondozombie (59).jpg");
	text_fondozombie[59].loadFromFile("fondozombie/fondozombie (60).jpg");
	text_fondozombie[60].loadFromFile("fondozombie/fondozombie (61).jpg");
	text_fondozombie[61].loadFromFile("fondozombie/fondozombie (62).jpg");
	text_fondozombie[62].loadFromFile("fondozombie/fondozombie (63).jpg");
	text_fondozombie[63].loadFromFile("fondozombie/fondozombie (64).jpg");
	text_fondozombie[64].loadFromFile("fondozombie/fondozombie (65).jpg");
	text_fondozombie[65].loadFromFile("fondozombie/fondozombie (66).jpg");
	text_fondozombie[66].loadFromFile("fondozombie/fondozombie (67).jpg");
	text_fondozombie[67].loadFromFile("fondozombie/fondozombie (68).jpg");
	text_fondozombie[68].loadFromFile("fondozombie/fondozombie (69).jpg");
	text_fondozombie[69].loadFromFile("fondozombie/fondozombie (70).jpg");
	text_fondozombie[70].loadFromFile("fondozombie/fondozombie (71).jpg");
	text_fondozombie[71].loadFromFile("fondozombie/fondozombie (72).jpg");
	text_fondozombie[72].loadFromFile("fondozombie/fondozombie (73).jpg");
	text_fondozombie[73].loadFromFile("fondozombie/fondozombie (74).jpg");
	text_fondozombie[74].loadFromFile("fondozombie/fondozombie (75).jpg");
	text_fondozombie[75].loadFromFile("fondozombie/fondozombie (76).jpg");
	text_fondozombie[76].loadFromFile("fondozombie/fondozombie (77).jpg");
	text_fondozombie[77].loadFromFile("fondozombie/fondozombie (78).jpg");
	text_fondozombie[78].loadFromFile("fondozombie/fondozombie (79).jpg");
	text_fondozombie[79].loadFromFile("fondozombie/fondozombie (80).jpg");
	text_fondozombie[80].loadFromFile("fondozombie/fondozombie (81).jpg");
	text_fondozombie[81].loadFromFile("fondozombie/fondozombie (82).jpg");
	text_fondozombie[82].loadFromFile("fondozombie/fondozombie (83).jpg");
	text_fondozombie[83].loadFromFile("fondozombie/fondozombie (84).jpg");
	text_fondozombie[84].loadFromFile("fondozombie/fondozombie (85).jpg");
	text_fondozombie[85].loadFromFile("fondozombie/fondozombie (86).jpg");
	text_fondozombie[86].loadFromFile("fondozombie/fondozombie (87).jpg");
	text_fondozombie[87].loadFromFile("fondozombie/fondozombie (88).jpg");
	text_fondozombie[88].loadFromFile("fondozombie/fondozombie (89).jpg");
	text_fondozombie[89].loadFromFile("fondozombie/fondozombie (90).jpg");
	text_fondozombie[90].loadFromFile("fondozombie/fondozombie (91).jpg");
	text_fondozombie[91].loadFromFile("fondozombie/fondozombie (92).jpg");
	text_fondozombie[92].loadFromFile("fondozombie/fondozombie (93).jpg");
	text_fondozombie[93].loadFromFile("fondozombie/fondozombie (94).jpg");
	text_fondozombie[94].loadFromFile("fondozombie/fondozombie (95).jpg");
	text_fondozombie[95].loadFromFile("fondozombie/fondozombie (96).jpg");
	text_fondozombie[96].loadFromFile("fondozombie/fondozombie (97).jpg");
	text_fondozombie[97].loadFromFile("fondozombie/fondozombie (98).jpg");
	text_fondozombie[98].loadFromFile("fondozombie/fondozombie (99).jpg");
	text_fondozombie[99].loadFromFile("fondozombie/fondozombie (100).jpg");

	for (int i = 0; i < 100; i++) 
	{
		spr_fondozombie[i].setTexture(text_fondozombie[i]);
		spr_fondozombie[i].setScale(resolucion.x / text_fondozombie[i].getSize().x, resolucion.y / text_fondozombie[i].getSize().y);
	}
}

void juego::cargar_sonidos()
{
	if (!BuffDisparo.loadFromFile("sonidos/shot.wav"))
	{
		cout << "No se pudo cargar el efecto disparo." << endl;
	}
	sonidoDisparo.setBuffer(BuffDisparo);
	
	if (!cancion_menu.openFromFile("sonidos/main theme.ogg"))
	{
		cout << "No se pudo cargar el efecto cancion menu." << endl;
	}
	cancion_menu.setVolume(50);

	if (!cancion_juego.openFromFile("sonidos/tormenta.ogg"))
	{
		cout << "No se pudo cargar el efecto tormenta." << endl;
	}
	cancion_juego.setVolume(60);

	if (!BuffendRound.loadFromFile("sonidos/endround.ogg"))
	{
		cout << "no se pudo cargar el buffer endRound" << endl;
	}
	Sonido_endRound.setBuffer(BuffendRound);
	Sonido_endRound.setVolume(50);

	if (!Buffsonido_boton_pass.loadFromFile("sonidos/menu_boton_pass.wav"))
	{
		cout << "No se pudo cargar el sonido boton pass." << endl;
	}
	sonido_boton_select.setBuffer(Buffsonido_boton_pass);

	
}

void juego::procesar_eventos()
{	
	
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
						
						rank_canttiros++; ///cuento tiros
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
void juego::menu_dibujar_principal(Vector2f resolucion,IntRect botonjugar, IntRect botonranking, IntRect botonsalir)
{
	ventana1->clear();

	
	ventana1->setMouseCursorVisible(false);
	//ventana1->draw(spr_intro1);

	for (int i = 0; i < 100; i++) 
	{
		spr_puntero1.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));
		spr_puntero2.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));

		ventana1->draw(spr_fondozombie[i]);
		///dibujo las opciones
		ventana1->draw(menutext[0]);
		ventana1->draw(menutext[1]);
		ventana1->draw(menutext[2]);
		///dibujo el puntero
		ventana1->draw(spr_puntero1);
		ventana1->draw(spr_puntero2);

		menu_dibujar_efectoblanco(botonjugar, botonranking, botonsalir);

		ventana1->display();

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
				menu_escribirNombre(resolucion);
				menu_dificultad(resolucion);
				/*
				cantz = CANT_ZOMBIES;
				contronda = 0;
				cancion_menu.stop();
				cancion_juego.play();
				game_over = false;
				gameloop(resolucion);
				*/
			}

			if (botonranking.contains(Mouse::getPosition(*ventana1)))
			{
				menu_ranking();
			}

			if (botonsalir.contains(Mouse::getPosition(*ventana1))) exit(1);
		}

	}

	
}
/*
void juego::menu_dibujar_principal()
{
	ventana1->clear();

	spr_puntero1.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));
	spr_puntero2.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));

	ventana1->setMouseCursorVisible(false);
	//ventana1->draw(spr_intro1);

	for (int i = 0; i < 100; i++)
	{
		ventana1->draw(spr_fondozombie[i]);
	}

	///dibujo las opciones
	ventana1->draw(menutext[0]);
	ventana1->draw(menutext[1]);
	ventana1->draw(menutext[2]);
	///dibujo el puntero
	ventana1->draw(spr_puntero1);
	ventana1->draw(spr_puntero2);

	ventana1->display();
}
*/
void juego::menu_dibujar_pressenter() 
{
	ventana1->clear();
	ventana1->draw(spr_intro1);
	ventana1->draw(titulo_intro);
	ventana1->draw(titulo_enter);
	ventana1->display();
}

void juego::menu_dibujar_escribirNombre()
{

	ventana1->clear();
	ventana1->draw(spr_intro1);
	ventana1->draw(titulo_ingrese_nombre);
	ventana1->draw(titulo_enter);
	ventana1->draw(playername);	
	ventana1->display();

	
}

void juego::menu_dibujar_game_over()
{
	ventana1->clear();
	ventana1->draw(spr_intro1);
	ventana1->draw(titulo_game_over);
	ventana1->draw(titulo_creators);
	ventana1->display();
}

void juego::menu_dibujar_dificultad()
{	
	spr_puntero1.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));
	spr_puntero2.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));

	ventana1->clear();
	ventana1->draw(spr_intro1);
	ventana1->draw(text_dif[0]);
	ventana1->draw(text_dif[1]);
	ventana1->draw(text_dif[2]);
	ventana1->draw(text_selecdif);
	ventana1->draw(spr_puntero1);
	ventana1->draw(spr_puntero2);

	ventana1->display();
}

void juego::menu_dibujar_efectoblanco(IntRect botonjugar, IntRect botonranking, IntRect botonsalir)
{

	if (botonjugar.contains(sf::Mouse::getPosition(*ventana1)))
	{

		menutext[0].setFillColor(Color::White);		
		if (flagsonidoblancojugar)
		{
			flagsonidoblancojugar = false;
			sonido_boton_select.play();
		}
	}
	if (!(botonjugar.contains(sf::Mouse::getPosition(*ventana1))))
	{
		menutext[0].setFillColor(Color::Red);
		if (!flagsonidoblancojugar)
		{
			flagsonidoblancojugar = true;
			sonido_boton_select.stop();
		}
	}
	if (botonranking.contains(sf::Mouse::getPosition(*ventana1)))
	{
		menutext[1].setFillColor(Color::White);
		if (flagsonidoblancoranking)
		{
			flagsonidoblancoranking = false;
			sonido_boton_select.play();
		}
	}
	if (!(botonranking.contains(sf::Mouse::getPosition(*ventana1))))
	{
		menutext[1].setFillColor(Color::Red);
		if (!flagsonidoblancoranking)
		{
			flagsonidoblancoranking = true;
			sonido_boton_select.stop();
		}
	}
	if (botonsalir.contains(sf::Mouse::getPosition(*ventana1)))
	{
		menutext[2].setFillColor(Color::White);

		if (flagsonidoblancosalir)
		{
			flagsonidoblancosalir = false;
			sonido_boton_select.play();
		}
	}
	if (!(botonsalir.contains(sf::Mouse::getPosition(*ventana1))))
	{
		menutext[2].setFillColor(Color::Red);
		if (!flagsonidoblancosalir)
		{
			flagsonidoblancosalir = true;
			sonido_boton_select.stop();
		}
	}
}

void juego::menu_dibujar_efectoblanco_dificulad(IntRect botonfacil, IntRect botonmedia, IntRect botondificil)
{
	if (botonfacil.contains(sf::Mouse::getPosition(*ventana1)))
	{
		text_dif[0].setFillColor(Color::White);
		if (flagsonidoblancofacil)
		{
			flagsonidoblancofacil = false;
			sonido_boton_select.play();
		}
	}
	if (!(botonfacil.contains(sf::Mouse::getPosition(*ventana1))))
	{
		text_dif[0].setFillColor(Color::Red);
		if (!flagsonidoblancofacil)
		{
			flagsonidoblancofacil = true;
			sonido_boton_select.stop();
		}
	}
	if (botonmedia.contains(sf::Mouse::getPosition(*ventana1)))
	{
		text_dif[1].setFillColor(Color::White);
		if (flagsonidoblancomedia)
		{
			flagsonidoblancomedia = false;
			sonido_boton_select.play();
		}
	}
	if (!(botonmedia.contains(sf::Mouse::getPosition(*ventana1))))
	{
		text_dif[1].setFillColor(Color::Red);
		if (!flagsonidoblancomedia)
		{
			flagsonidoblancomedia = true;
			sonido_boton_select.stop();
		}
	}
	if (botondificil.contains(sf::Mouse::getPosition(*ventana1)))
	{
		text_dif[2].setFillColor(Color::White);
		if (flagsonidoblancodificil)
		{
			flagsonidoblancodificil = false;
			sonido_boton_select.play();
		}
	}
	if (!(botondificil.contains(sf::Mouse::getPosition(*ventana1))))
	{
		text_dif[2].setFillColor(Color::Red);
		if (!flagsonidoblancodificil)
		{
			flagsonidoblancodificil = true;
			sonido_boton_select.stop();
		}
	}
}

void juego::menu_dibujar_ranking(IntRect botonatras)
{
	spr_puntero1.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));
	spr_puntero2.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));


	if (botonatras.contains(sf::Mouse::getPosition(*ventana1)))
	{
		text_atras.setFillColor(Color::White);
		if (flagsonidoblancoatras)
		{
			flagsonidoblancoatras = false;
			sonido_boton_select.play();
		}
	}
		
	if (!(botonatras.contains(sf::Mouse::getPosition(*ventana1))))
	{
		text_atras.setFillColor(Color::Red);
		if (!flagsonidoblancoatras)
		{
			flagsonidoblancoatras = true;
			sonido_boton_select.stop();
		}
	}

	ventana1->draw(txt_rank[0]);
	ventana1->draw(txt_rank[1]);
	ventana1->draw(txt_rank[2]);
	ventana1->draw(txt_rank[3]);
	ventana1->draw(txt_rank[4]);
	ventana1->draw(txt_rank[5]);
	ventana1->draw(text_atras);
	ventana1->draw(spr_puntero1);
	ventana1->draw(spr_puntero2);
}


///MENU - MENU
void juego::menu_pressenter(Vector2f resolucion)
{
	
	while (!(Keyboard::isKeyPressed(Keyboard::Enter))) 
	{
		menu_dibujar_pressenter();
		if (Keyboard::isKeyPressed(Keyboard::Enter))
			menu_principal(resolucion);
	}

}

void juego::menu_escribirNombre(Vector2f resolucion)
{
	while (!Keyboard::isKeyPressed(Keyboard::Enter))
	{
		menu_dibujar_escribirNombre();

		while (ventana1->pollEvent(*eventos))
		{

			switch (eventos->type)
			{
			case Event::TextEntered:
				playerInput += eventos->text.unicode;
				playername.setString(playerInput);
				playername.setFont(zombiefont);
				playername.setPosition(Vector2f(350, 300));
				playername.setCharacterSize(50);
				playername.setOutlineColor(Color::Color(0, 0, 0, 255));
				playername.setOutlineThickness(1.5);
				break;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter)) 
		{
			
			char nombre[30];
			size_t length = playerInput.copy(nombre, playerInput.size() , 0);
			nombre[length] = '\0';
			ranking.set_nombre(nombre);

			playerInput = "";
			return;
		}

	}
	
}

void juego::menu_principal(Vector2f resolucion)
{
	IntRect botonjugar(menutext[0].getPosition().x, menutext[0].getPosition().y, menutext[0].getGlobalBounds().width, menutext[0].getGlobalBounds().height);
	IntRect botonranking(menutext[1].getPosition().x, menutext[1].getPosition().y, menutext[1].getGlobalBounds().width, menutext[1].getGlobalBounds().height);
	IntRect botonsalir(menutext[2].getPosition().x, menutext[2].getPosition().y, menutext[2].getGlobalBounds().width, menutext[2].getGlobalBounds().height);

	while (true)
	{
		menu_dibujar_principal(resolucion, botonjugar, botonranking, botonsalir);
		//menu_dibujar_efectoblanco(botonjugar, botonranking, botonsalir);
		

		
	}
}

void juego::menu_dificultad(Vector2f resolucion)
{
	IntRect botonfacil(text_dif[0].getPosition().x, text_dif[0].getPosition().y, text_dif[0].getGlobalBounds().width, text_dif[0].getGlobalBounds().height);
	IntRect botonmedia(text_dif[1].getPosition().x, text_dif[1].getPosition().y, text_dif[1].getGlobalBounds().width, text_dif[1].getGlobalBounds().height);
	IntRect botondificil(text_dif[2].getPosition().x, text_dif[2].getPosition().y, text_dif[2].getGlobalBounds().width, text_dif[2].getGlobalBounds().height);
	IntRect botonatras(text_atras.getPosition().x, text_atras.getPosition().y, text_atras.getGlobalBounds().width, text_atras.getGlobalBounds().height);

	spr_puntero1.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));
	spr_puntero2.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));
	ventana1->setMouseCursorVisible(false);
	ventana1->draw(spr_intro1);

	while (true)
	{
		menu_dibujar_dificultad();
		menu_dibujar_efectoblanco_dificulad(botonfacil, botonmedia, botondificil);
		

		if (!Mouse::isButtonPressed(Mouse::Left))
		{
			spr_puntero1.setColor(Color(255, 255, 255, 0));
			spr_puntero2.setColor(Color(255, 255, 255, 255));

			
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			spr_puntero1.setColor(Color(255, 255, 255, 255));
			spr_puntero2.setColor(Color(255, 255, 255, 0));
			
			

			if (botonfacil.contains(sf::Mouse::getPosition(*ventana1)))
			{
				contronda = 0;
				cantz = CANT_ZOMBIES;
				cancion_menu.stop();
				cancion_juego.play();
				game_over = false;
				gameloop(resolucion, 1);
				return;
			}
			if (botonmedia.contains(sf::Mouse::getPosition(*ventana1)))
			{
				contronda = 0;
				cantz = CANT_ZOMBIES + 2;
				cancion_menu.stop();
				cancion_juego.play();
				game_over = false;
				gameloop(resolucion, 2);
				return;
			}
			if (botondificil.contains(sf::Mouse::getPosition(*ventana1)))
			{
				contronda = 0;
				cantz = CANT_ZOMBIES + 4;
				cancion_menu.stop();
				cancion_juego.play();
				game_over = false;
				gameloop(resolucion, 3);
				return;
			}
		}
	}
}

void juego::menu_ranking() 
{
	IntRect botonatras(text_atras.getPosition().x, text_atras.getPosition().y, text_atras.getGlobalBounds().width, text_atras.getGlobalBounds().height);
	ordenar_ranking();
	int i = 0;
	while (true)
	{
		ventana1->clear();
		for (i = 0; i < 60; i++) 
		{
			ventana1->draw(txt_jugadores[i]);
		}
		menu_dibujar_ranking(botonatras);

		ventana1->display();
		
		if (!Mouse::isButtonPressed(Mouse::Left))
		{
			spr_puntero1.setColor(Color(255, 255, 255, 0));
			spr_puntero2.setColor(Color(255, 255, 255, 255));
		
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			spr_puntero1.setColor(Color(255, 255, 255, 255));
			spr_puntero2.setColor(Color(255, 255, 255, 0));
			if (botonatras.contains(sf::Mouse::getPosition(*ventana1)))
			{
				return;
			}
		}
	}
}

