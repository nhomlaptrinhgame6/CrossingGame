#pragma once
#include "Animal.h"

class Dinosaur : public Animal
{
public:
	static const char form[][5];
	static const int width = 5, height = 3;
public:
	Dinosaur() {};
	Dinosaur(int, int) {};
	Dinosaur(const Dinosaur&) {};
	~Dinosaur() {};
public:
	virtual void selfDraw();
	void move();
	void clearPath();
	Dinosaur& operator=(const Dinosaur& d);
};