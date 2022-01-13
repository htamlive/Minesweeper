#pragma once
#include "Button.h"

class StatusBar
{
private:
	RectangleShape shape;

	std::map<std::string, Button*> buttons;

	Font* font;
	Text currentFlags, playTime, currentLevel;

	bool quit;

	void initButtons();
	void updateCurrentTime(int playTime);
	void updateCurrentFlags(int currentFlags);
	void updateCurLevel(std::string text);
public:	
	StatusBar(float x, float y, float width, float height, Font* font, Color color);
	virtual ~StatusBar();

	bool isQuit();
	void setTextExitButton(std::string text);

	void updateButtons(Vector2f mousePosView);


	void update(int currentFlags, int playTime, Vector2f mousePosView, std::string mode);

	void renderButtons(RenderTarget* target);
	void render(RenderTarget* target);

};

