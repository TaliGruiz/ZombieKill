
#pragma once
#include <iostream>

class score
{
private:
	char nombre[30];
	int rondas;
	int tiros, tirosacertados;
	float accuracy;
public:
	///set
	void set_rondas(int a) { rondas = a; }
	void set_nombre(const char* v) { strcpy(nombre, v); }
	void set_accuracy(float _accuracy) { accuracy = _accuracy; }
	void set_tiros(int a) { tiros = a; }
	void set_tirosacertados(int a) { tirosacertados = a; }

	///get
	int get_rondas() { return rondas; }
	const char* get_nombre() { return nombre; }
	float get_accuracy() { return accuracy; }
	int get_tiros() { return tiros; }
	int get_tirosacertados() { return tirosacertados; }

	///disco
	bool leerdedisco(int);
	void grabarendisco();
	void modificarendisco(int);

	///operadores
	bool operator>(score);
};

