#pragma once
#include "GameState.h"
#include "Button.h"

class OptionsState : public State
{

private:
	Texture backgroundTexture;
	RectangleShape background;
	Font font;

	std::map<std::string, Button*> buttons;
	std::map<std::string, Text*> textSet;
	Text resetHighScore;

	void initVariables();
	void initBackground();
	void initFonts();
	void initKeyBinds();
	void initButtons();
public:
	OptionsState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	OptionsState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, GameOptions* gameOptions);
	virtual ~OptionsState();

	void updateEvents();
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(RenderTarget* target = nullptr);
	void render(RenderTarget* target = nullptr);

};

