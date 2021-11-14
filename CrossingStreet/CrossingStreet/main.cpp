#include "Animal.h"
#include "People.h"
#include "Vehicle.h"
#include "MainHeader.h"
#include "Truck.h"
#include "Car.h"
#include "Bird.h"
#include "Dinosaur.h"
#include "Game.h"
#include <iomanip>
#pragma comment(lib, "winmm.lib")
// Hình vẽ xe hơi
const char Car::form[][6] = {
    {255, '_', '_', '_', '_', 255},
    {'|', '|', '_', '|', '_', '\\'},
    {192, 'O', 196, 'O', 196, 217},
};
// Hình vẽ xe tải
const char Truck::form[][5] = {
    {255, 255, 255, 220, 255},
    {220, 219, 219, 219, 219},
    {255, 'O', 255, 'O', 255}};
// Hình vẽ chim
const char Bird::form[][3] = {
    {254, ' ', 254},
    {' ', 223, ' '},
};
// Hình vẽ thú
const char Dinosaur::form[][5] = {
    {' ', ' ', ' ', ' ', 254},
    {219, 219, 219, 219, 255},
    {'/', '/', ' ', '/', '/'},
};
// Hình vẽ người
const char People::form[][3] = {
    {' ', 234, ' '},
    {'/', 186, '\\'},
    {'/', ' ', '\\'},
};
// Vị trí các đường kẻ trong game
// khoảng cách giữa các đường kẻ ngang là 4, dọc là 70
const int Game::posY[] = {30, 26, 22, 18, 14};
// biến lựa chọn (có thể là menu hoặc di chuyển
char MOVING;
// khởi tạo class game
Game g;

int lineY[4] = {29, 25, 21, 17};

bool checkisImpactPoint;

bool dead_vehicle, dead_animal;

bool lightCar = false;

bool lightTruck = false;

bool TrafficLight = true;

bool soundOn = true;

int continue1;

void askPlayContinue()
{
    bool continue2 = true;
    g.effect();
    GotoXY(123, 30);
    TextColor(15);
    cout << "Ban co muon choi lai khong";
    GotoXY(133, 31);
    TextColor(10);
    cout << "Yes";
    GotoXY(137, 31);
    TextColor(15);
    cout << "/";
    GotoXY(139, 31);
    cout << "No";
    while (1)
    {
        if (MOVING == 'A')
        {
            continue2 = true;
            GotoXY(133, 31);
            TextColor(10);
            cout << "Yes";
            TextColor(15);
            GotoXY(139, 31);
            cout << "No";
        }
        else if (MOVING == 'D')
        {
            continue2 = false;
            GotoXY(133, 31);
            TextColor(15);
            cout << "Yes";
            GotoXY(139, 31);
            TextColor(10);
            cout << "No";
        }
        if (MOVING == 13)
        {
            if (continue2)
                continue1 = 1;
            else
                continue1 = 2;
            break;
        }
    }
    g.clearEffect();
}

void trafficLight()
{
    srand(time(0));
    int countTruck = 0;
    int countCar = 3;
    while (TrafficLight && g.IS_RUNNING())
    {
        if (countCar % 9 == 1 || countCar == 3)
        {
            if (lightCar)
                lightCar = false;
            else
                lightCar = true;
        }
        if (countTruck % 9 == 1 || countTruck == 0)
        {
            if (lightTruck)
                lightTruck = false;
            else
                lightTruck = true;
        }
        if (countCar == 203)
            countCar = 3;
        if (countTruck == 200)
            countTruck = 0;
        countCar++, countTruck++;
        Sleep(300);
    }
}

void runGame()
{
    int flashing = 0;
    bool dead1 = false;
    while (g.IS_RUNNING())
    {
        if (!g.getPeople()->isDead()) // Nếu người vẫn còn sống
        {
            if (MOVING != ' ')
                g.updatePosPeople(MOVING);            // Cập nhật vị trí người theo thông tin từ main
            g.updatePosVehicle(lightTruck, lightCar); // Cập nhật vị trí xe
            g.updatePosAnimal();                      // Cập nhật vị trí
            g.drawGame(MOVING, flashing, checkisImpactPoint);
            dead1 = false;
            if (flashing == 60)
                flashing = 0;
        }
        // Tạm khóa không cho di chuyển, chờ nhận phím từ hàm main
        MOVING = ' ';
        if (g.getPeople()->isImpact(g.getTrucks(), g.NumOfEnemy(), true) ||
            g.getPeople()->isImpact(g.getCars(), g.NumOfEnemy(), false))
        {
            if (!dead1)
            {
                g.getPeople()->dead();
                // g.effect();
                dead_vehicle = true;
                dead1 = true;
                if (soundOn)
                    Sleep(3000);
                else
                    Sleep(500);
                askPlayContinue();
            }
        }
        else if (g.getPeople()->isImpact(g.getBirds(), g.NumOfEnemy(), true) ||
                 g.getPeople()->isImpact(g.getDinosaurs(), g.NumOfEnemy(), false))
        {
            //đây chỉ là xử lý tạm thời, sẽ thêm hiệu ứng lúc thua ở đây
            if (!dead1)
            {
                g.getPeople()->dead();
                // g.effect();
                dead_animal = true;
                dead1 = true;
                if (soundOn)
                    Sleep(1500);
                else
                    Sleep(500);
                askPlayContinue();
            }
        }
        if (g.getPeople()->isFinish())
        {
            //đây chỉ là xử lý tạm thời, sẽ thêm hiệu ứng qua màn ở đây
            GotoXY(LEFT + 10, 12);
            TextColor(10);
            cout << "Ban vua qua duong thanh cong, Qua man moi nao !";
            Sleep(2000);
            clearConsole(40, 10);
            drawConsole(40, 10);
            g.resetGame(g.nextLevel());
            flashing = -1;
            MOVING = 'F';
        }
        flashing++;
        Sleep(100);
    }
}

