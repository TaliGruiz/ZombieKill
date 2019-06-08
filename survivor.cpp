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
		jugadorRight = true;
		velocidad.x = speed;
	}
	if (jugadorLeft) {
		velocidad.x = -speed;
		jugadorRight = false;
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