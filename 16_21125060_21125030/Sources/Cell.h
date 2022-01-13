#pragma once
#include "Button.h"

using namespace sf;

enum cell_states {C_NULL = 1, C_NUM = 2, C_BOMB = 3 };
class Cell
	: public Button
{
private:
	short cellType;
	bool isOpened;
	bool isFlaged;
public:

	Cell(float x, float y, float width, float height, Font* font, std::string text, Color idleColor, Color hoverColor, Color activeColor);

	void setPosition(const float x, const float y);
	void setSize(Vector2f size);
	void updateState(const int state);

	short getState();
	float get_x();
	float get_y();
	float get_height();
	float get_width();
	RectangleShape getCellObject();

	bool checkOpened();
	bool checkNum();
	bool checkFlag();
	bool checkBomb();
	bool checkNull();

	bool openCell();
	bool closeCell();
	bool flagCell();
	bool unFlagCell();

	bool bombCell();
	bool numCell();
	bool defaultCell();

	void copyColor(Cell* target);
};