void addNameTxt(string nameFileTxt)
{
    fstream fi;
    fi.open("listName.txt", ios::out | ios::app);
    // if (fi.eof())
    fi << nameFileTxt << endl;
    // else
    // fi << endl << nameFileTxt;
    fi.close();
}

void updateRankBoard(string namePlayer)
{
    vector<string> name;
    vector<int> score;
    string name1;
    int score1;
    fstream fi;
    fi.open("rank.txt", ios::in);
    while (!fi.eof())
    {
        getline(fi, name1, '\n');
        fi >> score1;
        name.push_back(name1);
        score.push_back(score1);
        getline(fi, name1, '\n');
    }
    fi.close();
    int size = name.size();
    int highScore = g.HightScore();
    for (int i = 0; i < size; i++)
    {
        if (score[i] < highScore)
        {
            name[i] = namePlayer;
            score[i] = highScore;
            break;
        }
    }
    fstream fo;
    fo.open("rank.txt", ios::out | ios::trunc);
    int i = 0;
    while (!fo.eof())
    {
        fo << name[i] << endl
           << score[i];
        i++;
        if (i < size)
            fo << endl;
        else if (i == size)
            break;
    }
    fo.close();
}

void rankBoard()
{
    // vẽ thêm chữ "RANK BOARD"
    vector<string> name;
    vector<int> score;
    string name1;
    int score1;
    fstream fi;
    fi.open("rank.txt", ios::in);
    while (!fi.eof())
    {
        getline(fi, name1, '\n');
        fi >> score1;
        name.push_back(name1);
        score.push_back(score1);
        getline(fi, name1, '\n');
    }
    fi.close();
    TextColor(12);
    int x = 50;
    int y = 15;
    GotoXY(x - 1, 13);
    cout << "Rank       Name";
    GotoXY(x + 28, 13);
    cout << "Score";
    int size = name.size();
    TextColor(15);
    for (int i = 0; i < size; i++)
    {
        GotoXY(x, y);
        cout << i + 1;
        GotoXY(x + 5, y);
        cout << name[i];
        GotoXY(x + 28, y);
        cout << score[i];
        y += 2;
    }
}
/////////////////////////////////Ham tu them/////////////////////////////////////

void Loading()
{
    // SetConsoleCP(65001);
    // SetConsoleOutputCP(65001);
    // Loading game
    srand(NULL);
    GotoXY(73, 27);
    cout << "LOADING";

    int i = 10;
    GotoXY(43, i++);
    cout << " $$$$$$\\                                           $$\\";
    GotoXY(43, i++);
    cout << "$$  __$$\\                                         \\__ |";
    GotoXY(43, i++);
    cout << "$$ /  \\__|  $$$$$$\\   $$$$$$\\   $$$$$$$\\  $$$$$$$\\ $$\\   $$$$$$$\\    $$$$$$\\";
    GotoXY(43, i++);
    cout << "$$ |       $$  __$$\\ $$  __$$\\ $$  _____|$$  _____|$$ |  $$  __$$\\  $$  __$$\\";
    GotoXY(43, i++);
    cout << "$$ |       $$ |  \\__|$$ / $$ | \\$$$$$$\\  \\$$$$$$\\  $$ |  $$ |  $$ |  $$ / $$ |";
    GotoXY(43, i++);
    cout << "$$ |   $$\\ $$ |      $$ | $$ | \\____$$\\  \\____ $$\\ $$ |  $$ |  $$ |  $$ | $$ |";
    GotoXY(43, i++);
    cout << "\\$$$$$$  | $$ |      \\$$$$$$ | $$$$$$$ | $$$$$$$  |$$ |  $$ |  $$ | \\$$$$$$$ |";
    GotoXY(43, i++);
    cout << "\\______ / \\__|       \\______/ \\_______/ \\_______/ \\__|  \\__|  \\__ |  \\____$$ |";
    GotoXY(43, i++);
    cout << "                                                                    $$\\   $$ |";
    GotoXY(43, i++);
    cout << "                                                                    \\$$$$$$  |";
    GotoXY(43, i++);
    cout << "                                                                     \\______ /";

    GotoXY(45, 32);
    // cout << char(179);
    cout << char(179);
    GotoXY(109, 32);
    // cout << char(179);
    cout << char(179);
    GotoXY(46, 32);
    for (int i = 29; i < 92; i++)
    {
        int a = rand() % 50;
        Sleep(a);
        // cout << "█";
        cout << char(219);
    }
}

