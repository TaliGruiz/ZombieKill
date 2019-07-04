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
	
	void ordenar_ranking() 
	{
		score obj, * vecobj, aux;
		int pos = 0, cantreg = 0, i = 0, j, posmin;

		while (obj.leerdedisco(pos++)) 
		{
			cantreg++;
		}

		vecobj = new score[cantreg];

		pos = 0;
		
		while (obj.leerdedisco(pos++))
		{
			vecobj[i] = obj;
			i++;
		}
		
		for (i = 0; i < cantreg - 1; i++) 
		{
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
		
		switch (cantreg) 
		{
		case 1:

			txt_jugadores[0].setString(to_string(1));
			txt_jugadores[1].setString(vecobj[0].get_nombre());
			txt_jugadores[2].setString(to_string(vecobj[0].get_rondas()));
			txt_jugadores[3].setString(to_string(vecobj[0].get_tiros()));
			txt_jugadores[4].setString(to_string(vecobj[0].get_tirosacertados()));
			txt_jugadores[5].setString(to_string(vecobj[0].get_accuracy()));
			break;
		
		case 2:
			txt_jugadores[0].setString(to_string(1));
			txt_jugadores[1].setString(vecobj[0].get_nombre());
			txt_jugadores[2].setString(to_string(vecobj[0].get_rondas()));
			txt_jugadores[3].setString(to_string(vecobj[0].get_tiros()));
			txt_jugadores[4].setString(to_string(vecobj[0].get_tirosacertados()));
			txt_jugadores[5].setString(to_string(vecobj[0].get_accuracy()));

			txt_jugadores[6].setString(to_string(2));
			txt_jugadores[7].setString(vecobj[1].get_nombre());
			txt_jugadores[8].setString(to_string(vecobj[1].get_rondas()));
			txt_jugadores[9].setString(to_string(vecobj[1].get_tiros()));
			txt_jugadores[10].setString(to_string(vecobj[1].get_tirosacertados()));
			txt_jugadores[11].setString(to_string(vecobj[1].get_accuracy()));
			break;
		
		case 3:
			txt_jugadores[0].setString(to_string(1));
			txt_jugadores[1].setString(vecobj[0].get_nombre());
			txt_jugadores[2].setString(to_string(vecobj[0].get_rondas()));
			txt_jugadores[3].setString(to_string(vecobj[0].get_tiros()));
			txt_jugadores[4].setString(to_string(vecobj[0].get_tirosacertados()));
			txt_jugadores[5].setString(to_string(vecobj[0].get_accuracy()));

			txt_jugadores[6].setString(to_string(2));
			txt_jugadores[7].setString(vecobj[1].get_nombre());
			txt_jugadores[8].setString(to_string(vecobj[1].get_rondas()));
			txt_jugadores[9].setString(to_string(vecobj[1].get_tiros()));
			txt_jugadores[10].setString(to_string(vecobj[1].get_tirosacertados()));
			txt_jugadores[11].setString(to_string(vecobj[1].get_accuracy()));

			txt_jugadores[12].setString(to_string(3));
			txt_jugadores[13].setString(vecobj[2].get_nombre());
			txt_jugadores[14].setString(to_string(vecobj[2].get_rondas()));
			txt_jugadores[15].setString(to_string(vecobj[2].get_tiros()));
			txt_jugadores[16].setString(to_string(vecobj[2].get_tirosacertados()));
			txt_jugadores[17].setString(to_string(vecobj[2].get_accuracy()));
			break;
		
		case 4:
			txt_jugadores[0].setString(to_string(1));
			txt_jugadores[1].setString(vecobj[0].get_nombre());
			txt_jugadores[2].setString(to_string(vecobj[0].get_rondas()));
			txt_jugadores[3].setString(to_string(vecobj[0].get_tiros()));
			txt_jugadores[4].setString(to_string(vecobj[0].get_tirosacertados()));
			txt_jugadores[5].setString(to_string(vecobj[0].get_accuracy()));

			txt_jugadores[6].setString(to_string(2));
			txt_jugadores[7].setString(vecobj[1].get_nombre());
			txt_jugadores[8].setString(to_string(vecobj[1].get_rondas()));
			txt_jugadores[9].setString(to_string(vecobj[1].get_tiros()));
			txt_jugadores[10].setString(to_string(vecobj[1].get_tirosacertados()));
			txt_jugadores[11].setString(to_string(vecobj[1].get_accuracy()));

			txt_jugadores[12].setString(to_string(3));
			txt_jugadores[13].setString(vecobj[2].get_nombre());
			txt_jugadores[14].setString(to_string(vecobj[2].get_rondas()));
			txt_jugadores[15].setString(to_string(vecobj[2].get_tiros()));
			txt_jugadores[16].setString(to_string(vecobj[2].get_tirosacertados()));
			txt_jugadores[17].setString(to_string(vecobj[2].get_accuracy()));

			txt_jugadores[18].setString(to_string(4));
			txt_jugadores[19].setString(vecobj[3].get_nombre());
			txt_jugadores[20].setString(to_string(vecobj[3].get_rondas()));
			txt_jugadores[21].setString(to_string(vecobj[3].get_tiros()));
			txt_jugadores[22].setString(to_string(vecobj[3].get_tirosacertados()));
			txt_jugadores[23].setString(to_string(vecobj[3].get_accuracy()));
			break;
		
		case 5:
			txt_jugadores[0].setString(to_string(1));
			txt_jugadores[1].setString(vecobj[0].get_nombre());
			txt_jugadores[2].setString(to_string(vecobj[0].get_rondas()));
			txt_jugadores[3].setString(to_string(vecobj[0].get_tiros()));
			txt_jugadores[4].setString(to_string(vecobj[0].get_tirosacertados()));
			txt_jugadores[5].setString(to_string(vecobj[0].get_accuracy()));

			txt_jugadores[6].setString(to_string(2));
			txt_jugadores[7].setString(vecobj[1].get_nombre());
			txt_jugadores[8].setString(to_string(vecobj[1].get_rondas()));
			txt_jugadores[9].setString(to_string(vecobj[1].get_tiros()));
			txt_jugadores[10].setString(to_string(vecobj[1].get_tirosacertados()));
			txt_jugadores[11].setString(to_string(vecobj[1].get_accuracy()));

			txt_jugadores[12].setString(to_string(3));
			txt_jugadores[13].setString(vecobj[2].get_nombre());
			txt_jugadores[14].setString(to_string(vecobj[2].get_rondas()));
			txt_jugadores[15].setString(to_string(vecobj[2].get_tiros()));
			txt_jugadores[16].setString(to_string(vecobj[2].get_tirosacertados()));
			txt_jugadores[17].setString(to_string(vecobj[2].get_accuracy()));

			txt_jugadores[18].setString(to_string(4));
			txt_jugadores[19].setString(vecobj[3].get_nombre());
			txt_jugadores[20].setString(to_string(vecobj[3].get_rondas()));
			txt_jugadores[21].setString(to_string(vecobj[3].get_tiros()));
			txt_jugadores[22].setString(to_string(vecobj[3].get_tirosacertados()));
			txt_jugadores[23].setString(to_string(vecobj[3].get_accuracy()));

			txt_jugadores[24].setString(to_string(5));
			txt_jugadores[25].setString(vecobj[4].get_nombre());
			txt_jugadores[26].setString(to_string(vecobj[4].get_rondas()));
			txt_jugadores[27].setString(to_string(vecobj[4].get_tiros()));
			txt_jugadores[28].setString(to_string(vecobj[4].get_tirosacertados()));
			txt_jugadores[29].setString(to_string(vecobj[4].get_accuracy()));
			break;
		case 6:
			txt_jugadores[0].setString(to_string(1));
			txt_jugadores[1].setString(vecobj[0].get_nombre());
			txt_jugadores[2].setString(to_string(vecobj[0].get_rondas()));
			txt_jugadores[3].setString(to_string(vecobj[0].get_tiros()));
			txt_jugadores[4].setString(to_string(vecobj[0].get_tirosacertados()));
			txt_jugadores[5].setString(to_string(vecobj[0].get_accuracy()));

			txt_jugadores[6].setString(to_string(2));
			txt_jugadores[7].setString(vecobj[1].get_nombre());
			txt_jugadores[8].setString(to_string(vecobj[1].get_rondas()));
			txt_jugadores[9].setString(to_string(vecobj[1].get_tiros()));
			txt_jugadores[10].setString(to_string(vecobj[1].get_tirosacertados()));
			txt_jugadores[11].setString(to_string(vecobj[1].get_accuracy()));

			txt_jugadores[12].setString(to_string(3));
			txt_jugadores[13].setString(vecobj[2].get_nombre());
			txt_jugadores[14].setString(to_string(vecobj[2].get_rondas()));
			txt_jugadores[15].setString(to_string(vecobj[2].get_tiros()));
			txt_jugadores[16].setString(to_string(vecobj[2].get_tirosacertados()));
			txt_jugadores[17].setString(to_string(vecobj[2].get_accuracy()));

			txt_jugadores[18].setString(to_string(4));
			txt_jugadores[19].setString(vecobj[3].get_nombre());
			txt_jugadores[20].setString(to_string(vecobj[3].get_rondas()));
			txt_jugadores[21].setString(to_string(vecobj[3].get_tiros()));
			txt_jugadores[22].setString(to_string(vecobj[3].get_tirosacertados()));
			txt_jugadores[23].setString(to_string(vecobj[3].get_accuracy()));

			txt_jugadores[24].setString(to_string(5));
			txt_jugadores[25].setString(vecobj[4].get_nombre());
			txt_jugadores[26].setString(to_string(vecobj[4].get_rondas()));
			txt_jugadores[27].setString(to_string(vecobj[4].get_tiros()));
			txt_jugadores[28].setString(to_string(vecobj[4].get_tirosacertados()));
			txt_jugadores[29].setString(to_string(vecobj[4].get_accuracy()));

			txt_jugadores[30].setString(to_string(6));
			txt_jugadores[31].setString(vecobj[4].get_nombre());
			txt_jugadores[32].setString(to_string(vecobj[5].get_rondas()));
			txt_jugadores[33].setString(to_string(vecobj[5].get_tiros()));
			txt_jugadores[34].setString(to_string(vecobj[5].get_tirosacertados()));
			txt_jugadores[35].setString(to_string(vecobj[5].get_accuracy()));
			break;

		case 7:
			txt_jugadores[0].setString(to_string(1));
			txt_jugadores[1].setString(vecobj[0].get_nombre());
			txt_jugadores[2].setString(to_string(vecobj[0].get_rondas()));
			txt_jugadores[3].setString(to_string(vecobj[0].get_tiros()));
			txt_jugadores[4].setString(to_string(vecobj[0].get_tirosacertados()));
			txt_jugadores[5].setString(to_string(vecobj[0].get_accuracy()));

			txt_jugadores[6].setString(to_string(2));
			txt_jugadores[7].setString(vecobj[1].get_nombre());
			txt_jugadores[8].setString(to_string(vecobj[1].get_rondas()));
			txt_jugadores[9].setString(to_string(vecobj[1].get_tiros()));
			txt_jugadores[10].setString(to_string(vecobj[1].get_tirosacertados()));
			txt_jugadores[11].setString(to_string(vecobj[1].get_accuracy()));

			txt_jugadores[12].setString(to_string(3));
			txt_jugadores[13].setString(vecobj[2].get_nombre());
			txt_jugadores[14].setString(to_string(vecobj[2].get_rondas()));
			txt_jugadores[15].setString(to_string(vecobj[2].get_tiros()));
			txt_jugadores[16].setString(to_string(vecobj[2].get_tirosacertados()));
			txt_jugadores[17].setString(to_string(vecobj[2].get_accuracy()));

			txt_jugadores[18].setString(to_string(4));
			txt_jugadores[19].setString(vecobj[3].get_nombre());
			txt_jugadores[20].setString(to_string(vecobj[3].get_rondas()));
			txt_jugadores[21].setString(to_string(vecobj[3].get_tiros()));
			txt_jugadores[22].setString(to_string(vecobj[3].get_tirosacertados()));
			txt_jugadores[23].setString(to_string(vecobj[3].get_accuracy()));

			txt_jugadores[24].setString(to_string(5));
			txt_jugadores[25].setString(vecobj[4].get_nombre());
			txt_jugadores[26].setString(to_string(vecobj[4].get_rondas()));
			txt_jugadores[27].setString(to_string(vecobj[4].get_tiros()));
			txt_jugadores[28].setString(to_string(vecobj[4].get_tirosacertados()));
			txt_jugadores[29].setString(to_string(vecobj[4].get_accuracy()));

			txt_jugadores[30].setString(to_string(6));
			txt_jugadores[31].setString(vecobj[5].get_nombre());
			txt_jugadores[32].setString(to_string(vecobj[5].get_rondas()));
			txt_jugadores[33].setString(to_string(vecobj[5].get_tiros()));
			txt_jugadores[34].setString(to_string(vecobj[5].get_tirosacertados()));
			txt_jugadores[35].setString(to_string(vecobj[5].get_accuracy()));

			txt_jugadores[36].setString(to_string(7));
			txt_jugadores[37].setString(vecobj[6].get_nombre());
			txt_jugadores[38].setString(to_string(vecobj[6].get_rondas()));
			txt_jugadores[39].setString(to_string(vecobj[6].get_tiros()));
			txt_jugadores[40].setString(to_string(vecobj[6].get_tirosacertados()));
			txt_jugadores[41].setString(to_string(vecobj[6].get_accuracy()));
			break;

		case 8:
			txt_jugadores[0].setString(to_string(1));
			txt_jugadores[1].setString(vecobj[0].get_nombre());
			txt_jugadores[2].setString(to_string(vecobj[0].get_rondas()));
			txt_jugadores[3].setString(to_string(vecobj[0].get_tiros()));
			txt_jugadores[4].setString(to_string(vecobj[0].get_tirosacertados()));
			txt_jugadores[5].setString(to_string(vecobj[0].get_accuracy()));

			txt_jugadores[6].setString(to_string(2));
			txt_jugadores[7].setString(vecobj[1].get_nombre());
			txt_jugadores[8].setString(to_string(vecobj[1].get_rondas()));
			txt_jugadores[9].setString(to_string(vecobj[1].get_tiros()));
			txt_jugadores[10].setString(to_string(vecobj[1].get_tirosacertados()));
			txt_jugadores[11].setString(to_string(vecobj[1].get_accuracy()));

			txt_jugadores[12].setString(to_string(3));
			txt_jugadores[13].setString(vecobj[2].get_nombre());
			txt_jugadores[14].setString(to_string(vecobj[2].get_rondas()));
			txt_jugadores[15].setString(to_string(vecobj[2].get_tiros()));
			txt_jugadores[16].setString(to_string(vecobj[2].get_tirosacertados()));
			txt_jugadores[17].setString(to_string(vecobj[2].get_accuracy()));

			txt_jugadores[18].setString(to_string(4));
			txt_jugadores[19].setString(vecobj[3].get_nombre());
			txt_jugadores[20].setString(to_string(vecobj[3].get_rondas()));
			txt_jugadores[21].setString(to_string(vecobj[3].get_tiros()));
			txt_jugadores[22].setString(to_string(vecobj[3].get_tirosacertados()));
			txt_jugadores[23].setString(to_string(vecobj[3].get_accuracy()));

			txt_jugadores[24].setString(to_string(5));
			txt_jugadores[25].setString(vecobj[4].get_nombre());
			txt_jugadores[26].setString(to_string(vecobj[4].get_rondas()));
			txt_jugadores[27].setString(to_string(vecobj[4].get_tiros()));
			txt_jugadores[28].setString(to_string(vecobj[4].get_tirosacertados()));
			txt_jugadores[29].setString(to_string(vecobj[4].get_accuracy()));

			txt_jugadores[30].setString(to_string(6));
			txt_jugadores[31].setString(vecobj[5].get_nombre());
			txt_jugadores[32].setString(to_string(vecobj[5].get_rondas()));
			txt_jugadores[33].setString(to_string(vecobj[5].get_tiros()));
			txt_jugadores[34].setString(to_string(vecobj[5].get_tirosacertados()));
			txt_jugadores[35].setString(to_string(vecobj[5].get_accuracy()));

			txt_jugadores[36].setString(to_string(7));
			txt_jugadores[37].setString(vecobj[6].get_nombre());
			txt_jugadores[38].setString(to_string(vecobj[6].get_rondas()));
			txt_jugadores[39].setString(to_string(vecobj[6].get_tiros()));
			txt_jugadores[40].setString(to_string(vecobj[6].get_tirosacertados()));
			txt_jugadores[41].setString(to_string(vecobj[6].get_accuracy()));

			txt_jugadores[42].setString(to_string(8));
			txt_jugadores[43].setString(vecobj[7].get_nombre());
			txt_jugadores[43].setString(to_string(vecobj[7].get_rondas()));
			txt_jugadores[45].setString(to_string(vecobj[7].get_tiros()));
			txt_jugadores[46].setString(to_string(vecobj[7].get_tirosacertados()));
			txt_jugadores[47].setString(to_string(vecobj[7].get_accuracy()));
			break;

		case 9:
			txt_jugadores[0].setString(to_string(1));
			txt_jugadores[1].setString(vecobj[0].get_nombre());
			txt_jugadores[2].setString(to_string(vecobj[0].get_rondas()));
			txt_jugadores[3].setString(to_string(vecobj[0].get_tiros()));
			txt_jugadores[4].setString(to_string(vecobj[0].get_tirosacertados()));
			txt_jugadores[5].setString(to_string(vecobj[0].get_accuracy()));

			txt_jugadores[6].setString(to_string(2));
			txt_jugadores[7].setString(vecobj[1].get_nombre());
			txt_jugadores[8].setString(to_string(vecobj[1].get_rondas()));
			txt_jugadores[9].setString(to_string(vecobj[1].get_tiros()));
			txt_jugadores[10].setString(to_string(vecobj[1].get_tirosacertados()));
			txt_jugadores[11].setString(to_string(vecobj[1].get_accuracy()));

			txt_jugadores[12].setString(to_string(3));
			txt_jugadores[13].setString(vecobj[2].get_nombre());
			txt_jugadores[14].setString(to_string(vecobj[2].get_rondas()));
			txt_jugadores[15].setString(to_string(vecobj[2].get_tiros()));
			txt_jugadores[16].setString(to_string(vecobj[2].get_tirosacertados()));
			txt_jugadores[17].setString(to_string(vecobj[2].get_accuracy()));

			txt_jugadores[18].setString(to_string(4));
			txt_jugadores[19].setString(vecobj[3].get_nombre());
			txt_jugadores[20].setString(to_string(vecobj[3].get_rondas()));
			txt_jugadores[21].setString(to_string(vecobj[3].get_tiros()));
			txt_jugadores[22].setString(to_string(vecobj[3].get_tirosacertados()));
			txt_jugadores[23].setString(to_string(vecobj[3].get_accuracy()));

			txt_jugadores[24].setString(to_string(5));
			txt_jugadores[25].setString(vecobj[4].get_nombre());
			txt_jugadores[26].setString(to_string(vecobj[4].get_rondas()));
			txt_jugadores[27].setString(to_string(vecobj[4].get_tiros()));
			txt_jugadores[28].setString(to_string(vecobj[4].get_tirosacertados()));
			txt_jugadores[29].setString(to_string(vecobj[4].get_accuracy()));

			txt_jugadores[30].setString(to_string(6));
			txt_jugadores[31].setString(vecobj[5].get_nombre());
			txt_jugadores[32].setString(to_string(vecobj[5].get_rondas()));
			txt_jugadores[33].setString(to_string(vecobj[5].get_tiros()));
			txt_jugadores[34].setString(to_string(vecobj[5].get_tirosacertados()));
			txt_jugadores[35].setString(to_string(vecobj[5].get_accuracy()));

			txt_jugadores[36].setString(to_string(7));
			txt_jugadores[37].setString(vecobj[6].get_nombre());
			txt_jugadores[38].setString(to_string(vecobj[6].get_rondas()));
			txt_jugadores[39].setString(to_string(vecobj[6].get_tiros()));
			txt_jugadores[40].setString(to_string(vecobj[6].get_tirosacertados()));
			txt_jugadores[41].setString(to_string(vecobj[6].get_accuracy()));

			txt_jugadores[42].setString(to_string(8));
			txt_jugadores[43].setString(vecobj[7].get_nombre());
			txt_jugadores[43].setString(to_string(vecobj[7].get_rondas()));
			txt_jugadores[45].setString(to_string(vecobj[7].get_tiros()));
			txt_jugadores[46].setString(to_string(vecobj[7].get_tirosacertados()));
			txt_jugadores[47].setString(to_string(vecobj[7].get_accuracy()));

			txt_jugadores[48].setString(to_string(9));
			txt_jugadores[49].setString(vecobj[7].get_nombre());
			txt_jugadores[50].setString(to_string(vecobj[8].get_rondas()));
			txt_jugadores[51].setString(to_string(vecobj[8].get_tiros()));
			txt_jugadores[52].setString(to_string(vecobj[8].get_tirosacertados()));
			txt_jugadores[53].setString(to_string(vecobj[8].get_accuracy()));
			break;

		case 10:
			txt_jugadores[0].setString(to_string(1));
			txt_jugadores[1].setString(vecobj[0].get_nombre());
			txt_jugadores[2].setString(to_string(vecobj[0].get_rondas()));
			txt_jugadores[3].setString(to_string(vecobj[0].get_tiros()));
			txt_jugadores[4].setString(to_string(vecobj[0].get_tirosacertados()));
			txt_jugadores[5].setString(to_string(vecobj[0].get_accuracy()));

			txt_jugadores[6].setString(to_string(2));
			txt_jugadores[7].setString(vecobj[1].get_nombre());
			txt_jugadores[8].setString(to_string(vecobj[1].get_rondas()));
			txt_jugadores[9].setString(to_string(vecobj[1].get_tiros()));
			txt_jugadores[10].setString(to_string(vecobj[1].get_tirosacertados()));
			txt_jugadores[11].setString(to_string(vecobj[1].get_accuracy()));

			txt_jugadores[12].setString(to_string(3));
			txt_jugadores[13].setString(vecobj[2].get_nombre());
			txt_jugadores[14].setString(to_string(vecobj[2].get_rondas()));
			txt_jugadores[15].setString(to_string(vecobj[2].get_tiros()));
			txt_jugadores[16].setString(to_string(vecobj[2].get_tirosacertados()));
			txt_jugadores[17].setString(to_string(vecobj[2].get_accuracy()));

			txt_jugadores[18].setString(to_string(4));
			txt_jugadores[19].setString(vecobj[3].get_nombre());
			txt_jugadores[20].setString(to_string(vecobj[3].get_rondas()));
			txt_jugadores[21].setString(to_string(vecobj[3].get_tiros()));
			txt_jugadores[22].setString(to_string(vecobj[3].get_tirosacertados()));
			txt_jugadores[23].setString(to_string(vecobj[3].get_accuracy()));

			txt_jugadores[24].setString(to_string(5));
			txt_jugadores[25].setString(vecobj[4].get_nombre());
			txt_jugadores[26].setString(to_string(vecobj[4].get_rondas()));
			txt_jugadores[27].setString(to_string(vecobj[4].get_tiros()));
			txt_jugadores[28].setString(to_string(vecobj[4].get_tirosacertados()));
			txt_jugadores[29].setString(to_string(vecobj[4].get_accuracy()));

			txt_jugadores[30].setString(to_string(6));
			txt_jugadores[31].setString(vecobj[5].get_nombre());
			txt_jugadores[32].setString(to_string(vecobj[5].get_rondas()));
			txt_jugadores[33].setString(to_string(vecobj[5].get_tiros()));
			txt_jugadores[34].setString(to_string(vecobj[5].get_tirosacertados()));
			txt_jugadores[35].setString(to_string(vecobj[5].get_accuracy()));

			txt_jugadores[36].setString(to_string(7));
			txt_jugadores[37].setString(vecobj[6].get_nombre());
			txt_jugadores[38].setString(to_string(vecobj[6].get_rondas()));
			txt_jugadores[39].setString(to_string(vecobj[6].get_tiros()));
			txt_jugadores[40].setString(to_string(vecobj[6].get_tirosacertados()));
			txt_jugadores[41].setString(to_string(vecobj[6].get_accuracy()));

			txt_jugadores[42].setString(to_string(8));
			txt_jugadores[43].setString(vecobj[7].get_nombre());
			txt_jugadores[43].setString(to_string(vecobj[7].get_rondas()));
			txt_jugadores[45].setString(to_string(vecobj[7].get_tiros()));
			txt_jugadores[46].setString(to_string(vecobj[7].get_tirosacertados()));
			txt_jugadores[47].setString(to_string(vecobj[7].get_accuracy()));

			txt_jugadores[48].setString(to_string(9));
			txt_jugadores[49].setString(vecobj[8].get_nombre());
			txt_jugadores[50].setString(to_string(vecobj[8].get_rondas()));
			txt_jugadores[51].setString(to_string(vecobj[8].get_tiros()));
			txt_jugadores[52].setString(to_string(vecobj[8].get_tirosacertados()));
			txt_jugadores[53].setString(to_string(vecobj[8].get_accuracy()));

			txt_jugadores[54].setString(to_string(10));
			txt_jugadores[55].setString(vecobj[9].get_nombre());
			txt_jugadores[56].setString(to_string(vecobj[9].get_rondas()));
			txt_jugadores[57].setString(to_string(vecobj[9].get_tiros()));
			txt_jugadores[58].setString(to_string(vecobj[9].get_tirosacertados()));
			txt_jugadores[59].setString(to_string(vecobj[9].get_accuracy()));

			break;
		}

	
		delete vecobj;	
	}
	
	
private:
	bullet b1;
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
	SoundBuffer Buffsonido_boton_pass;
	Sound sonido_boton_select;
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
	Text txt_jugadores[60];

	string playerInput;

	Text playername;
	
	///Event
	Event* eventos;

	///flags
	bool flagsonidoblancojugar = true;
	bool flagsonidoblancoranking = true;
	bool flagsonidoblancosalir = true;
	bool flagsonidoblancofacil = true;
	bool flagsonidoblancomedia = true;
	bool flagsonidoblancodificil = true;
	bool flagsonidoblancoatras = true;
	bool deletebala = false;
	bool spr_zombie_flag = false;
	bool flag = true;

	//contadores
	int cantz;
	int contronda = 1;
	int rank_canttiros, rank_rondas = 1, rank_tirosacertados;
	float rank_accuracy;

	///game over
	bool game_over = false;
	///menu loop
	bool menuloop = true;
};