#pragma once

class survivor
{
private:
	Texture text_survivor, text_survivordisparo;;
	Sprite spr_survivor, spr_survivordisparo;
	int life;
	Vector2f posicion, velocidad;

public:
	//set
	void set_life(int _life) { life = _life; }
	void set_velocidad(Vector2f _vel) { velocidad = _vel; }
	void set_posicion(Vector2f _pos) { posicion = _pos; }
	void set_spr_survivor();
	void set_spr_survivordisparo();

	//get
	Sprite get_spr_survivor() { return spr_survivor; }
	Sprite get_spr_survivordisparo() { return spr_survivordisparo; }
	int get_life() { return life; }
	Vector2f get_velocidad() { return velocidad; }
	Vector2f get_posicion() { return posicion; }

	//constructor
	survivor(Vector2f, float, float);

	//MOVIMIENTOS
	
	void update(bool, bool, bool, bool);
	
	void mover(Vector2f);

	void rotar(float);

	//COLOR
	void color_aprietodisparo() 
	{
		spr_survivor.setColor(Color(255, 255, 255, 0));
		spr_survivordisparo.setColor(Color(255, 255, 255, 255));
	}
	void color_sueltodisparo()
	{
		spr_survivor.setColor(Color(255, 255, 255, 255));
		spr_survivordisparo.setColor(Color(255, 255, 255, 0));
	}
};