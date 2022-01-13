#pragma once
#include <vector>

#include "Cell.h"
#include "CellAnimations.h"
#include "GameSounds.h"
#include "GameOptions.h"

class CellController
{
private:
	float height, width, startTime, totalTime;
	int mines, cellsLeft, currentFlags, lastPlayTime;
	bool isOver, isWin;
	Clock clock;

	std::vector<std::vector<Cell*>> cells;
	std::vector<std::vector<int>> test;
	std::vector<std::vector<float>> timeOpen;
	std::vector<std::vector<float>> timeFlag;

	CellAnimations* cellAnimations;
	GameExecution* gameExec;
	GameSounds* gameSound;
	GameOptions* gameOptions;
	
public:
	virtual ~CellController();
	CellController(int x, int y, int rows, int cols, int mines, float width, float height);
	CellController(int x, int y, int rows, int cols, int mines, float width, float height, GameOptions* gameOptions);

	bool checkStarted();
	bool checkWin();
	bool checkLose();

	bool openCell(short row, short col);
	void setOpenCellStatus(int row, int col);
	void updateOpenCells();
	bool flagOrUnflagCell(short row, short col);

	void udpateMouseClick();
	void update(const Vector2f mousePos);
	void render(RenderTarget* target);

	float getStartTime();
	float getPlayTime();

	float get_height();
	float get_width();

	int getCurrentFlags();
	int updateHighScore();
	void saveGame();
};

