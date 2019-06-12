#include "bala.h"

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