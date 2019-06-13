#include "zombie.h"
using namespace std;
using namespace sf;

//////////// ****** sets ****** ////////////

void zombie::set_spr_zombie()
{
	text_zombie.loadFromFile("imagenes/newzombie.png");
	spr_zombie.setTexture(text_zombie);
	spr_zombie.setOrigin(22.5, 20);
}
void zombie::set_str(float _str) { str = _str; }
void zombie::set_life(float _life) { life = _life; }
void zombie::set_velocidad(Vector2f _velocidad) { velocidad = _velocidad; }
void zombie::set_posicion(Vector2f _posicion) { posicion = _posicion; }
void zombie::set_spr_zombie_rotation(float _ang) { spr_zombie.setRotation(_ang); }
void zombie::set_spr_zombie_posicion(Vector2f _pos) { spr_zombie.setPosition(_pos); }

//////////// ****** constructores ****** ////////////

zombie::zombie(Vector2f _pos, float MulVel, float _str, float _life)
{
	set_spr_zombie();
	str= _str;
	life = _life;
	posicion = _pos;
	velocidad.x = 1 * MulVel;
	velocidad.y = 1 * MulVel;
	spr_zombie.setPosition(posicion);
	
}

//////////// ****** Movimientos ****** ////////////

void zombie::mover(Vector2f _mov) { spr_zombie.move(_mov); }

void zombie::rotar(float _angle) { spr_zombie.setRotation(_angle); }

void zombie::update(Vector2f pospj) {

	float speed = 1;
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