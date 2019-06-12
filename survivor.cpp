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

survivor::survivor(Vector2f _pos, float _mulvel, float _life)
{
	set_spr_survivor();
	set_spr_survivordisparo();
	posicion.x = _pos.x;
	posicion.y = _pos.y;
	velocidad.x = 1 * _mulvel;
	velocidad.y = 1 * _mulvel;
	set_life(_life);
}

void survivor::update(bool jugadorUp, bool jugadorDown, bool jugadorRight, bool jugadorLeft) {

	float speed = 3;

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