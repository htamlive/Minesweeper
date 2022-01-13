#pragma once
#include "GameState.h"
#include "OptionsState.h"
#include "Button.h"
#include "Numbox.h"
#include "RankTable.h"

class MainMenuState : public State
{

private:

	Texture backgroundTexture;
	Sprite bgSprite;
	RectangleShape background;
	Font fontSquid;
	Font font;
	RankTable* rankTable;


	std::map<std::string, Button*> buttons;
	std::map<std::string, Numbox*> numboxes;
	std::map<int, int> levelRows;
	std::map<int, int> levelCols;
	std::map<int, int> levelMines;

	bool lastPlay;
	short curLv;

	void initVariables();
	void initBackground();
	void initFonts();
	void initKeyBinds();
	void initButtons();
	void initNumboxes();
	void initData();
	void initRankTable();
	
	bool getInput(int &rows, int &cols, int &mines);
public:
	MainMenuState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	MainMenuState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, GameOptions* gameOptions);
	virtual ~MainMenuState();

	void showInputConditions(RenderTarget* target);

	void updateEvents();
	void updateInput(const float& dt);
	void updateButtons();
	void updateNumboxes();
	void update(const float& dt);
	void renderButtons(RenderTarget *target = nullptr);
	void renderNumboxes(RenderTarget* target);
	void render(RenderTarget* target = nullptr);
};

