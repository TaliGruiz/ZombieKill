#pragma once
#include "SFML\Graphics.hpp"
using namespace sf;

class bullet
{
private:
	/*
	Sprite spr_bala;
	Texture text_bala;
	Vector2f velocidad;
	Vector2f aceleracion;
	float str;
	*/
	/*
	CircleShape shape;
	Vector2f currVelocity;
	float maxSpeed;
	*/
	Vector2f velocidad, posicion;
	int str;

public:
	Texture text_bala;
	Sprite spr_bala;
	CircleShape shape;
	Vector2f currVelocity;
	float maxSpeed;
	
	void set_str(int _str) { str = _str; }
	int get_str() { return str; }

	void set_currVelocity(Vector2f vec) { currVelocity = vec; }
	float get_maxSpeed() { return maxSpeed; }
	Sprite get_spr_bala() { return spr_bala; }

	void set_velocidad(Vector2f _vel) { velocidad = _vel; }

	void set_posicion(Vector2f _pjpos) { posicion = _pjpos; }
	
	
	/*
	//set
	void set_velocidad(Vector2f _vel) { velocidad = _vel; }
	void set_aceleracion(Vector2f _ace) { aceleracion = _ace; }
	void set_str(float _str) { str = _str; }
	
	//get
	
	float get_str() { return str; }
	Vector2f get_velocidad() { return velocidad; }
	Vector2f get_aceleracion() { return aceleracion; }
	Vector2f get_spr_bala_posicion() { return spr_bala.getPosition(); }
	*/
	//constructor
	//bullet(float, float, float);
	
	bullet()
	{
		text_bala.loadFromFile("imagenes/bala.png");
		spr_bala.setTexture(text_bala);
		spr_bala.setColor(Color(255, 255, 255, 0));
		str = 20;
	}

	void update(Vector2f, Vector2i);
	
	void mover(Vector2f);

	Vector2f get_velocidad() { return velocidad; }
};