void menuTitle()
{
    int i = 3;
    TextColor(15);
    GotoXY(43, i++);
    cout << " $$$$$$\\                                           $$\\";
    GotoXY(43, i++);
    cout << "$$  __$$\\                                         \\__ |";
    GotoXY(43, i++);
    cout << "$$ /  \\__|  $$$$$$\\   $$$$$$\\   $$$$$$$\\  $$$$$$$\\ $$\\   $$$$$$$\\    $$$$$$\\";
    GotoXY(43, i++);
    cout << "$$ |       $$  __$$\\ $$  __$$\\ $$  _____|$$  _____|$$ |  $$  __$$\\  $$  __$$\\";
    GotoXY(43, i++);
    cout << "$$ |       $$ |  \\__|$$ / $$ | \\$$$$$$\\  \\$$$$$$\\  $$ |  $$ |  $$ |  $$ / $$ |";
    GotoXY(43, i++);
    cout << "$$ |   $$\\ $$ |      $$ | $$ | \\____$$\\  \\____ $$\\ $$ |  $$ |  $$ |  $$ | $$ |";
    GotoXY(43, i++);
    cout << "\\$$$$$$  | $$ |      \\$$$$$$ | $$$$$$$ | $$$$$$$  |$$ |  $$ |  $$ | \\$$$$$$$ |";
    GotoXY(43, i++);
    cout << "\\______ / \\__|       \\______/ \\_______/ \\_______/ \\__|  \\__|  \\__ |  \\____$$ |";
    GotoXY(43, i++);
    cout << "                                                                    $$\\   $$ |";
    GotoXY(43, i++);
    cout << "                                                                    \\$$$$$$  |";
    GotoXY(43, i++);
    cout << "                                                                     \\______ /";
}

int menu()
{
    system("cls");
    int Choose = 1;
    char press;

    menuTitle();

    do
    {
        switch (Choose)
        {
        case 1:
        {
            GotoXY(65, 19);
            TextColor(12);
            cout << "=>    N_E_W   G_A_M_E    <=";
            GotoXY(65, 21);
            TextColor(15);
            cout << "     L_O_A_D   G_A_M_E     ";
            GotoXY(65, 23);
            TextColor(15);
            cout << "    R_A_N_K   B_O_A_R_D    ";
            GotoXY(65, 25);
            TextColor(15);
            cout << "     I_N_T_R_O_D_U_C_E     ";
            GotoXY(65, 27);
            TextColor(15);
            cout << "       S_E_T_T_I_N_G     ";
            GotoXY(65, 29);
            TextColor(15);
            cout << "     E_X_I_T   G_A_M_E     ";
            break;
        }
        case 2:
        {
            GotoXY(65, 19);
            TextColor(15);
            cout << "      N_E_W   G_A_M_E      ";
            GotoXY(65, 21);
            TextColor(12);
            cout << "=>   L_O_A_D   G_A_M_E   <=";
            GotoXY(65, 23);
            TextColor(15);
            cout << "    R_A_N_K   B_O_A_R_D    ";
            GotoXY(65, 25);
            TextColor(15);
            cout << "     I_N_T_R_O_D_U_C_E     ";
            GotoXY(65, 27);
            TextColor(15);
            cout << "       S_E_T_T_I_N_G     ";
            GotoXY(65, 29);
            TextColor(15);
            cout << "     E_X_I_T   G_A_M_E     ";
            break;
        }
        case 3:
        {
            GotoXY(65, 19);
            TextColor(15);
            cout << "      N_E_W   G_A_M_E      ";
            GotoXY(65, 21);
            TextColor(15);
            cout << "     L_O_A_D   G_A_M_E     ";
            GotoXY(65, 23);
            TextColor(12);
            cout << "=>  R_A_N_K   B_O_A_R_D  <=";
            GotoXY(65, 25);
            TextColor(15);
            cout << "     I_N_T_R_O_D_U_C_E     ";
            GotoXY(65, 27);
            TextColor(15);
            cout << "       S_E_T_T_I_N_G       ";
            GotoXY(65, 29);
            TextColor(15);
            cout << "     E_X_I_T   G_A_M_E     ";
            break;
        }
        case 4:
        {
            GotoXY(65, 19);
            TextColor(15);
            cout << "      N_E_W   G_A_M_E      ";
            GotoXY(65, 21);
            TextColor(15);
            cout << "     L_O_A_D   G_A_M_E     ";
            GotoXY(65, 23);
            TextColor(15);
            cout << "    R_A_N_K   B_O_A_R_D    ";
            GotoXY(65, 25);
            TextColor(12);
            cout << "=>   I_N_T_R_O_D_U_C_E   <=";
            GotoXY(65, 27);
            TextColor(15);
            cout << "       S_E_T_T_I_N_G       ";
            GotoXY(65, 29);
            TextColor(15);
            cout << "     E_X_I_T   G_A_M_E     ";
            break;
        }
        case 5:
        {
            GotoXY(65, 19);
            TextColor(15);
            cout << "      N_E_W   G_A_M_E      ";
            GotoXY(65, 21);
            TextColor(15);
            cout << "     L_O_A_D   G_A_M_E     ";
            GotoXY(65, 23);
            TextColor(15);
            cout << "    R_A_N_K   B_O_A_R_D    ";
            GotoXY(65, 25);
            TextColor(15);
            cout << "     I_N_T_R_O_D_U_C_E     ";
            GotoXY(65, 27);
            TextColor(12);
            cout << "=>     S_E_T_T_I_N_G     <=";
            GotoXY(65, 29);
            TextColor(15);
            cout << "     E_X_I_T   G_A_M_E     ";
            break;
        }
        case 6:
        {
            GotoXY(65, 19);
            TextColor(15);
            cout << "      N_E_W   G_A_M_E      ";
            GotoXY(65, 21);
            TextColor(15);
            cout << "     L_O_A_D   G_A_M_E     ";
            GotoXY(65, 23);
            TextColor(15);
            cout << "    R_A_N_K   B_O_A_R_D    ";
            GotoXY(65, 25);
            TextColor(15);
            cout << "     I_N_T_R_O_D_U_C_E     ";
            GotoXY(65, 27);
            TextColor(15);
            cout << "       S_E_T_T_I_N_G       ";
            GotoXY(65, 29);
            TextColor(12);
            cout << "=>   E_X_I_T   G_A_M_E   <=";
            break;
        }
        }
        press = toupper(_getch());
        if (press == 'W' || press == 72)
        {
            if (Choose == 1)
                Choose = 6;
            else
                Choose--;
        }
        else if (press == 'S' || press == 80)
        {
            if (Choose == 6)
                Choose = 1;
            else
                Choose++;
        }
    } while (press != 13);
    if (Choose != 5)
        system("cls");
    // system("color e4");
    return Choose;
}

