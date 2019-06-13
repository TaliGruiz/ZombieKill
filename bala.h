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

public:
	Texture text_bala;
	CircleShape shape;
	Vector2f currVelocity;
	float maxSpeed;
	CircleShape get_circleshape() { return shape; }
	void set_currVelocity(Vector2f vec) { currVelocity = vec; }
	float get_maxSpeed() { return maxSpeed; }
	/*
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
	*/
	//constructor
	//bullet(float, float, float);
	
	bullet(float radius = 3.f)
		: currVelocity(0.f,0.f), maxSpeed(15.f)
	{
		text_bala.loadFromFile("imagenes/bala.png");
		this->shape.setRadius(radius);
		shape.setFillColor(Color(0, 0, 0, 0));
	}

	void update(Vector2f, Vector2i);
	
	void mover(Vector2f);

	Vector2f get_velocidad() { return velocidad; }
};