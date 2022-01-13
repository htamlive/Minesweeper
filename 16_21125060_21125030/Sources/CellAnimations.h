#pragma once
#include "Cell.h"
#include "GameExecution.h"

constexpr float OPEN_DURATION = 0.125f;
constexpr float FLAG_DURATION = 0.150f;

class CellAnimations
{
private:
	float width, height;
	bool* isOver;
	bool* isWin;

	Cell* revealedModel1;
	Cell* revealedModel2;
	Cell* model1;
	Cell* model2;
	Cell* blackModel;

	Cell* bombModel;
	Cell* lockModel;

	GameExecution* gameExec;

	std::vector<Texture> numsTexture;

	std::vector<std::vector<Cell*>>* cells;
	std::vector<std::vector<int>>* test;

	std::vector<std::vector<float>>* timeOpen;
	std::vector<std::vector<float>>* timeFlag;

	void initModel();
public:
	CellAnimations(std::vector<std::vector<Cell*>>* cells,
				std::vector<std::vector<float>>* timeOpen, std::vector<std::vector<float>>* timeFlag,
				float width, float height, bool* isOver, bool* isWin);

	CellAnimations(std::vector<std::vector<Cell*>>* cells, GameExecution* gameExec,
				std::vector<std::vector<float>>* timeOpen, std::vector<std::vector<float>>* timeFlag,
				float width, float height, bool* isOver, bool* isWin);

	CellAnimations(std::vector<std::vector<Cell*>>* cells, std::vector<std::vector<int>>* test,
				std::vector<std::vector<float>>* timeOpen, std::vector<std::vector<float>>* timeFlag,
				float width, float height, bool* isOver, bool* isWin);

	void openCellAnimation(short row, short col, RenderTarget* target, float seconds);
	void setOpenCell(int row, int col);

	void winningAnimation(int row, int col, RenderTarget* target, float seconds);

	void flagCellAnimation(short row, short col, RenderTarget* target, float seconds);
	void setFlagCell(int row, int col, float seconds);

	void bombAnimation(int row, int col);
	void showNumber(int row, int col, RenderTarget* target);

	void update();
	void render(RenderTarget* target, float seconds);

	bool checkIsOver();
	bool checkIsWin();
	bool checkIsLose();
	virtual ~CellAnimations();
};

