#pragma once
#include "juego.h"
#include <math.h>
#include <dos.h>
#include "survivor.h"

class zombie
{
public:
	//set
	void set_str(int);
	void set_hp(int);
	void set_velocidad(Vector2f);
	void set_posicion(Vector2f);
	void set_spr_zombie_rotation(float);
	void set_spr_zombie();
	void set_currHp(int _currHp) { currHp = _currHp; }
	void set_hpbarpos(Vector2f);
	void set_hpbar();
	//get
	Sprite get_spr_zombie() { return spr_zombie; }
	int get_str() { return str; }
	int get_hp() { return hp; }
	int get_currHp() { return currHp; }
	RectangleShape gethpbar() { return hpbar; }
	Vector2f get_velocidad() { return velocidad; }
	Vector2f get_posicion() { return spr_zombie.getPosition(); }

	//constructores
	zombie(Vector2f, float, int);
	void eliminar() { delete this; }

	//movimientos
	void mover(Vector2f);
	void set_spr_zombie_posicion(Vector2f);
	//void set_hp_bar_posicion(Vector2f);
	void rotar(float);

	//zombie sigue survivor
	void update(Vector2f, float);

private:
	
	Texture text_zombie;
	RectangleShape hpbar;
	Sprite spr_zombie;
	int str;
	int hp, currHp;
	Vector2f velocidad;
	Vector2f posicion;
};

