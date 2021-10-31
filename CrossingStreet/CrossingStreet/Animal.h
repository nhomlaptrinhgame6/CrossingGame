#pragma once
#include "MainHeader.h"

class Animal
{
protected:
	int mX, mY;
public:
	Animal();
	Animal(int, int);
	virtual ~Animal() {};
public:
	virtual void move() = 0;
public:
	void setPos(int, int);
	int X() const { return mX; }
	int Y() const { return mY; }
};