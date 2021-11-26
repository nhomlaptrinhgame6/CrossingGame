#pragma once
#include "Vehicle.h"

class Car : public Vehicle
{
public:
	static const char form[][6];
	static const int width = 6, height = 3;
public:
	Car() {};
	Car(int, int) {};
	Car(const Car&) {};
	~Car() {};
public:
	virtual void selfDraw();
	void clearPath();
	void move();
};