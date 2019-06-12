#pragma once
#include "SFML\Graphics.hpp"
using namespace sf;

class bullet
{
private:
	Sprite spr_bala;
	Texture text_bala;
	Vector2f velocidad;
	Vector2f aceleracion;
	float str;

public:

	//set
	void set_velocidad(Vector2f _vel) { velocidad = _vel; }
	void set_aceleracion(Vector2f _ace) { aceleracion = _ace; }
	void set_str(float _str) { str = _str; }
	
	//get
	Sprite get_spr_bala() { return spr_bala; }
	float get_str() { return str; }
	Vector2f get_velocidad() { return velocidad; }
	Vector2f get_aceleracion() { return aceleracion; }
	Vector2f get_spr_bala_posicion() { return spr_bala.getPosition(); }
	
	//constructor
	bullet(float, float, float)
};













