#pragma once
#include <cstdlib>
#include <time.h>
#include <queue>
#include <fstream>
#include <sstream>
#include <cmath>

#include "Cell.h"

using namespace std;
enum LEVEL
{
    LV_EASY = 0,
    LV_MEDIUM = 1,
    LV_HARD = 2,
    LV_CUSTOM = 3
};

class GameExecution
{
private:
    int height, width, num_mine, curLv;
    int Map[205][205];
    bool open[205][205], flag[205][205], firstclick = false;

    void reset();
    void getBasicFromFile();
    void checkLastPlay();
    void initTable();

    long long Rand(long long l, long long h);

    void Generate_Map(int Xspecial, int Yspecial);

    void Update_Map(int Sx, int Sy);
public:
    enum Status
    {
        MINE = -1,
        EMPTY = 0,
    };

    GameExecution();
    GameExecution(vector<vector<float>>* timeOpen, vector<vector<float>>* timeFlag, int& playTime, int& curFlags, int& cellsLeft);

    int Getheight();

    int Getwidth();

    int Getmine();

    int status(int x, int y);

    bool checkClicked();

    bool checkInTable(int x, int y);

    bool checkOpened(int x, int y);

    bool checkNotOpened(int x, int y);

    bool checkFlaged(int x, int y);

    bool checkUnFlaged(int x, int y);

    bool valid(int x, int y);

    int askOpen(int x, int y);

    bool askFlag(int x, int y);

    bool askUnFlag(int x, int y);

    int updateHighScore(int totalTime);

    void save(vector<vector<float>>* timeOpen, vector<vector<float>>* timeFlag, int playTime, int curFlags, int cellsLeft);
};

