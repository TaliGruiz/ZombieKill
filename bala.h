#pragma once
#include "SFML\Graphics.hpp"


using namespace sf;

class bala
{
public:
	//set
	void set_str(float _str) { str = _str; }
	void set_velocidad(Vector2f _velocidad) { velocidad = _velocidad; }
	void set_aceleracion(Vector2f _aceleracion) { aceleracion = _aceleracion; }
	//get
	Sprite get_sprite() { return *spr_bala; };
	float get_str() { return str; }
	Vector2f get_velocidad() { return velocidad; }
	Vector2f get_aceleracion() { return aceleracion; }


	bala(Vector2f pos_inicial, Vector2f vel);
	void actualizar(float delta_t);
	
	
	

private:
	Sprite* spr_bala;
	Texture* txt_bala;
	Vector2f velocidad;
	Vector2f aceleracion;
	float str;
	
	


};