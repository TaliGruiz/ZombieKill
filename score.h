
#pragma once
#include <iostream>

class score
{
private:
	char nombre[15];
	int rondas;
	int kills;
	float aim;

public:
	///set
	void set_rondas(int a) { rondas = a; }
	void set_kills(int a) { kills = a; }
	void set_nombre(const char* v) { strcpy(nombre, v); }
	void set_aim(float a) { aim = a; }
	
	///get
	int get_rondas() { return rondas; }
	int get_zombies() { return kills; }
	const char* get_nombre() { return nombre; }
	float get_aim() { return aim; }
	
	///disco
	bool leerdedisco(int);
	void grabarendisco();
	void modificarendisco(int);
};

