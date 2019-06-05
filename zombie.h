#pragma once
#include "juego.h"
 

class zombie
{
public:
	zombie();
	//set
	void set_str(float _str) { str = _str; }
	void set_life(float _life) { life = _life; }
	void set_velocidad(Vector2f(_velocidad)) { velocidad = _velocidad; }
	void set_posicion(Vector2f _posicion) { posicion = _posicion; }
	void set_posicion_x(float x) { posicion.x = x; }
	void set_posicion_y(float y) { posicion.y = y; }

	//get
	float get_str() { return str; }
	float get_life() { return life; }
	Vector2f get_velocidad() { return velocidad; }
	Vector2f get_posicion() { return posicion; }
	float get_posicion_x() { return posicion.x; }
	float get_posicion_y() { return posicion.y; }
	
private:
	Texture text_zombie;
	Sprite spr_zombie;
	float str;
	float life;
	Vector2f velocidad;
	Vector2f posicion;
};