void PauseGame(HANDLE t)
{
    SuspendThread(t);
}

void resumeGame(HANDLE t)
{
    ResumeThread(t);
}

void soundPoint()
{
    int count_dead = 0;
    while (g.IS_RUNNING())
    {
        int nY = g.getPeople()->Y() - 2;
        if (dead_vehicle && count_dead == 0)
        {
            PlaySound(TEXT("sound/dead.wav"), NULL, SND_SYNC);
            count_dead++;
        }
        else if (dead_animal && count_dead == 0)
        {
            PlaySound(TEXT("sound/die_enemy.wav"), NULL, SND_SYNC);
            count_dead++;
        }
        else if (checkisImpactPoint)
        {
            PlaySound(TEXT("sound/point.wav"), NULL, SND_SYNC);
            checkisImpactPoint = false;
        }
        else if (nY <= lineY[0] && nY >= lineY[0] - 2)
        {
            if (!dead_vehicle)
            {
                Sleep(100);
                PlaySound(TEXT("sound/truck.wav"), NULL, SND_SYNC);
            }
        }
        else if (nY <= lineY[1] && nY >= lineY[1] - 2)
        {
            if (!dead_vehicle)
            {
                Sleep(100);
                PlaySound(TEXT("sound/car.wav"), NULL, SND_SYNC);
            }
        }
        else if (nY <= lineY[2] && nY >= lineY[2] - 2)
        {
            if (!dead_animal)
            {
                Sleep(100);
                PlaySound(TEXT("sound/dinosaur.wav"), NULL, SND_SYNC);
            }
        }
        else if (nY <= lineY[3] && nY >= lineY[3] - 2)
        {
            if (!dead_animal)
            {
                Sleep(100);
                PlaySound(TEXT("sound/bird.wav"), NULL, SND_SYNC);
            }
        }
        if (!(dead_animal || dead_vehicle))
            count_dead = 0;
    }
}

void initName(string &name)
{

    // Nhap ten
    TextColor(15);

    int x1 = 98;
    int y1 = 12;

    for (int i = 61; i < 98; i++)
    {
        GotoXY(i, y1);
        cout << char(223);
        GotoXY(x1--, y1 + 5);
        cout << char(220);
    }

    for (int i = 12; i < 29; i++)
    {
        GotoXY(98, i);
        cout << char(219);
        GotoXY(61, i);
        cout << char(219);
    }

    GotoXY(65, 15);
    cout << "Nhap ten:";
    GotoXY(68, 16);
    getline(cin, name);

    system("cls");
}

