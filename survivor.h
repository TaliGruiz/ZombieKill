#pragma once

class survivor
{
private:
	int life;
	float xvel, yvel;
	float xpos, ypos;
	
public:
	//set
	void set_life(int _life) { life = _life; }
	void set_xvel(float _xvel) { xvel = _xvel; }
	void set_yvel(float _yvel) { yvel = _yvel; }
	void set_ypos(float _ypos) { ypos = _ypos; }
	void set_xpos(float _xpos) { xpos = _xpos; }
	//get
	int get_life() { return life; }
	float get_xvel() { return xvel; }
	float get_yvel() { return yvel; }
	float get_xpos() { return xpos; }
	float get_ypos() { return ypos; }
	//constructor
	survivor()
	{
		life = 1000;
		xvel = 0;
		yvel = 0;
		xpos = 0;
		ypos = 0;
	}
	survivor(float _xpos, float _ypos)
	{
		life = 1000;
		xvel = 0;
		yvel = 0;
		xpos = _xpos;
		ypos = _ypos;
	}

	void update(bool jugadorUp, bool jugadorDown, bool jugadorRight, bool jugadorLeft) {

		float speed = 3;

		if (jugadorRight) {
			jugadorRight = true;
			xvel = speed;
		}
		if (jugadorLeft) {
			xvel = -speed;
			jugadorRight = false;
		}
		if (jugadorDown) {
			yvel = speed;
		}
		if (jugadorUp) {
			yvel = -speed;
		}
		if (!(jugadorRight || jugadorLeft)) {
			xvel = 0;
		}
		if (!(jugadorUp || jugadorDown)) {
			yvel = 0;
		}
		xpos += xvel;
		ypos += yvel;
	}
};