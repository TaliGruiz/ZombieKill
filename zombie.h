#pragma once
#include "juego.h"
#include <math.h>
#include <dos.h>
#include "survivor.h"

class zombie
{
public:
	//set
	void set_str(float);
	void set_life(float);
	void set_velocidad(Vector2f);
	void set_posicion(Vector2f);
	void set_spr_zombie_rotation(float);
	void set_spr_zombie();
	
	
	//get
	Sprite get_spr_zombie() { return spr_zombie; }
	float get_str() { return str; }
	float get_life() { return life; }
	Vector2f get_velocidad() { return velocidad; }
	Vector2f get_posicion() { return spr_zombie.getPosition(); }
	
	//constructores
	zombie(Vector2f, float, float, float);

	//movimientos
	void mover(Vector2f);
	void set_spr_zombie_posicion(Vector2f);
	void rotar(float);

	//zombie sigue survivor
	void update(Vector2f);

private:
	Texture text_zombie;
	Sprite spr_zombie;
	float str;
	float life;
	Vector2f velocidad;
	Vector2f posicion;
};

