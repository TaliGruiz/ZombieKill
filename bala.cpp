#include "bala.h"
/*
bullet::bullet(float _mulvel, float _mulace, float _str)
{
	text_bala.loadFromFile("imagenes/bala.png");
	spr_bala.setTexture(text_bala);
	velocidad.x = 1 * _mulvel;
	velocidad.y = 1 * _mulvel;
	set_aceleracion({ 1 * _mulace, 1 * _mulace });
	set_velocidad({ 1 * _mulvel, 1 * _mulvel });
	set_str(_str);
}
*/

void bullet::update(Vector2f pospj,Vector2i posmouse) {

	float speed = 65;
	Vector2f distance;
	distance.x = posmouse.x - pospj.x;
	distance.y = posmouse.y - pospj.y;
	float length = sqrt((distance.x * distance.x) + (distance.y * distance.y));

	velocidad.y = speed * (distance.y / length);
	velocidad.x = speed * (distance.x / length);
		
	spr_bala.setPosition(pospj);

	posicion.y += velocidad.y;
	posicion.x += velocidad.x;
}

void bullet::mover(Vector2f _mov)
{
	spr_bala.move(_mov);
}
