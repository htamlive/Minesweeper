#pragma once
#include <ctime>
#include <cstdio>
#include <fstream>
#include <sstream>

#include "Entity.h"
#include "GameOptions.h"

class State
{
private:


protected:
	std::stack<State*>* states;
	GameOptions* gameOptions;
	RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	std::map<std::string, sf::Texture*> textures;
	bool quit;

	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	

	virtual void initKeyBinds() = 0;
public:

	State(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	State(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, GameOptions* gameOptions);
	virtual ~State();
	Event ev;

	const bool& getQuit() const;
	void endState();
	virtual void updateMousePos();
	virtual void updateInput(const float& dt) = 0;

	virtual void updateEvents() = 0;
	//pure virtual classes
	

	virtual void update(const float& dt) = 0;
	virtual void render(RenderTarget* target = nullptr) = 0;
};

