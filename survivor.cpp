#include "juego.h"
#include "survivor.h"
using namespace std;
using namespace sf;


void survivor::set_spr_survivor()
{
	text_survivor.loadFromFile("imagenes/survivor2.png");
	spr_survivor.setTexture(text_survivor);
	spr_survivor.setOrigin(30.f, 18.5);
}

void survivor::set_spr_survivordisparo()
{
	text_survivordisparo.loadFromFile("imagenes/survivorshoot2.png");
	spr_survivordisparo.setTexture(text_survivordisparo);
	spr_survivordisparo.setOrigin(30.f, 18.5);
	spr_survivordisparo.setColor(Color(255, 255, 255, 0));
}

survivor::survivor(Vector2f _pos, float _life)
{
	set_spr_survivor();
	set_spr_survivordisparo();
	spr_survivor.setPosition(_pos);
	spr_survivordisparo.setPosition(_pos);
	posicion = _pos;
	set_life(_life);
	currHp = life;
}

void survivor::update(bool jugadorUp, bool jugadorDown, bool jugadorRight, bool jugadorLeft) {

	float speed = 2;

	if (jugadorRight) {
		velocidad.x = speed;
	}
	if (jugadorLeft) {
		velocidad.x = -speed;
	}
	if (jugadorDown) {
		velocidad.y = speed;
	}
	if (jugadorUp) {
		velocidad.y = -speed;
	}
	if (!(jugadorRight || jugadorLeft)) {
		velocidad.x = 0;
	}
	if (!(jugadorUp || jugadorDown)) {
		velocidad.y = 0;
	}
	posicion.x += velocidad.x;
	posicion.y += velocidad.y;
}

void survivor::update_joystick() 
{
	int speed = 2;
	float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	x += speed;
	y += speed;
	mover(Vector2f(x, y));
}
void survivor::mover( Vector2f _mov)
{
	spr_survivor.move(Vector2f(_mov));
	spr_survivordisparo.move(Vector2f(_mov));
}

void survivor::rotar(float _angle)
{
	spr_survivor.setRotation(_angle);
	spr_survivordisparo.setRotation(_angle);
}

void survivor::colisionVentana(Vector2f resolucion) {
	//Colision ventana sprite survivor
	//Colision izquierda
	if (spr_survivor.getPosition().x <= 33.f) {
		spr_survivor.setPosition(33.f, spr_survivor.getPosition().y);
		posicion.x = 33.f;
	}
	//Colision arriba
	if (spr_survivor.getPosition().y <= 33.f) {
		spr_survivor.setPosition(spr_survivor.getPosition().x, 33.f);
		posicion.y = 33.f;
	}
	//Colision derecha
	if (spr_survivor.getPosition().x + spr_survivor.getGlobalBounds().width >= (resolucion.x + 39.f)) {
		spr_survivor.setPosition((resolucion.x + 39.f) - spr_survivor.getGlobalBounds().width, spr_survivor.getPosition().y);
		posicion.x = (resolucion.x + 39.f) - spr_survivor.getGlobalBounds().width;
	}
	//Colision abajo
	if (spr_survivor.getPosition().y + spr_survivor.getGlobalBounds().height >= (resolucion.y + 39.f)) {
		spr_survivor.setPosition(spr_survivor.getPosition().x, (resolucion.y + 39.f) - spr_survivor.getGlobalBounds().height);
		posicion.y = (resolucion.y + 39.f) - spr_survivor.getGlobalBounds().height;
	}

	//Colision ventana sprite survivordisp
	//Colision izquierda
	if (spr_survivordisparo.getPosition().x <= 33.f) {
		spr_survivordisparo.setPosition(33.f, spr_survivordisparo.getPosition().y);
		posicion.x = 33.f;
	}
	//Colision arriba
	if (spr_survivordisparo.getPosition().y <= 33.f) {
		spr_survivordisparo.setPosition(spr_survivordisparo.getPosition().x, 33.f);
		posicion.y = 33.f;
	}
	//Colision derecha
	if (spr_survivordisparo.getPosition().x + spr_survivordisparo.getGlobalBounds().width >= (resolucion.x + 39.f)) {
		spr_survivordisparo.setPosition((resolucion.x + 39.f) - spr_survivordisparo.getGlobalBounds().width, spr_survivordisparo.getPosition().y);
		posicion.x = (resolucion.x + 39.f) - spr_survivor.getGlobalBounds().width;
	}
	//Colision abajo
	if (spr_survivordisparo.getPosition().y + spr_survivordisparo.getGlobalBounds().height >= (resolucion.y + 39.f)) {
		spr_survivordisparo.setPosition(spr_survivordisparo.getPosition().x, (resolucion.y + 39.f) - spr_survivordisparo.getGlobalBounds().height);
		posicion.y = (resolucion.y + 39.f) - spr_survivor.getGlobalBounds().height;
	}
}


void survivor::movimiento_teclado()
{
	bool jugadorUp, jugadorDown, jugadorRight, jugadorLeft;

	if (Keyboard::isKeyPressed(Keyboard::W)) { jugadorUp = true; }
	if (!Keyboard::isKeyPressed(Keyboard::W)) { jugadorUp = false; }
	if (Keyboard::isKeyPressed(Keyboard::S)) { jugadorDown = true; }
	if (!Keyboard::isKeyPressed(Keyboard::S)) { jugadorDown = false; }
	if (Keyboard::isKeyPressed(Keyboard::D)) { jugadorRight = true; }
	if (!Keyboard::isKeyPressed(Keyboard::D)) { jugadorRight = false; }
	if (Keyboard::isKeyPressed(Keyboard::A)) { jugadorLeft = true; }
	if (!Keyboard::isKeyPressed(Keyboard::A)) { jugadorLeft = false; }
	update(jugadorUp, jugadorDown, jugadorRight, jugadorLeft);
	mover(Vector2f(velocidad.x, velocidad.y));
}


void survivor::movimiento_joystick() {

	
	/*bool jugadorUp, jugadorDown, jugadorRight, jugadorLeft;

	if(Joystick::isButtonPressed(0,Joystick::Z)) { jugadorUp = true; }
	if (!Joystick::isButtonPressed(0, Joystick::Z)) { jugadorUp = false; }
	if (Joystick::isButtonPressed(0, Joystick::X)) { jugadorDown = true; }
	if (!Joystick::isButtonPressed(0, Joystick::X)) { jugadorDown = false; }
	if (Joystick::isButtonPressed(0, Joystick::Y)) { jugadorRight = true; }
	if (!Joystick::isButtonPressed(0, Joystick::Y)) { jugadorRight = false; }
	if (Joystick::isButtonPressed(0, Joystick::R)) { jugadorLeft = true; }
	if (!Joystick::isButtonPressed(0, Joystick::R)) { jugadorLeft = false; }
	mover(Vector2f(velocidad.x, velocidad.y));
	*/
}


void survivor::mirarAlMouse(Window *ventana1)
{
	float a, b, angle;
	a = get_posicion().x - Mouse::getPosition(*ventana1).x;
	b = get_posicion().y - Mouse::getPosition(*ventana1).y;
	angle = (-atan2(a, b) * 180.f / 3.14) - 97.f;
	rotar(angle);
}