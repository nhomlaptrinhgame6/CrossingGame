#include "Game.h"
#include "Animal.h"
#include "People.h"
#include "Vehicle.h"
#include "MainHeader.h"
#include "Truck.h"
#include "Car.h"
#include "Bird.h"
#include "Dinosaur.h"
#include "MainHeader.h"

Game::Game()
{
	srand(time(NULL));
	score = highScore = 0;
	m_currentLevel = 1;
	m_nextLevel = false;
	resetGame(1);
};
Game::Game(int level)
{
	srand(time(NULL));
	resetGame(level);
};
void Game::drawGame(char key, int& flashing, bool& checkisImpactPoint)
{
	int i;
	GotoXY(127, 24);
	TextColor(15);
	cout << m_currentLevel;
	if (isImpactPoint())
	{
		flashing = 0;
		score += 10;
		checkisImpactPoint = true;
	}
	if (flashing == 0)
	{
		updateScore();
		m_people->setPos();
		m_people->draw();
	}
	else if (flashing % 6 == 0)
	{
		m_people->clear();
		if (flashing == 60)
			flashing = 1;
	}
	else if (flashing % 3 == 0)
		m_people->draw();
	for (i = 0; i < num; ++i)
	{
		m_truck[i].clearPath();
		m_truck[i].selfDraw();
		m_car[i].clearPath();
		m_car[i].selfDraw();
		m_Dinosaur[i].clearPath();
		m_Dinosaur[i].selfDraw();
		m_bird[i].clearPath();
		m_bird[i].selfDraw();
	}
	if (key != ' ')
	{
		m_people->clearPath(key);
		m_people->selfDraw();
		m_people->reloadConsole(posY);
	}
};
Game::~Game()
{
	clearGame();
}
int Game::nextLevel()
{
	m_nextLevel = true;
	return ++m_currentLevel;
}
void Game::newgame()
{
	score = 0;
	m_nextLevel = false;
}
void Game::resetGame(int level)
{
	clearGame();
	m_currentLevel = level;
	if (m_nextLevel)
		score += 20;
	is_running = true;
	m_people = new People((RIGHT + LEFT) / 2, BOTTOM);

	int interval = (level - 1) / 3 + 1;
	if (interval < 2)
		interval++;
	int numOfVehicles = interval;// số lượng xe
	int distance = (RIGHT - LEFT - 1) / numOfVehicles; // khoảng cách xe
	if (level > 4)
		distance += 3;
	int laneDistance = 4; // khoảng cách giữa 2 làn

	int row = BOTTOM - laneDistance;
	int col = LEFT + 1;
	num = numOfVehicles;
	m_truck = new Truck[num];
	for (int i = 0; i < num; ++i, col += distance)
		m_truck[i].setPos(col - 1, row);

	row -= laneDistance;
	col = (((LEFT + 1) << 1) + distance) >> 1;
	m_car = new Car[num];
	for (int i = 0; i < num; ++i, col += distance)
		m_car[i].setPos(col + 1, row);

	row -= laneDistance;
	col = LEFT + 1;
	m_Dinosaur = new Dinosaur[num];
	for (int i = 0; i < num; ++i, col += distance)
		m_Dinosaur[i].setPos(col + 1, row);

	row -= laneDistance;
	col = (((LEFT + 1) << 1) + distance) >> 1;
	m_bird = new Bird[num];
	for (int i = 0; i < num; ++i, col += distance)
		m_bird[i].setPos(col - 1, row);
}
void Game::exitGame(thread* t)
{
	is_running = false;
	t->join();
}
void Game::startGame()
{
	is_running = true;
}
void Game::clearGame()
{
	delete m_people;
	delete[]m_truck;
	delete[]m_car;
	delete[]m_Dinosaur;
	delete[]m_bird;
}
void Game::updatePosPeople(char key)
{
	if (key == 'W')
		m_people->up();

	else if (key == 'A')
		m_people->left();

	else if (key == 'S')
		m_people->down();

	else if (key == 'D')
		m_people->right();
};
void Game::updatePosVehicle(bool lightTruck, bool lightCar)
{
	int i;
	for (i = 0; i < num; ++i)
	{
		if (!lightTruck)
			m_truck[i].move();
		if (!lightCar)
			m_car[i].move();
	}
	if (!lightCar)
	{
		GotoXY(111, 23);
		TextColor(15);
		cout << (char)219;
		GotoXY(111, 24);
		TextColor(10);
		cout << (char)219;
	}
	else
	{
		GotoXY(111, 23);
		TextColor(12);
		cout << (char)219;
		GotoXY(111, 24);
		TextColor(15);
		cout << (char)219;
	}
	if (!lightTruck)
	{
		GotoXY(111, 27);
		TextColor(15);
		cout << (char)219;
		GotoXY(111, 28);
		TextColor(10);
		cout << (char)219;
	}
	else
	{
		GotoXY(111, 27);
		TextColor(12);
		cout << (char)219;
		GotoXY(111, 28);
		TextColor(15);
		cout << (char)219;
	}
};
void Game::updatePosAnimal() {
	int i;
	for (i = 0; i < num; ++i)
	{
		m_bird[i].move();
		m_Dinosaur[i].move();
	}
};
void Game::updateScore()
{
	TextColor(15);
	GotoXY(142, 19);
	cout << "    ";
	GotoXY(142, 19);
	cout << score;
	highScore = max(highScore, score);
	GotoXY(142, 24);
	cout << highScore;
}
bool Game::isImpactPoint()
{
	return m_people->isImpact();
}
void Game::saveGame(string file, string name)
{
	int x, y;
	fstream fi;
	fi.open(file, ios::out | ios::trunc);
	fi << name << endl;
	fi << m_currentLevel << endl;
	for (int i = 0; i < num; i++)
	{
		x = m_truck[i].X();
		y = m_truck[i].Y();
		fi << x << " " << y << " ";
	}
	fi << endl;
	for (int i = 0; i < num; i++)
	{
		x = m_car[i].X();
		y = m_car[i].Y();
		fi << x << " " << y << " ";
	}
	fi << endl;
	for (int i = 0; i < num; i++)
	{
		x = m_Dinosaur[i].X();
		y = m_Dinosaur[i].Y();
		fi << x << " " << y << " ";
	}
	fi << endl;
	for (int i = 0; i < num; i++)
	{
		x = m_bird[i].X();
		y = m_bird[i].Y();
		fi << x << " " << y << " ";
	}
	fi << endl;
	x = m_people->X();
	y = m_people->Y();
	fi << x << " " << y << endl;
	fi << score << " " << highScore;
	fi.close();
	GotoXY(2, 30);
	cout << "                                     ";
	GotoXY(5, 31);
	cout << "                                   ";
}
void Game::loadGame(string file, string &name)
{
	int x, y;
	fstream fi;
	fi.open(file, ios::in);
	if (!fi.fail())
	{
		clearGame();
		getline(fi, name, '\n');
		fi >> m_currentLevel;

		int interval = (m_currentLevel - 1) / 3 + 1;
		int numOfVehicles = interval + 1;// số lượng xe
		int distance = (RIGHT - LEFT - 1) / numOfVehicles; // khoảng cách xe
		int laneDistance = 4; // khoảng cách giữa 2 làn

		num = numOfVehicles;
		m_truck = new Truck[num];
		for (int i = 0; i < num; ++i)
		{
			fi >> x >> y;
			m_truck[i].setPos(x, y);
		}

		m_car = new Car[num];
		for (int i = 0; i < num; ++i)
		{
			fi >> x >> y;
			m_car[i].setPos(x, y);
		}

		m_Dinosaur = new Dinosaur[num];
		for (int i = 0; i < num; ++i)
		{
			fi >> x >> y;
			m_Dinosaur[i].setPos(x, y);
		}

		m_bird = new Bird[num];
		for (int i = 0; i < num; ++i)
		{
			fi >> x >> y;
			m_bird[i].setPos(x, y);
		}

		is_running = true;
		fi >> x >> y;
		m_people = new People(x, y);
		fi >> score >> highScore;
		updateScore();
		m_people->setPos();
		clearConsole(40, 10);
		drawConsole(40, 10);
	}
	fi.close();
	GotoXY(2, 30);
	cout << "                                   ";
	GotoXY(5, 31);
	cout << "                                   ";
}
void Game::effect()
{
	TextColor(15);
	int y2[] = { 0,5 };
	//ngang
	int y1 = 28;
	int x = 120;
	for (int i = 0; i < 2; i++)
	{
		GotoXY(x + 1, y1 + y2[i]);
		for (int j = 0; j < 31; j++)
			cout << (char)205;
	}
	//doc	
	GotoXY(x, y1);
	cout << (char)201;
	GotoXY(x + 31, y1);
	cout << (char)187;

	GotoXY(x, y1 + y2[1]);
	cout << (char)200;
	GotoXY(x + 31, y1 + y2[1]);
	cout << (char)188;

	for (int i = y1; i < y1 + y2[1]; i++)
	{
		if (i + 1 != y1 && i + 1 != y1 + y2[1])
		{
			GotoXY(x, i + 1);
			cout << (char)186;
			GotoXY(x + 31, i + 1);
			cout << (char)186;
		}
	}
}
void Game::clearEffect()
{
	int y2[] = { 0,5 };
	//ngang
	int y1 = 28;
	int x = 120;
	for (int i = 0; i < 6; i++)
	{
		GotoXY(x, y1 + i);
		for (int j = 0; j <= 31; j++)
			cout << " ";
	}
}
void Game::endgame(char& MOVING, bool soundOn)
{
	//clearGame();
	char form[][56] = {
{'#','#',255,255,255,255,'#','#',255,255,'#','#','#','#','#','#','#',255,255,'#','#',255,255,255,255,255,'#','#',255,255,255,255,'#','#',255,255,255,255,255,255,'#','#',255,'#','#','#','#',255,'#','#',255,255,255,255,'#','#'},
{255,'#','#',255,255,'#','#',255,255,'#','#',255,255,255,255,255,'#','#',255,'#','#',255,255,255,255,255,'#','#',255,255,255,255,'#','#',255,255,'#','#',255,255,'#','#',255,255,'#','#',255,255,'#','#','#',255,255,255,'#','#'},
{255,255,'#','#','#','#',255,255,255,'#','#',255,255,255,255,255,'#','#',255,'#','#',255,255,255,255,255,'#','#',255,255,255,255,'#','#',255,255,'#','#',255,255,'#','#',255,255,'#','#',255,255,'#','#','#','#',255,255,'#','#'},
{255,255,255,'#','#',255,255,255,255,'#','#',255,255,255,255,255,'#','#',255,'#','#',255,255,255,255,255,'#','#',255,255,255,255,'#','#',255,255,'#','#',255,255,'#','#',255,255,'#','#',255,255,'#','#',255,'#','#',255,'#','#'},
{255,255,255,'#','#',255,255,255,255,'#','#',255,255,255,255,255,'#','#',255,'#','#',255,255,255,255,255,'#','#',255,255,255,255,'#','#',255,255,'#','#',255,255,'#','#',255,255,'#','#',255,255,'#','#',255,255,'#','#','#','#'},
{255,255,255,'#','#',255,255,255,255,'#','#',255,255,255,255,255,'#','#',255,'#','#',255,255,255,255,255,'#','#',255,255,255,255,'#','#',255,255,'#','#',255,255,'#','#',255,255,'#','#',255,255,'#','#',255,255,255,'#','#','#'},
{255,255,255,'#','#',255,255,255,255,255,'#','#','#','#','#','#','#',255,255,255,'#','#','#','#','#','#','#',255,255,255,255,255,255,'#','#','#',255,255,'#','#','#',255,255,'#','#','#','#',255,'#','#',255,255,255,255,'#','#'},
	};

	int x_girl = LEFT + (RIGHT - LEFT) / 2;
	int x_boy = 116;
	People* boy = new People(x_boy, 15);
	People* girl = new People(x_girl, 15);
	girl->selfDraw();
	while (boy->X() > x_girl + 3)
	{
		boy->clearPath('A');
		boy->selfDraw();
		boy->left();
		Sleep(50);
	}
	delete boy;
	delete girl;
	int x = 49;
	int y = 20;
	TextColor(12);
	for (int i = 0; i < 56; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			GotoXY(x + i, y + j);
			cout <<(char)form[j][i];
			Sleep(3);
		}
	}
	if (soundOn)
		PlaySound(TEXT("sound/win.wav"), NULL, SND_SYNC);
	GotoXY(LEFT + (RIGHT - LEFT) / 2 - 10, 38);
	TextColor(10);
	cout << " <PRESS ENTER KEY TO EXIT>";
	while (MOVING != 13) {}
}