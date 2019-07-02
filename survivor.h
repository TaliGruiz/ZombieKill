#pragma once

class survivor
{
private:
	Texture text_survivor, text_survivordisparo;;
	Sprite spr_survivor, spr_survivordisparo;
	int life;
	int currHp;
	Vector2f posicion;
	Vector2f velocidad;

public:
	//set
	void set_life(float _life) { life = _life; }
	void set_velocidad(Vector2f _vel) { velocidad = _vel; }
	void set_posicion(Vector2f _pos) { posicion = _pos; }
	void set_spr_survivor();
	void set_spr_survivordisparo();
	void set_currHp(int _hp) { currHp = _hp; }
	void set_spr_survivor_posicion(Vector2f _pos) { spr_survivor.setPosition(_pos); }
	void set_spr_survivordisparo_posicion(Vector2f _pos) { spr_survivordisparo.setPosition(_pos); }

	//get
	Sprite get_spr_survivor() { return spr_survivor; }
	Sprite get_spr_survivordisparo() { return spr_survivordisparo; }
	int get_life() { return life; }
	Vector2f get_velocidad() { return velocidad; }
	Vector2f get_posicion() { return posicion; }
	int get_currHp() { return currHp; }


	//constructor
	survivor(Vector2f, float, float);

	//MOVIMIENTOS
	
	void update(bool, bool, bool, bool);
	void mover(Vector2f);
	void rotar(float);
	void colisionVentana(Vector2f);
	void movimiento_teclado();
	void mirarAlMouse(Window *);
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