#pragma once

#include <iostream>
#include <sstream>

#include "SFML/Graphics.hpp"

using namespace sf;

enum TB_KEY
{
	DELETE_KEY = 8,
	ENTER_KEY = 13,
	ESCAPE_KEY = 27
};

class Textbox
{
private:
	Text textValue;
	RectangleShape shape;
	std::ostringstream text;
	bool isLock;
	bool isSelected;
	bool hasLimit;
	int limit;

	void initVariables();
	void inputLogic(int charTyped);
	void deleteLastChar();
public:

	Textbox();
	Textbox(int fontSize, float boxWidth, float boxHeight, Color textColor, Color bgColor);

	void lockBox();

	void setFont(Font& font);

	void setPosition(Vector2f pos);

	void setLimt(bool ToF);

	void setInitText(std::string s);

	void setLimit(bool ToF, int lim);

	void setSelected(bool sel);

	std::string getText();

	void render(RenderTarget* target);

	bool updateByMouse(const Vector2f mousePos);

	void update(Event input);
};

