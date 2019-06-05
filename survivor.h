#pragma once

class survivor
{
private:
	int life;
	Vector2f posicion;
	Vector2f velocidad;

public:
	//set
	void set_life(int _life) { life = _life; }
	void set_velocidad(Vector2f _vel) { velocidad = _vel; }
	void set_velocidad_x(float _xvel) { velocidad.x = _xvel; }
	void set_velocidad_y(float _yvel) { velocidad.y = _yvel; }
	void set_posicion(Vector2f _pos) { posicion = _pos; }
	void set_posicion_y(float _ypos) { posicion.y = _ypos; }
	void set_posicion_x(float _xpos) { posicion.x = _xpos; }
	//get
	int get_life() { return life; }
	Vector2f get_velocidad() { return velocidad; }
	float get_velocidad_x() { return velocidad.x; }
	float get_velocidad_y() { return velocidad.y; }
	Vector2f get_posicion() { return posicion; }
	float get_posicion_x() { return posicion.x; }
	float get_posicion_y() { return posicion.y; }

	//constructor
	survivor()
	{
		life = 1000;
		posicion.x = 0;
		posicion.y = 0;
		velocidad.x = 0;
		velocidad.y = 0;
	}
	survivor(float _xpos, float _ypos)
	{
		life = 1000;
		velocidad.x = 0;
		velocidad.y = 0;
		posicion.x = _xpos;
		posicion.y = _ypos;
	}

	void update(bool jugadorUp, bool jugadorDown, bool jugadorRight, bool jugadorLeft) {

		float speed = 3;

		if (jugadorRight) {
			jugadorRight = true;
			velocidad.x = speed;
		}
		if (jugadorLeft) {
			velocidad.x = -speed;
			jugadorRight = false;
		}
		if (jugadorDown) {
			velocidad.y = speed;
		}
		if (jugadorUp) {
			velocidad.y = -speed;
		}
		if (!(jugadorRight || jugadorLeft)) {
			velocidad.x = 0;
		}
		if (!(jugadorUp || jugadorDown)) {
			velocidad.y = 0;
		}
		posicion.x += velocidad.x;
		posicion.y += velocidad.y;
	}
};