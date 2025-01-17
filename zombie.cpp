#include "zombie.h"
#include <iostream>
using namespace std;
using namespace sf;

//////////// ****** sets ****** ////////////

void zombie::set_spr_zombie2()
{
	text_zombie.loadFromFile("imagenes/zombie2.png"); 
	spr_zombie.setTexture(text_zombie);
	spr_zombie.setOrigin(22.5, 20);
}
void zombie::set_spr_zombie1()
{
	text_zombie.loadFromFile("imagenes/zombie3.png");
	spr_zombie.setTexture(text_zombie);
	spr_zombie.setOrigin(22.5, 20);
}

void zombie::set_str(int _str) { str = _str; }
void zombie::set_hp(int _hp) { hp = _hp; }
void zombie::set_velocidad(Vector2f _velocidad) { velocidad = _velocidad; }
void zombie::set_posicion(Vector2f _posicion) { posicion = _posicion; }
void zombie::set_spr_zombie_rotation(float _ang) { spr_zombie.setRotation(_ang); }
void zombie::set_spr_zombie_posicion(Vector2f _pos) { spr_zombie.setPosition(_pos); }

//////////// ****** constructores ****** ////////////

zombie::zombie(Vector2f _pos, int sprtype, int _hp)
{
	if (sprtype == 1) set_spr_zombie1();
	if (sprtype == 2) set_spr_zombie2();
	str = 1;
	hp = _hp;
	currHp = hp;
	posicion = _pos;
	spr_zombie.setPosition(posicion);
	
}

//////////// ****** Movimientos ****** ////////////

void zombie::mover(Vector2f _mov) { spr_zombie.move(_mov); }

void zombie::rotar(float _angle) { spr_zombie.setRotation(_angle); }

void zombie::update(Vector2f pospj,float speed) {

	Vector2f distance;
	distance.x = pospj.x - posicion.x;
	distance.y = pospj.y - posicion.y;
	float length = sqrt((distance.x * distance.x) + (distance.y * distance.y));

	velocidad.y = speed * (distance.y / length);
	velocidad.x = speed * (distance.x / length);

	if (length != 0) {
		posicion.y += velocidad.y;
		posicion.x += velocidad.x;
	}

}