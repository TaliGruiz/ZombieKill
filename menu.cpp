#include "menu.h"
menu::menu(float ancho, float alto, Font scaryfont) 
{
	menutext[0].setFont(scaryfont);
	menutext[0].setFillColor(Color::White);
	menutext[0].setString("JUGAR");
	menutext[0].setPosition(Vector2f(350, 50));
	menutext[0].setCharacterSize(50);
	menutext[0].setOutlineColor(Color::Color(0, 0, 0, 255));
	menutext[0].setOutlineThickness(1.5);

	menutext[1].setFont(scaryfont);
	menutext[1].setFillColor(Color::Red);
	menutext[1].setString("RANKING");
	menutext[1].setPosition(Vector2f(350, 250));
	menutext[1].setOutlineColor(Color::Color(0, 0, 0, 255));
	menutext[1].setOutlineThickness(1.5);

	menutext[2].setFont(scaryfont);
	menutext[2].setFillColor(Color::Red);
	menutext[2].setString("SALIR");
	menutext[2].setPosition(Vector2f(350, 450));
	menutext[2].setOutlineColor(Color::Color(0, 0, 0, 255));
	menutext[2].setOutlineThickness(1.5);
}

void menu::drawmain(RenderWindow *ventana1) 
{
	for (int i = 0; i < OPCIONES_MENU; i++) 
	{
		ventana1->draw(menutext[i]);
	}
}

void menu::menuloop(bool _menuloop) 
{

}