void loadgame(bool &checkLoad, int &choose, string &name)
{
    system("cls");
    GotoXY(LEFT + (RIGHT - LEFT) / 2 - 3, 38);
    TextColor(10);
    cout << "An 'Esc' De Thoat";
    TextColor(15);
    int x = 10;
    int y = 4;
    int n = 140;
    for (int i = x; i < 140; i++)
    {
        GotoXY(i, 3);
        cout << char(219);
        GotoXY(n--, 36);
        cout << char(219);
    }

    // textColor(52);
    int i = 6;
    GotoXY(38, i++);
    cout << "$$                                  $$         $$$$$$                                    " << endl;
    GotoXY(38, i++);
    cout << "$$                                  $$        $$    $$                                   " << endl;
    GotoXY(38, i++);
    cout << "$$         $$$$$$    $$$$$$    $$$$$$$        $$         $$$$$$   $$$$$$ $$$$    $$$$$$  " << endl;
    GotoXY(38, i++);
    cout << "$$        $$    $$        $$  $$    $$        $$  $$$$        $$  $$   $$   $$  $$    $$ " << endl;
    GotoXY(38, i++);
    cout << "$$        $$    $$   $$$$$$$  $$    $$        $$    $$   $$$$$$$  $$   $$   $$  $$$$$$$$ " << endl;
    GotoXY(38, i++);
    cout << "$$        $$    $$  $$    $$  $$    $$        $$    $$  $$    $$  $$   $$   $$  $$       " << endl;
    GotoXY(38, i++);
    cout << "$$$$$$$$   $$$$$$    $$$$$$$   $$$$$$$         $$$$$$    $$$$$$$  $$   $$   $$   $$$$$$$ " << endl;

    string s, s1;

    //////////////////////////////////////////////////
    fstream fi;
    int x1 = 98;
    int y1 = 18;

    for (int i = 61; i < 98; i++)
    {
        GotoXY(i, y1);
        cout << char(223);
        GotoXY(x1--, y1 + 10);
        cout << char(220);
    }

    for (int i = 18; i < 29; i++)
    {
        GotoXY(98, i);
        cout << char(219);
        GotoXY(61, i);
        cout << char(219);
    }

    int choice3;
    vector<string> list;
    fi.open("listname.txt", ios::in);
    while (!fi.eof())
    {
        getline(fi, s1, '\n');
        list.push_back(s1);
    }
    fi.close();

    checkLoad = false;
    int size = 9;
    int pos = 0;
    int y2 = y1;
    while (1)
    {
        for (int i = 0; i < size; i++)
        {
            if (pos == i)
                TextColor(12);
            else
                TextColor(15);
            if (i < size - 1)
            {
                GotoXY(64, y2 + i + 1);
                cout << list[i];
            }
        }
        if (pos == size - 1)
            TextColor(12);
        else
            TextColor(15);
        GotoXY(66, y2 + size);
        cout << "Khac";

        MOVING = toupper(_getch());
        if (MOVING == 27)
            return;
        if (MOVING == 'W')
            pos--;
        else if (MOVING == 'S')
            pos++;
        else if (MOVING == 13)
        {
            if (pos < size - 1)
                checkLoad = true;
            break;
        }
        if (pos < 0)
            pos = size - 1;
        else if (pos == size)
            pos = 0;
    }

    //////////////////////////////////////////////////
    // sửa lại bằng cách chạy 1 list các tên thư mục
    if (!checkLoad)
    {
        GotoXY(28 + 19 + 7, 33);
        TextColor(15);
        cout << "Input name of file (require .txt):  ";
        GotoXY(89, 33);
        cout << (char)219;
        GotoXY(89, 33);
        cin >> s;
        g.loadGame("File Save/" + s, name);
        choose = 1;
    }
    else
    {
        g.loadGame("File Save/" + list[pos], name);
        choose = 1;
    }
    system("cls");
}

