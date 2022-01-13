#include "GameExecution.h"

#include <iostream>

void GameExecution::reset()
{
    for (int x = 1; x <= this->height; x++)
        for (int y = 1; y <= this->width; y++) this->Map[x][y] = this->flag[x][y] =  this->open[x][y] = 0;
}

void GameExecution::getBasicFromFile()
{

    ifstream ifs("Data/basicSpecifications.txt");
    ifs >> this->height;
    ifs >> this->width;
    ifs >> this->num_mine;
    ifs >> this->curLv;
    ifs.close();
}

void GameExecution::checkLastPlay()
{
    ifstream ifs("Data/lastPlay.txt");
    if (ifs.is_open()) {
        ifs >> this->firstclick;
    }

    ifs.close();
}

void GameExecution::initTable()
{
    if (this->firstclick) {
        ifstream ifs("Data/boardValues.txt");
        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < this->width; ++j) {
                ifs >> this->Map[i + 1][j + 1];
            }
        }
        
        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < this->width; ++j) {
                ifs >> this->open[i + 1][j + 1];
            }
        }       
        
        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < this->width; ++j) {
                ifs >> this->flag[i + 1][j + 1];
            }
        }

        ifs.close();
    }
    else {
        this->reset();
    }

}

long long GameExecution::Rand(long long l, long long h)
{
    return l + ((long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) * (RAND_MAX + 1) +
        (long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
        (long long)rand() * (RAND_MAX + 1) +
        rand()) % (h - l + 1);
}

void GameExecution::Generate_Map(int Xspecial, int Yspecial)
{
    srand(time(NULL));

    for (int i = 1; i <= num_mine; i++) {
        int x = 0, y = 0;
        do {
            x = Rand(1, height), y = Rand(1, width);
        } while (status(x, y) == -1 || (x == Xspecial && y == Yspecial));
        Map[x][y] = -1;

        for (int u = x - 1; u <= x + 1; u++)
            for (int v = y - 1; v <= y + 1; v++)
                if (status(u, v) != -1) Map[u][v]++;
    }
    /*
        cout << "\n";
        for (int i = 1; i <= this->height; ++i) {
            for (int j = 1; j <= this->width; ++j) {
                std::cout << this->status(i, j) << " ";
            }
            cout << "\n";
        }
    */

}

void GameExecution::Update_Map(int Sx, int Sy)
{
    queue <pair <int, int>> Queue;
    open[Sx][Sy] = true;
    if(this->status(Sx, Sy) == Status::EMPTY)
        Queue.push({ Sx, Sy });
    while (Queue.size()) {
        int x = Queue.front().first;
        int y = Queue.front().second;
        Queue.pop();
        for (int u = x - 1; u <= x + 1; u++)
            for (int v = y - 1; v <= y + 1; v++) if (valid(u, v)) {
                open[u][v] = true;
                if (status(u, v) == 0)
                    Queue.push({ u, v });
            }
    }
}

GameExecution::GameExecution()
{
    this->getBasicFromFile();
    this->checkLastPlay();
    this->initTable();
}


GameExecution::GameExecution(vector<vector<float>>* timeOpen, vector<vector<float>>* timeFlag, int& playTime, int& curFlags, int& cellsLeft)
{
    this->getBasicFromFile();

    ifstream ifs("Data/lastPlay.txt");

    if (ifs.is_open()) {
        ifs >> this->firstclick;
        if (this->firstclick) {
            ifs >> playTime;
            ifs >> curFlags;
            ifs >> cellsLeft;
        }
    }
    ifs.close();

    if (this->firstclick) {
        ifs.open("Data/boardValues.txt");

        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < this->width; ++j) {
                ifs >> this->Map[i + 1][j + 1];
            }
        }

        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < this->width; ++j) {
                ifs >> this->open[i + 1][j + 1];
            }
        }

        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < this->width; ++j) {
                ifs >> this->flag[i + 1][j + 1];
            }
        }

        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < this->width; ++j) {
                ifs >> (*timeOpen)[i][j];
            }
        }

        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < this->width; ++j) {
                ifs >> (*timeFlag)[i][j];
            }
        }

        ifs.close();
    }
    else {
        this->reset();
    }
}


