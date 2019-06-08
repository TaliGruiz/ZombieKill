#pragma once
#include "SFML\Graphics.hpp"
using namespace sf;

class bala
{
private:
	Sprite spr_bala;
	Texture text_bala;
	Vector2f velocidad;
	Vector2f aceleracion;
	float str;

public:

	//set
	void set_spr_bala(const char v[]) 
	{
		text_bala.loadFromFile(v);
		spr_bala.setTexture(text_bala);
	}
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
	bala(const char v[], float _mulvel, float _mulace, float _str)
	{
		set_spr_bala(v);
		velocidad.x = 1 * _mulvel;
		velocidad.y = 1 * _mulvel;
		set_aceleracion( {1 * _mulace, 1 * _mulace } );
		set_velocidad( { 1 * _mulvel, 1 * _mulvel } );
		set_str(_str);
	}
};













