#pragma once
#include "Vehicle.h"

class Truck : public Vehicle
{
public:
	static const char form[][5];
	static const int width = 5, height = 3;
public:
	Truck() {};
	Truck(int, int) {};
	Truck(const Truck&) {};
	~Truck() {};
public:
	virtual void selfDraw();
	void clearPath();
	void move();
	Truck& operator=(const Truck& c);
};