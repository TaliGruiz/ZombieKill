#pragma once
#include "juego.h"
 

class zombie
{
public:
	//set
	void set_str(float _str) { str = _str; }
	void set_life(float _life) { life = _life; }
	void set_velocidad(Vector2f(_velocidad)) { velocidad = _velocidad; }
	void set_posicion(Vector2f _posicion) { posicion = _posicion; }
	void set_spr_zombie_rotation(float _ang) 
	{
		spr_zombie.setRotation(_ang);
	}
	void set_spr_zombie(const char v[]) 
	{
		text_zombie.loadFromFile(v);
		spr_zombie.setTexture(text_zombie);
	}
	
	void set_spr_zombie_posicion(Vector2f _pos) { spr_zombie.setPosition(_pos); }
	
	//get
	Sprite get_spr_zombie() { return spr_zombie; }
	float get_str() { return str; }
	float get_life() { return life; }
	Vector2f get_velocidad() { return velocidad; }
	Vector2f get_spr_zombie_posicion() { return spr_zombie.getPosition(); }
	

	//constructores
	zombie(const char v[], Vector2f pos, float MulVel, float _str, float _life)
	{
		set_spr_zombie(v);
		set_str(_str);
		set_life(_life);
		set_posicion(pos);
		velocidad.x = 1 * MulVel;
		velocidad.y = 1 * MulVel;
		spr_zombie.setPosition(posicion);
	}
	
	zombie();
private:
	Texture text_zombie;
	Sprite spr_zombie;
	float str;
	float life;
	Vector2f velocidad;
	Vector2f posicion;
};

