#pragma once
#include "MainHeader.h"

class Vehicle
{
private:
	void copyVehicle(const Vehicle&);
protected:
	int mX, mY;
public:
	Vehicle();
	Vehicle(int, int);
	Vehicle(const Vehicle& a);
	virtual ~Vehicle() {};
	Vehicle& operator=(const Vehicle& a)
	{
		if (this != &a) {
			copyVehicle(a);
		}
		return *this;
	}
public:
	//virtual void selfDraw() const = 0;
public:
	void setPos(int x, int y);
	int X() const { return mX; }
	int Y() const { return mY; }
};