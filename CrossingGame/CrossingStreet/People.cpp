#include "People.h"
#include "Animal.h"
#include "Vehicle.h"
#include "Truck.h"
#include "Car.h"
#include "Bird.h"
#include "Dinosaur.h"

void People::copyPeople(const People& p)
{
	mX = p.mX;
	mY = p.mY;
	//mSpeed = p.mSpeed;
	mState = p.mState;
}
People::People()
{
	mX = mY = 0;
	srand(time(0));
	pY = posY[rand() % 4];
	pX = posX[rand() % 6];
	//mSpeed = 1;
	mState = true;
}
People::People(int column, int row)
{
	mX = column;
	mY = row;
	srand(time(0));
	pY = posY[rand() % 4];
	pX = posX[rand() % 6];
	//mSpeed = 1;
	mState = true;
}
People::People(const People& p)
{
	copyPeople(p);
}
void People::selfDraw()
{
	TextColor(15);
	int row = mY - height + 1;
	int i = row, j;
	for (; row <= mY; row++) {
		GotoXY(mX, row);
		for (j = 0; j < width; j++)
			cout << form[row - i][j];
	}
}
void People::clearPath(char key)
{
	int i = 0;
	int x1 = mX, y1 = mY - height + 1;
	if (key == 'A')
	{
		for (; i < height; i++)
		{
			GotoXY(x1 + width, y1 + i);
			cout << "  ";
		}
	}
	else if (key == 'W')
	{
		for (; i < width; i++)
		{
			GotoXY(x1 + i, y1 + height);
			cout << " ";
			GotoXY(x1 + i, y1 + height + 1);
			cout << " ";
		}
	}
	else if (key == 'S')
	{
		for (; i < width; i++)
		{
			GotoXY(x1 + i, y1 - 1);
			cout << " ";
			GotoXY(x1 + i, y1 - 2);
			cout << " ";
		}
	}
	else if (key == 'D')
	{
		for (; i < height; i++)
		{
			GotoXY(x1 - 2, y1 + i);
			cout << "  ";
		}
	}
}
void People::reloadConsole(static const int posY[])
{
	int y1 = mY - height + 1;
	for (int i = 0; i < 8; i++)
	{
		if (posY[i] >= y1 && posY[i] < y1 + height)
		{
			TextColor(15);
			GotoXY(mX - 2, posY[i]);
			cout << (char)205 << (char)205;
			GotoXY(mX + width, posY[i]);
			cout << (char)205 << (char)205;
			break;
		}
		else if (posY[i] == y1 + height)
		{
			TextColor(15);
			for (int j = 0; j < height; j++)
			{
				GotoXY(mX + j, posY[i]);
				cout << (char)205 << (char)205;
			}
			break;
		}
	}
	for (int i = 7; i >= 0; i--)
		if (posY[i] == y1 - 1)
		{
			TextColor(15);
			for (int j = 0; j < height; j++)
			{
				GotoXY(mX + j, posY[i]);
				cout << (char)205 << (char)205;
			}
			break;
		}
}
void People::setPos(int x, int y)
{
	mX = x;
	mY = y;
}
void People::up()
{
	mY -= 2;
}
void People::down()
{
	if (mY + 2 <= BOTTOM)
		mY += 2;
}
void People::left() {
	if (mX - 2 >= LEFT)
		mX -= 2;
	else
		mX = LEFT;
}
void People::right()
{
	if (mX + 2 <= RIGHT - width + 1)
		mX += 2;
	else
		mX = RIGHT - width + 1;
}
bool People::isImpact(const Animal* obj, int num, bool animal)
{
	int x, y = obj[0].Y();
	int w;
	if (animal)
		w = Bird::width;
	else
		w = Dinosaur::width;
	if (y <= mY + 2 && y > mY - People::height)
	{
		for (int i = 0; i < num; i++)
		{
			x = obj[i].X();
			if (mX >= x - 2 && mX < x + w)
			{
				mState = false;
				return true;
			}
		}
	}
	return false;
}
bool People::isImpact(const Vehicle* obj, int num, bool vehicle)
{
	int x, y = obj[0].Y();
	int w;
	if (vehicle)
		w = Truck::width;
	else
		w = Car::width;
	if (y <= mY + 2 && y > mY - People::height)
	{
		for (int i = 0; i < num; i++)
		{
			x = obj[i].X();
			if (mX >= x - 2 && mX < x + w)
			{
				mState = false;
				return true;
			}
		}
	}
	return false;
}