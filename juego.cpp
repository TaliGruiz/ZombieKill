#include "juego.h"
#include <iostream>
#include <dos.h>
using namespace std;

bool jugadorUp, jugadorDown, jugadorRight, jugadorLeft;
float angle, angle2, a, b, c, d;
Time delay = seconds(3);
zombie zombie1({ 200,300 }, 1, 20, 100);
survivor pj ( { 0,0 } ,1 ,1 );
RectangleShape borde1(Vector2f(800, 1));
RectangleShape borde2(Vector2f(6800, 1));
RectangleShape borde3(Vector2f(1, 600));
RectangleShape borde4(Vector2f(1, 600));
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
	gameloop(resolucion);
}
void juego::gameloop(Vector2f resolucion)
{
	
//	spr_survivor.setRotation(0);
	//spr_survivordisp.setRotation(0);
	while (!game_over)
	{
		*tiempo1 = reloj1->getElapsedTime();
		 
		if (tiempo1->asSeconds() > tiempo2 + fps)
		{
			tiempo2 = tiempo1->asSeconds();

			ventana1->clear();


			procesar_eventos();
			
			///survivor sigue al mouse
			a = pj.get_posicion().x - Mouse::getPosition(*ventana1).x;
			b = pj.get_posicion().y - Mouse::getPosition(*ventana1).y;
			angle = (-atan2(a, b) * 180 / 3.14) - 97;
			pj.rotar(angle);
			
			///zombie mira a survivor
			c = zombie1.get_posicion().x - pj.get_posicion().x;
			d = zombie1.get_posicion().y - pj.get_posicion().y;
			angle2 = (-atan2(c, d) * 180 / 3.14) - 170;
			zombie1.set_spr_zombie_rotation(angle2);

			float cantx, canty;
			
			// angle (in radians) between monster and player
			float angle3 = atan2(pj.get_posicion().y - zombie1.get_posicion().y, pj.get_posicion().x - zombie1.get_posicion().x);
			// monster.speed is the amount of pixels to move
			// If this doesn't work, invert cos for x and sin for y
			float ab= sin(angle) * 1;
			float cd= cos(angle) * 1;
			zombie1.update(ab, cd);
			

			/*
			///zombie sigue surv
			if (zombie1.get_posicion().x < pj.get_posicion().x)
			{
				cantx = (pj.get_posicion().x - zombie1.get_posicion().x); 
			}
			else 
				cantx = (zombie1.get_posicion().x - pj.get_posicion().x);

			if(zombie1.get_posicion().y < pj.get_posicion().y)
				canty = (zombie1.get_posicion().y - pj.get_posicion().y);
			else
				canty = (pj.get_posicion().y - zombie1.get_posicion().y);
			*/		
			//zombie1.mover({ cantx, canty });
			

			///ventana1->draw(spr_intro1);


			ventana1->draw(spr_fondo);

			ventana1->draw(pj.get_spr_survivordisparo());
			
			//ventana1->draw(pj.get_spr_survivor());
			
			ventana1->draw(zombie1.get_spr_zombie());


			ventana1->draw(spr_mira);
			
			ventana1->draw(borde1); ventana1->draw(borde2); ventana1->draw(borde3); ventana1->draw(borde4);
			borde1.setPosition(Vector2f(0, 0));
			borde2.setPosition(Vector2f(0, 600));
			borde3.setPosition(Vector2f(800, 0));
			borde4.setPosition(Vector2f(800, 600));
			borde1.setFillColor(Color(255,255,255,0));
			borde2.setFillColor(Color(255, 255, 255, 0));
			borde3.setFillColor(Color(255, 255, 255, 0));
			borde4.setFillColor(Color(255, 255, 255, 0));

			if(Collision::PixelPerfectTest(pj.get_spr_survivor(), zombie1.get_spr_zombie()))
			{
				cout << "colision" << endl;
			}
			else { cout << "no colision" << endl; }
			
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
			pj.update(jugadorUp, jugadorDown, jugadorRight, jugadorLeft);
			pj.mover(Vector2f(pj.get_velocidad().x, pj.get_velocidad().y));
			
			///procesar colision
			procesar_colision(resolucion);

		}
	}

}

void juego::procesar_colision(Vector2f resolucion) 
{	/*
	//Colision ventana sprite survivor
	//Colision izquierda
	if (spr_survivor.getPosition().x <= 33.f) {
		spr_survivor.setPosition(33.f, spr_survivor.getPosition().y);
	}
	//Colision arriba
	if (spr_survivor.getPosition().y <= 33.f) {
		spr_survivor.setPosition(spr_survivor.getPosition().x, 33.f);
	}
	//Colision derecha
	if (spr_survivor.getPosition().x + spr_survivor.getGlobalBounds().width >= (resolucion.x + 39.f)) {
		spr_survivor.setPosition((resolucion.x + 39.f) - spr_survivor.getGlobalBounds().width, spr_survivor.getPosition().y);
	}
	//Colision abajo
	if (spr_survivor.getPosition().y + spr_survivor.getGlobalBounds().height >= (resolucion.y + 39.f)) {
		spr_survivor.setPosition(spr_survivor.getPosition().x, (resolucion.y + 39.f) - spr_survivor.getGlobalBounds().height);
	}

	//Colision ventana sprite survivordisp
	//Colision izquierda
	if (spr_survivordisp.getPosition().x <= 33.f) {
		spr_survivordisp.setPosition(33.f, spr_survivordisp.getPosition().y);
	}
	//Colision arriba
	if (spr_survivordisp.getPosition().y <= 33.f) {
		spr_survivordisp.setPosition(spr_survivordisp.getPosition().x, 33.f);
	}
	//Colision derecha
	if (spr_survivordisp.getPosition().x + spr_survivordisp.getGlobalBounds().width >= (resolucion.x + 39.f)) {
		spr_survivordisp.setPosition((resolucion.x + 39.f) - spr_survivordisp.getGlobalBounds().width, spr_survivordisp.getPosition().y);
	}
	//Colision abajo
	if (spr_survivordisp.getPosition().y + spr_survivordisp.getGlobalBounds().height >= (resolucion.y + 39.f)) {
		spr_survivordisp.setPosition(spr_survivordisp.getPosition().x, (resolucion.y + 39.f) - spr_survivordisp.getGlobalBounds().height);
	}*/
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
	spr_blanco.setColor(Color(255, 255, 255, 0));

	text_fondo.loadFromFile("imagenes/fondo.jpg");
	spr_fondo.setTexture(text_fondo);
	spr_fondo.setScale((float)ventana1->getSize().x / text_fondo.getSize().x, (float)ventana1->getSize().y / text_fondo.getSize().y);
	
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
					pj.color_aprietodisparo();
					sonidoDisparo.play();
					
					if (Mouse::isButtonPressed(Mouse::Left)) {
						sonidoDisparo.setLoop(true);
						sonidoDisparo.setPitch(7);
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
					pj.color_sueltodisparo();
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
