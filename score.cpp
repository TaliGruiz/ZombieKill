#include "score.h"
#include <iostream>
using namespace std;

bool score::leerdedisco(int pos) 
{
	FILE* p;
	p = fopen("score.txt", "rb");
	if (p == NULL) {
		std::cout << "No pudo abrir archivo." << endl;
		exit(1);
	}
	bool leyo = fread(this, sizeof (*this) * pos, 1, p);
	fclose(p);
	return leyo;
}

bool score::grabarendisco() 
{
	FILE* p;
	p = fopen("score.txt", "ab");
	if (p == NULL) {
		std::cout << "No pudo abrir archivo." << endl;
		exit(1);
	}
	bool grabo=fwrite(this, sizeof * this, 1, p);
	fclose(p);
	return grabo;
}

void score::modificarendisco(int pos)
{
	FILE* p;
	p = fopen("score.txt", "rb+");
	if (p == NULL) {
		std::cout << "No pudo abrir archivo." << endl;
		exit(1);
	}
	fseek(p, sizeof * this * pos, 0);
	fwrite(this, sizeof * this, 1, p);
	fclose(p);
}

bool score::operator>(score obj) 
{
	if (rondas > obj.rondas)return true;
	return false;
}

