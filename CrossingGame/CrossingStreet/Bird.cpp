#include "Bird.h"
void Bird::selfDraw()
{
	TextColor(13);
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
void Bird::move() {
	mX -= mSpeed;
	if (mX >= RIGHT)
		mX = mX + LEFT - RIGHT + 1;
	if (mX <= LEFT - width + 1)
		mX = mX - (LEFT - RIGHT + 1);
	if (mY == TOP + 6)
		mY--;
	else
		mY++;
}
void Bird::clearPath()
{
	int x1, y1;
	y1 = mY - height + 1;
	x1 = mX;
	if (RIGHT - mX - 3 < width)
	{
		for (int j = 0; j <= height; j++)
		{
			GotoXY(LEFT + 1, TOP + 4 + j);
			cout << "   ";
		}
	}
	if (x1 < RIGHT - 3)
		for (int i = 0; i <= height; i++)
		{
			GotoXY(x1 + 2, TOP + 4 + i);
			cout << "    ";
		}
}