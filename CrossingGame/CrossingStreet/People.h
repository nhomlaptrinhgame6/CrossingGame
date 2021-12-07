#pragma once
#include "MainHeader.h"
#include "Animal.h"
#include "Vehicle.h"
#include "Truck.h"
#include "Car.h"
#include "Bird.h"
#include "Dinosaur.h"

class People
{
public:
	static const char form[][3];
	static const int width = 3;
	static const int height = 3;
public:
	int mX, mY;
	//int mSpeed;
	bool mState;
	int posY[4] = { 28,24,20,16 };
	int posX[6] = { 45, 55, 65,75,85,95 };
	int pX = 0, pY = 0;
	void copyPeople(const People& p);
public:
	People();
	People(int, int);
	~People() {}
	People(const People&);
	int X() { return mX; }
	int Y() { return mY; }
	void selfDraw();
	void clearPath(char);
	void reloadConsole(static const int posY[]);
	void setPos(int, int);
	//void tell();
	void up();
	void down();
	void left();
	void right();
	bool isImpact(const Animal*, int, bool);
	bool isImpact(const Vehicle*, int, bool);
	bool isFinish() { return mY <= TOP + 2; }
	bool isDead() { return mState == false; }
	void dead() { mState = false; }
public:
	// diem thuong
	void setPos()
	{
		srand(time(0));
		pY = posY[rand() % 4];
		pX = posX[rand() % 6];
	}
	void draw()
	{
		GotoXY(pX, pY);
		TextColor(12);
		cout << "*";
	}
	void clear()
	{
		GotoXY(pX, pY);
		cout << " ";
	}
	bool isImpact()
	{
		if (pY <= mY && pY >= mY - 2)
		{
			if (mX <= pX && mX + 2 >= pX)
				return true;
		}
		return false;
	}
};