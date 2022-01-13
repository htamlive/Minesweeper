#pragma once
#include <iostream>
#include <vector>

#include "MainMenuState.h"

using namespace sf;

class Game
{
private:
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;
	std::vector<VideoMode> videoModes;
	ContextSettings windowSettings;
	bool fullscreen;

	Clock dtClock;
	float dt;

	std::stack<State*> states;
	GameOptions* gameOptions;
	std::map<std::string, int> supportedKeys;
	std::map<std::string, Button*> buttons;
	Music music;
	

	void initVariables();
	void initWindow();
	void initKeys();
	void initState();

	void updateEvents();
	void updateDt();
	void updateMusic();

public:
	Game();
	virtual ~Game();

	const bool running() const;

	void endApplication();

	void updateSFMLEvents();
	void update();

	void render();
	void run();
	
	void closeWindow();
	void keyReleasedProc();
	void mouseProc();
};

