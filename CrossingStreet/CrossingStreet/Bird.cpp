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
	int i = 0;
	if (RIGHT - mX - 1 < width)
	{
		for (int j = 0; j < height; j++)
		{
			GotoXY(LEFT, y1 + j);
			cout << " ";
			GotoXY(LEFT + 1, y1 + j);
			cout << " ";
		}
		GotoXY(LEFT + 1, TOP + 6 - height);
		cout << " ";
		GotoXY(LEFT, TOP + 6);
		cout << " ";
	}
	for (; i < height; i++)
	{
		GotoXY(x1 + width, y1 + i);
		cout << " ";
	}
	if (mY == TOP + 6)
	{
		for (i = 0; i < width; i++)
		{
			GotoXY(x1 + width + i - 2, TOP + 6 - height);
			cout << " ";
		}
	}
	else
	{
		for (i = 0; i < width; i++)
		{
			GotoXY(x1 + width + i - 2, TOP + 6);
			cout << " ";
		}
	}
}