void setting(int x, int y, int &level, bool &soundOn) // 8 30
{
    int pos = 1;
    GotoXY(x, y);
    TextColor(15);
    cout << "SETTING";
    TextColor(10);
    GotoXY(x + 10, y);
    cout << "1. Level";
    TextColor(15);
    GotoXY(x + 10, y + 1);
    cout << "2. Sound";
    TextColor(15);
    GotoXY(x + 10, y + 2);
    cout << "3. Back";
    while (1)
    {
        MOVING = toupper(_getch());
        if (MOVING == 'W')
        {
            if (pos == 1)
                pos = 3;
            else
                pos--;
            GotoXY(x, y);
            TextColor(15);
            cout << "SETTING";
            if (pos == 1)
                TextColor(10);
            else
                TextColor(15);
            GotoXY(x + 10, y);
            cout << "1. Level";
            if (pos == 2)
                TextColor(10);
            else
                TextColor(15);
            GotoXY(x + 10, y + 1);
            cout << "2. Sound";
            if (pos == 3)
                TextColor(10);
            else
                TextColor(15);
            GotoXY(x + 10, y + 2);
            cout << "3. Back";
        }
        else if (MOVING == 'S')
        {
            if (pos == 3)
                pos = 1;
            else
                pos++;
            GotoXY(x, y);
            TextColor(15);
            cout << "SETTING";
            if (pos == 1)
                TextColor(10);
            else
                TextColor(15);
            GotoXY(x + 10, y);
            cout << "1. Level";
            if (pos == 2)
                TextColor(10);
            else
                TextColor(15);
            GotoXY(x + 10, y + 1);
            cout << "2. Sound";
            if (pos == 3)
                TextColor(10);
            else
                TextColor(15);
            GotoXY(x + 10, y + 2);
            cout << "3. Back";
        }
        else if (MOVING == 13)
        {
            if (pos == 1)
            {
                GotoXY(x + 20, y);
                TextColor(15);
                cout << "<<   >>";
                TextColor(10);
                GotoXY(x + 23, y);
                cout << level;
                while (1)
                {
                    MOVING = toupper(_getch());
                    if (MOVING == 'A')
                    {
                        if (level == 1)
                            level = 7;
                        else
                            level--;
                        TextColor(10);
                        GotoXY(x + 23, y);
                        cout << level;
                    }
                    else if (MOVING == 'D')
                    {
                        if (level == 7)
                            level = 1;
                        else
                            level++;
                        TextColor(10);
                        GotoXY(x + 23, y);
                        cout << level;
                    }
                    else if (MOVING == 13)
                    {
                        GotoXY(x + 20, y);
                        cout << "            ";
                        break;
                    }
                }
            }
            else if (pos == 2)
            {
                GotoXY(x + 20, y + 1);
                TextColor(15);
                cout << "<<     >>";
                TextColor(10);
                GotoXY(x + 23, y + 1);
                cout << "On ";
                while (1)
                {
                    MOVING = toupper(_getch());
                    if (MOVING == 'A' && soundOn)
                        MOVING = 'D';
                    else if (MOVING == 'D' && !soundOn)
                        MOVING = 'A';
                    if (MOVING == 'A')
                    {
                        soundOn = true;
                        TextColor(10);
                        GotoXY(x + 23, y + 1);
                        cout << "On ";
                    }
                    else if (MOVING == 'D')
                    {
                        soundOn = false;
                        TextColor(10);
                        GotoXY(x + 23, y + 1);
                        cout << "Off";
                    }
                    else if (MOVING == 13)
                    {
                        GotoXY(x + 20, y + 1);
                        cout << "            ";
                        break;
                    }
                }
            }
            else if (pos == 3)
            {
                GotoXY(x, y);
                cout << "                                ";
                GotoXY(x, y + 1);
                cout << "                                ";
                GotoXY(x, y + 2);
                cout << "                                ";
                return;
            }
        }
    }
}

void title(int x, int y)
{
    TextColor(14);
    GotoXY(x, y);
    cout << "eeee eeeeee eeeee eeeee eeeee e  eeeee eeeee   eeeee eeeee eeeeee eeee eeee eeeee" << endl;
    GotoXY(x, y + 1);
    cout << "8  8 8   88 8  88 8     8     8  8   8 8       8       8   8   88 8    8      8   " << endl;
    GotoXY(x, y + 2);
    cout << "8    8eee8e 8   8 8eeee 8eeee 8e 8e  8 8 ee8   8eeee   8   8eee8e 8eee 8eee   8  " << endl;
    GotoXY(x, y + 3);
    cout << "8    88   8 8   8    88    88 88 88  8 8   8      88   8   88   8 8    8      8  " << endl;
    GotoXY(x, y + 4);
    cout << "88e8 88   8 8eee8 8ee88 8ee88 88 88  8 88ee8   8ee88   88  88   8 88ee 88ee   8  " << endl;
}

void goodBye(int x, int y)
{
    TextColor(9);
    GotoXY(x, y);
    cout << " ######      #######     #######    ########    ########    ##    ##   ########        ########    ##            ###      ##    ##   ########   ########  ";
    GotoXY(x, y + 1);
    cout << "##    ##    ##     ##   ##     ##   ##     ##   ##     ##    ##  ##    ##              ##     ##   ##           ## ##      ##  ##    ##         ##     ## ";
    GotoXY(x, y + 2);
    cout << "##          ##     ##   ##     ##   ##     ##   ##     ##     ####     ##              ##     ##   ##          ##   ##      ####     ##         ##     ## ";
    GotoXY(x, y + 3);
    cout << "##   ####   ##     ##   ##     ##   ##     ##   ########       ##      ######          ########    ##         ##     ##      ##      ######     ########  ";
    GotoXY(x, y + 4);
    cout << "##    ##    ##     ##   ##     ##   ##     ##   ##     ##      ##      ##              ##          ##         #########      ##      ##         ##   ##   ";
    GotoXY(x, y + 5);
    cout << "##    ##    ##     ##   ##     ##   ##     ##   ##     ##      ##      ##              ##          ##         ##     ##      ##      ##         ##    ##  ";
    GotoXY(x, y + 6);
    cout << " ######      #######     #######    ########    ########       ##      ########        ##          ########   ##     ##      ##      ########   ##     ## ";
}

