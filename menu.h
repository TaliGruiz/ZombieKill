#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "SFML\System.hpp"
using namespace std;
using namespace sf;
#define OPCIONES_MENU 3
class menu
{
public:
	menu(float, float,Font);
	void moveUp();
	void moveDown();
	void draw(RenderWindow*);
private:
	Text menutext[OPCIONES_MENU];
};

