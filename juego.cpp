#include "juego.h"
#include <iostream>

using namespace std;

juego::juego(Vector2f resolucion, String titulo)
{

	game_over = false;
	mousemueve = new Event;

	fps = 60;
	ventana1 = new RenderWindow (VideoMode(resolucion.x, resolucion.y), titulo);
	//ventana1->setFramerateLimit(fps);
	ventana1->setMouseCursorVisible(false);
	cargar_graficos();
	gameloop();
}

void juego::gameloop()
{
	while (!game_over)
	{

		ventana1->clear();

		procesar_eventos();
		


		ventana1->draw(spr_fondo);
		ventana1->draw(spr_survirordisp);
		//spr_survirordisp.setColor(Color::Transparent);
		ventana1->draw(spr_mira);
		ventana1->draw(spr_surviror);
		ventana1->display();
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
	spr_survirordisp.setTexture(text_survirordisp);
	
	text_survivor.loadFromFile("imagenes/survivor.png");
	spr_surviror.setTexture(text_survivor);

}

void juego::procesar_eventos()
{
	while (ventana1->pollEvent(*mousemueve))
	{
		switch (mousemueve->type)
		{
		case Event::MouseMoved:
			
			spr_mira.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));
			break;
		case Event::KeyPressed:
			if (Keyboard::isKeyPressed(Keyboard::W)) { cout << "W" << endl; }
			if (!Keyboard::isKeyPressed(Keyboard::W)) {  }
			if (Keyboard::isKeyPressed(Keyboard::S)) { cout << "S" << endl; }
			if (!Keyboard::isKeyPressed(Keyboard::S)) { }
			if (Keyboard::isKeyPressed(Keyboard::D)) { cout << "D" << endl; }
			if (!Keyboard::isKeyPressed(Keyboard::D)) {  }
			if (Keyboard::isKeyPressed(Keyboard::A)) { cout << "A" << endl; }
			if (!Keyboard::isKeyPressed(Keyboard::A)) {  }
			//
			break;

		case Event::MouseButtonPressed:
			if (Mouse::isButtonPressed(Mouse::Left)) {
				cout << "Mouse Boton Izquierdo" << endl;

				//spr_surviror.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));
				ventana1->draw(spr_survirordisp);
				spr_survirordisp.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));
				
			}
			break;

		case Event::MouseButtonReleased:
			if (Mouse::Button::Left) {
				//spr_survirordisp.setColor(Color::Transparent);
				
				spr_surviror.setPosition((Vector2f)(Mouse::getPosition(*ventana1)));
			}
				break;
			
		}
	}
}