void intro(int x, int y)
{
    GotoXY(x, y);
    cout << "####   ##    ##   ########   ########     #######    ########    ##     ##    ######    ######## ";
    GotoXY(x, y + 1);
    cout << " ##    ###   ##      ##      ##     ##   ##     ##   ##     ##   ##     ##   ##    ##   ##       ";
    GotoXY(x, y + 2);
    cout << " ##    ####  ##      ##      ##     ##   ##     ##   ##     ##   ##     ##   ##         ##       ";
    GotoXY(x, y + 3);
    cout << " ##    ## ## ##      ##      ########    ##     ##   ##     ##   ##     ##   ##         ######   ";
    GotoXY(x, y + 4);
    cout << " ##    ##  ####      ##      ##   ##     ##     ##   ##     ##   ##     ##   ##         ##       ";
    GotoXY(x, y + 5);
    cout << " ##    ##   ###      ##      ##    ##    ##     ##   ##     ##   ##     ##   ##    ##   ##       ";
    GotoXY(x, y + 6);
    cout << "####   ##    ##      ##      ##     ##    #######    ########     #######     ######    ######## ";
    GotoXY(x + 2, y + 10);
    cout << "                                      GROUP 6 INTRODUCE";
    GotoXY(x + 2, y + 14);
    cout << "                                     CROSSING STREET GAME";
    GotoXY(x + 2, y + 16);
    cout << "With an easy-to-play game format that will help you have the best experience when playing games";
    GotoXY(x + 2, y + 18);
    cout << "       You will transform into a young man who crosses the streets in search of real love";
    GotoXY(x + 2, y + 20);
    cout << "        Simple gameplay with only 4 keys (W: Go up, A: Go left, S: Go back, D: Go right)";
    GotoXY(x + 2, y + 22);
    cout << "                   On the way to move, avoid the obstacles on your way.";
    GotoXY(x + 2, y + 24);
    cout << "        There are also items that help you increase your score while moving (REMEMBER))";
    GotoXY(x + 2, y + 29);
    cout << "                            <PRESS ESC KEY TO BACK TO MENU DISPLAY>";
}
/////////////////////////////////Ham tu them/////////////////////////////////////