int GameExecution::Getheight()
{
    return this->height;
}

int GameExecution::Getwidth()
{
    return this->width;
}

int GameExecution::Getmine()
{
    return this->num_mine;
}

int GameExecution::status(int x, int y)
{
    /// -1: Mine
    ///  0: Empty grid
    ///1,2,3...: num of mines
    return this->Map[x][y];
}

bool GameExecution::checkClicked()
{
    return this->firstclick;
}

bool GameExecution::checkInTable(int x, int y)
{
    return 1 <= x && x <= this->height && 1 <= y && y <= this->width;
}

bool GameExecution::checkOpened(int x, int y)
{
    return this->checkInTable(x, y) && (this->open[x][y]);
}

bool GameExecution::checkNotOpened(int x, int y)
{
    return this->checkInTable(x, y) && !(this->open[x][y]);
}

bool GameExecution::checkFlaged(int x, int y)
{
    return this->checkInTable(x, y) && (this->flag[x][y]);
}

bool GameExecution::checkUnFlaged(int x, int y)
{
    return this->checkInTable(x, y) && !(this->flag[x][y]);
}

bool GameExecution::valid(int x, int y)
{
    return this->checkNotOpened(x, y) && this->status(x, y) != Status::MINE;
}

int GameExecution::askOpen(int x, int y)
{
    if (!(this->firstclick)) {
        this->firstclick = true;
        this->Generate_Map(x, y);
    }
    //if (valid(x, y)) Update_Map(x, y); 
    Update_Map(x, y);
    return status(x, y);
}

bool GameExecution::askFlag(int x, int y)
{
    if(this->flag[x][y])
        return false;
    this->flag[x][y] = true;
    return true;
}

bool GameExecution::askUnFlag(int x, int y)
{
    if (!(this->flag[x][y]))
        return false;
    this->flag[x][y] = false;
    return true;
}

int GameExecution::updateHighScore(int totalTime)
{
    float score = 1 / pow((totalTime + 1), 0.1f);
    score = (9999 - totalTime) * score;
    score += 0.602f;
    ifstream ifs("Data/highScore.txt");
    int easy, medium, hard;
    ifs >> easy;
    ifs >> medium;
    ifs >> hard;
    ifs.close();
    ofstream ofs("Data/highScore.txt");
    switch (this->curLv)
    {
    case LV_EASY: 
        easy = (easy < score) ? score : easy; 
        break;
    case LV_MEDIUM: 
        medium = (medium < score) ? score : medium; 
        break;
    case LV_HARD:
        hard = (hard < score) ? score : hard; 
        break;
    default:
        break;
    }
    ofs << easy << "\n";
    ofs << medium << "\n";
    ofs << hard << "\n";
    ofs.close();
    return score;
}

void GameExecution::save(vector<vector<float>>* timeOpen, vector<vector<float>>* timeFlag, int playTime, int curFlags, int cellsLeft)
{
    ofstream ofs("Data/boardValues.txt");
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            ofs <<  this->Map[i + 1][j + 1] << " ";
        }
    }

    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            ofs << this->open[i + 1][j + 1] << " ";
        }
    }

    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            ofs << this->flag[i + 1][j + 1] << " ";
        }
    }    
    
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            ofs << (*timeOpen)[i][j] << " ";
        }
    }
    
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            ofs << (*timeFlag)[i][j] << " ";
        }
    }

    ofs.close();

    ofs.open("Data/lastPlay.txt");
    ofs << 1 << " " << playTime << " " << curFlags << " " << cellsLeft << "\n";
    ofs.close();
}

