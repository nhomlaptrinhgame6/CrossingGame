#include "Truck.h"
void Truck::selfDraw()
{
	TextColor(14);
	int row = mY - height + 1;
	int i = row, j;
	for (; row <= mY; row++)
	{
		for (j = 0; j < width; j++)
		{
			if (mX + j < LEFT)
			{
				GotoXY(mX + j + (RIGHT - LEFT + 1), row);
				cout << form[row - i][j];
			}
			else if (mX + j > RIGHT)
			{
				GotoXY(mX + j - (RIGHT - LEFT + 1), row);
				cout << form[row - i][j];
			}
			else
			{
				GotoXY(mX + j, row);
				cout << form[row - i][j];
			}
		}
	}
}
void Truck::clearPath()
{
	int x1, y1;
	y1 = mY - height + 1;
	x1 = mX;
	if (RIGHT - mX - 3 < width)
	{
		for (int j = 0; j < height; j++)
		{
			GotoXY(LEFT, y1 + j);
			cout << "    ";
		}
	}
	if (x1 + width < RIGHT - 3)
		for (int i = 0; i < height; i++)
		{
			GotoXY(x1 + width, y1 + i);
			cout << "   ";
		}
	for (int i = 0; i < height; i++)
	{
		GotoXY(RIGHT - 3, y1 + i);
		cout << "    ";
	}
}
void Truck::move() {
	mX -= mSpeed;
	if (mX >= RIGHT)
		mX = mX + LEFT - RIGHT + 1;
	if (mX <= LEFT - width + 1)
		mX = mX - (LEFT - RIGHT + 1);
}
Truck& Truck::operator=(const Truck& c)
{
	Vehicle::operator=(c);
	return *this;
}