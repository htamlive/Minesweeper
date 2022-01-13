#pragma once
#include "State.h"
#include "CellController.h"
#include "StatusBar.h"

class GameState: public State
{
private:
	Texture backgroundTexture;
	RectangleShape background;

	Font font;

	StatusBar* statusBar;

	int curLv , rows, columns, mines, currentFlags;
	float height, width;
	bool lastPlay;

	Entity player;
	CellController* cellController;

	void initVariables(int rows = 8, int cols = 10, int mines = 10, int curLv = LV_EASY);
	void initFonts();
	void initCells();
	void initStatusBar();
	void initKeyBinds();
	void initBackground();

	std::string getMode();
	
public:

	GameState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	GameState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, GameOptions* gameOptions);
	GameState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, int rows, int cols, int mines, int curLv);
	GameState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, int rows, int cols, int mines, int curLv, GameOptions* gameOptions);
	virtual ~GameState();
	void adjustCells(const int totalX, const int totalY);
	Vector2u setCenter(const int totalX, const int totalY);

	bool checkLastPlay();

	void updateEvents();
	void updateInput(const float& dt);
	void updateCells();
	void updateStatusBar();
	void update(const float& dt);
	void renderCells(RenderTarget* target);
	void renderStatusBar(RenderTarget* target);
	void render(RenderTarget* target = nullptr);
};

