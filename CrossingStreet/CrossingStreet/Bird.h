#pragma once
#include "Animal.h"

class Bird : public Animal
{
public:
	static const char form[][3];
	static const int width = 3, height = 2;
public:
	Bird() {};
	Bird(int, int) {};
	~Bird() {};
public:
	virtual void selfDraw();
	void move();
	void clearPath();
};