int main()
{
    // system("color e4");
    // setup khung
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 1250, 690, TRUE);
    FixConsoleWindow();
    DisableResizeWindow();
    Nocursortype();
    ShowScrollbar(0);
    Loading();           // ms them
    system("cls");       // ms them
    int choose = menu(); // ms them
    bool checkLoad = false;
    int temp; // ms them
    bool pause = false;
    bool run = true;
    int level = 1;
    soundOn = true;
    string name = "";
    checkisImpactPoint = false;
    dead_vehicle = false, dead_animal = false;
    thread t1(runGame);
    thread t2(soundPoint);
    thread t3(trafficLight);
    g.pauseGame(t1.native_handle());
    g.pauseGame(t2.native_handle());
    g.pauseGame(t3.native_handle());

    while (1)
    {
        if (choose == 1)
        {
            if (!checkLoad)
                initName(name);

            // vẽ khung trò chơi và menu
            drawConsole(40, 10);
            // Tọa độ khung menu:
            // Menu Trái: 3, 13
            // Menu phải: 40, 13
            // Chiều ngang: 30
            title(35, 2);
            drawMenu(120, 13);

            GotoXY(16, 14);
            cout << "MENU";
            GotoXY(8, 16);
            cout << "N : New Game";
            GotoXY(8, 18);
            cout << "P : Pause/Resume Game ";
            GotoXY(8, 20);
            cout << "T : Save Game";
            GotoXY(8, 22);
            cout << "L : Load Game";
            GotoXY(8, 24);
            cout << "G : Setting";
            GotoXY(8, 26);
            cout << "Esc : Exit";

            GotoXY(122, 15);
            cout << "Name Player: " << name;
            ;
            GotoXY(128, 19);
            cout << "Score:";
            GotoXY(125, 22);
            cout << "Level";
            GotoXY(138, 22);
            cout << "High Score";

            // bắt đầu game
            g.startGame();
            run = true;
            TrafficLight = true;
            lightCar = false;
            lightTruck = false;
            continue1 = 0;
            // thread t1(runGame);
            // HANDLE handle_t1 = t1.native_handle();
            // reset game sẽ được dùng lại mỗi khi new game hoặc mở load game,
            // số xe, thú tăng theo lv mà người đang chơi, ở đây là 1 nên có 2 xe, thú
            // công thức thì xem kỹ hơn ở trong hàm
            g.resetGame(level);
            if (!checkLoad)
                g.newgame();
            MOVING = 'I';
            g.updateScore();
            g.getPeople()->setPos();
            g.resumeGame(t1.native_handle());
            if (soundOn)
                g.resumeGame(t2.native_handle());
            g.resumeGame(t3.native_handle());
            while (run)
            {
                MOVING = toupper(_getch());
                // phần chạy hỏi có chơi lại hay không
                if (MOVING == 13)
                {
                    Sleep(50);
                    if (continue1 == 2)
                        MOVING = 27;
                    else if (continue1 == 1)
                        MOVING = 'N';
                }
                // --------------------------------------
                if (MOVING == 27) // ESC
                {
                    PauseGame(t1.native_handle());
                    PauseGame(t2.native_handle());
                    PauseGame(t3.native_handle());
                    updateRankBoard(name);
                    choose = menu();
                    run = false;
                    MOVING = ' ';
                    continue1 = 0;
                    name = "";
                }
                else if (MOVING == 'N') // new game
                {
                    g.clearEffect();
                    g.pauseGame(t1.native_handle());
                    clearConsole(40, 10);
                    drawConsole(40, 10);
                    g.resetGame(1);
                    g.resumeGame(t1.native_handle());
                    g.updateScore();
                    dead_vehicle = false;
                    dead_animal = false;
                    resumeGame(t3.native_handle());
                    if (soundOn)
                        resumeGame(t2.native_handle());
                    continue1 = 0;
                }
                else if (MOVING == 'P') // Pause/resume Game
                {
                    if (!pause)
                    {
                        pause = true;
                        g.pauseGame(t1.native_handle());
                        g.pauseGame(t2.native_handle());
                        g.pauseGame(t3.native_handle());
                        GotoXY(LEFT + (RIGHT - LEFT) / 2 - 8, 36);
                        TextColor(12);
                        cout << "An 'P' de choi tiep";
                    }
                    else
                    {
                        pause = false;
                        GotoXY(LEFT + (RIGHT - LEFT) / 2 - 8, 36);
                        cout << "                      ";
                        g.resumeGame(t1.native_handle());
                        if (soundOn)
                            g.resumeGame(t2.native_handle());
                        g.resumeGame(t3.native_handle());
                    }
                }
                else if (MOVING == 'T')
                {
                    // save game
                    g.pauseGame(t1.native_handle());
                    PauseGame(t3.native_handle());
                    PauseGame(t2.native_handle());
                    string s;
                    GotoXY(2, 30);
                    cout << "Input name of file (require .txt):";
                    GotoXY(5, 31);
                    cout << (char)219;
                    GotoXY(5, 31);
                    cin >> s;
                    g.saveGame("File Save/" + s, name);
                    addNameTxt(s);
                    g.resumeGame(t1.native_handle());
                    resumeGame(t3.native_handle());
                    if (soundOn)
                        resumeGame(t2.native_handle());
                }
                else if (MOVING == 'L') // Load Game
                {
                    g.pauseGame(t1.native_handle());
                    PauseGame(t3.native_handle());
                    PauseGame(t2.native_handle());
                    loadgame(checkLoad, choose, name);
                    choose = 1;
                    break;
                }
                else if (MOVING == 'G')
                {
                    // setting
                    g.pauseGame(t1.native_handle());
                    PauseGame(t3.native_handle());
                    PauseGame(t2.native_handle());
                    level = g.currentLevel();
                    setting(8, 30, level, soundOn);
                    if (level != g.currentLevel())
                    {
                        clearConsole(40, 10);
                        drawConsole(40, 10);
                        g.resetGame(level);
                        g.resumeGame(t1.native_handle());
                        g.updateScore();
                        dead_vehicle = false;
                        dead_animal = false;
                    }
                    g.resumeGame(t1.native_handle());
                    resumeGame(t3.native_handle());
                    if (soundOn)
                        resumeGame(t2.native_handle());
                }
            }
        }
        else if (choose == 2) // Load game
        {
            loadgame(checkLoad, choose, name);
            if (checkLoad)
                choose = 1;
            else
                choose = menu();
        }
        else if (choose == 3) // rank board
        {
            int i = 3;
            GotoXY(25, i++);
            cout << "$$$$$$$                       $$              $$$$$$$                                         $$" << endl;
            GotoXY(25, i++);
            cout << "$$    $$                      $$              $$    $$                                        $$" << endl;
            GotoXY(25, i++);
            cout << "$$    $$   $$$$$$   $$$$$$$   $$    $$        $$    $$   $$$$$$     $$$$$$    $$$$$$    $$$$$$$$" << endl;
            GotoXY(25, i++);
            cout << "$$$$$$$         $$  $$    $$  $$   $$         $$$$$$$   $$    $$         $$  $$    $$  $$     $$" << endl;
            GotoXY(25, i++);
            cout << "$$    $$   $$$$$$$  $$    $$  $$$$$$          $$    $$  $$    $$    $$$$$$$  $$        $$     $$" << endl;
            GotoXY(25, i++);
            cout << "$$    $$  $$    $$  $$    $$  $$   $$         $$    $$  $$    $$   $$    $$  $$        $$     $$" << endl;
            GotoXY(25, i++);
            cout << "$$    $$   $$$$$$$  $$    $$  $$    $$        $$$$$$$    $$$$$$     $$$$$$$  $$         $$$$$$$$" << endl;

            g.pauseGame(t1.native_handle());
            rankBoard();
            GotoXY(LEFT + (RIGHT - LEFT) / 2 - 8, 36);
            TextColor(12);
            cout << "An phim bat ki de thoat";
            MOVING = toupper(_getch());
            GotoXY(LEFT + (RIGHT - LEFT) / 2 - 8, 36);
            cout << "                                     ";
            choose = menu();
        }
        else if (choose == 4)
        {
            intro(30, 6);
            MOVING = toupper(_getch());
            choose = menu();
        }
        else if (choose == 5)
        {
            setting(100, 27, level, soundOn);
            choose = menu();
        }
        else if (choose == 6) // Exit
        {
            // system("cls");
            goodBye(50, 15);
            g.exitGame(&t1);
            g.exitGame(&t2);
            g.exitGame(&t3);
            break;
        }
    }
}