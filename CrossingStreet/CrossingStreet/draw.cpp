#include "MainHeader.h"
void drawConsole(int x, int y)
{
    TextColor(15);
    int y1 = y;
    for (int i = 0; i < 7; i++)
    {
        //GotoXY(x, y1);
        for (int j = 0; j < 70; j++)
        {
            GotoXY(x + j + 1, y1);
            cout << (char)205;
        }
        y1 += 4;
    }
    y1 = y;
    for (int i = 0; i < 25; i++)
    {
        if (y1 == y)
        {
            GotoXY(x, y1);
            cout << (char)201;
            GotoXY(x + 70, y1++);
            cout << (char)187;
        }
        else if (y1 == y + 24)
        {
            GotoXY(x, y1);
            cout << (char)200;
            GotoXY(x + 70, y1++);
            cout << (char)188;
        }
        else if ((y1 + 2) % 4 == 0)
        {
            GotoXY(x, y1);
            cout << (char)204;
            GotoXY(x + 70, y1++);
            cout << (char)185;
        }
        else
        {
            GotoXY(x, y1);
            cout << (char)186;
            GotoXY(x + 70, y1++);
            cout << (char)186;
        }
    }
}
void drawMenu(int x, int y)
{
    TextColor(15);
    //menu phải
    int y2[] = { 0,8, 12 };
    //ngang
    int y1 = y;
    for (int i = 0; i < 3; i++)
    {
        GotoXY(x + 1, y1 + y2[i]);
        for (int j = 0; j < 30; j++)
            cout << (char)205;
    }
    //doc
    GotoXY(x, y1);
    cout << (char)201;
    GotoXY(x + 30, y1);
    cout << (char)187;
    GotoXY(x, y1 + y2[1]);
    cout << (char)204;
    GotoXY(x + 30, y1 + y2[1]);
    cout << (char)185;
    GotoXY(x, y1 + y2[2]);
    cout << (char)204;
    GotoXY(x + 30, y1 + y2[2]);
    cout << (char)185;
    GotoXY(x, y1 + y2[2]);
    cout << (char)200;
    GotoXY(x + 30, y1 + y2[2]);
    cout << (char)188;
    for (int i = y1; i < y + y2[2]; i++)
    {
        if (i + 1 != y1 && i + 1 != y1 + y2[1] && i + 1 != y1 + y2[2])
        {
            GotoXY(x, i + 1);
            cout << (char)186;
            GotoXY(x + 30, i + 1);
            cout << (char)186;
        }
        if (i + 1 >= y1 + y2[1] && i + 1 <= y1 + y2[2])
        {
            if (i + 1 == y1 + y2[1])
            {
                GotoXY(x + 15, i + 1);
                cout << (char)203;
            }
            else if (i + 1 == y1 + y2[2])
            {
                GotoXY(x + 15, i + 1);
                cout << (char)202;
            }
            else
            {
                GotoXY(x + 15, i + 1);
                cout << (char)186;
            }
        }
    }



    //menu trái
    GotoXY(3 + 1, y1);
    for (int j = 0; j < 30; j++)
        cout << (char)205;
    GotoXY(3 + 1, y1 + y2[2] + 2);
    for (int j = 0; j < 30; j++)
        cout << (char)205;

    //doc
    GotoXY(3, y1);
    cout << (char)201;
    GotoXY(3 + 30, y1);
    cout << (char)187;
    GotoXY(3, y1 + y2[2] + 2);
    cout << (char)204;
    GotoXY(3 + 30, y1 + y2[2] + 2);
    cout << (char)185;
    GotoXY(3, y1 + y2[2] + 2);
    cout << (char)200;
    GotoXY(3 + 30, y1 + y2[2] + 2);
    cout << (char)188;
    for (int i = y1; i < y + y2[2] + 2; i++)
    {
        if (i + 1 != y1 && i + 1 != y1 + y2[2] + 2)
        {
            GotoXY(3, i + 1);
            cout << (char)186;
            GotoXY(3 + 30, i + 1);
            cout << (char)186;
        }
    }
}
void clearConsole(int x, int y)
{
    int y1 = y;
    for (int i = y; i < 35; i++)
    {
        GotoXY(x, i);
        cout << "                                                                            ";
    }
}