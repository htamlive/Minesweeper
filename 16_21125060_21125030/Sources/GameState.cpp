#include "GameState.h"
#include <iostream>


void GameState::initKeyBinds()
{
	this->keybinds.emplace("MOVE_LEFT", this->supportedKeys->at("A"));
	this->keybinds.emplace("MOVE_UP", this->supportedKeys->at("W"));
	this->keybinds.emplace("MOVE_RIGHT", this->supportedKeys->at("D"));
	this->keybinds.emplace("MOVE_DOWN", this->supportedKeys->at("S"));
	this->keybinds.emplace("CLOSE", this->supportedKeys->at("Escape"));
}

void GameState::initBackground()
{
	this->background.setSize(Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)
	)
	);
	//std::cout << system("dir")<<"\n";
	std::cout << this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg0.png");

	this->background.setTexture(&this->backgroundTexture);
}

std::string GameState::getMode()
{
	std::string mode;
	switch (this->curLv)
	{
	case LV_EASY:
		mode = "EASY"; break;
	case LV_MEDIUM:
		mode = "MEDIUM"; break;
	case LV_HARD:
		mode = "HARD"; break;
	case LV_CUSTOM:
		mode = "CUSTOM"; break;
	default:
		break;
	}
	//cout << "\n" << this->curLv << " ";
	return "Mode: " + mode;
}

void GameState::initVariables(int rows, int cols, int mines, int curLv)
{
	this->width = 100.f;
	this->height = 100.f;
	if (this->lastPlay) {
		std::ifstream ifs("Data/basicSpecifications.txt");
		if (ifs.is_open()) {
			ifs >> this->rows;
			ifs >> this->columns;
			ifs >> this->mines;
			ifs >> this->curLv;
		}
		ifs.close();
	}
	else {
		this->rows = rows;
		this->columns = cols;
		this->mines = mines;
		this->curLv = curLv;
		std::ofstream ofs("Data/basicSpecifications.txt");
		if (ofs.is_open()) {
			ofs << this->rows << "\n";
			ofs << this->columns << "\n";
			ofs << this->mines << "\n";
			ofs << this->curLv << "\n";
		}
		ofs.close();
	}

}

void GameState::initFonts()
{
	if (this->font.loadFromFile("Fonts/UVNBachTuyet_B.ttf")) {
		//throw("COULD NOT LOAD FRONTS IN MMS");
	}
}

void GameState::initCells()
{
	int totalX = this->window->getSize().x;
	int totalY = this->window->getSize().y - 150;

	this->adjustCells(totalX, totalY);

	this->cellController = new CellController(this->setCenter(totalX,totalY).x, this->setCenter(totalX, totalY).y, this->rows, this->columns,this->mines, this->width, this->height, this->gameOptions);
}

void GameState::initStatusBar()
{
	short width = this->window->getSize().x, height = 150;
	this->statusBar = new StatusBar(this->window->getSize().x - width, this->window->getSize().y - height, width, height, &this->font, Color(255, 166, 0));
}

GameState::GameState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->lastPlay = true;
	this->initVariables();
	this->initFonts();
	this->initCells();
	this->initStatusBar();
	this->initKeyBinds();

}

GameState::GameState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, GameOptions* gameOptions)
	: State(window, supportedKeys, states, gameOptions)
{
	this->lastPlay = true;
	this->initVariables();
	this->initFonts();
	this->initCells();
	this->initStatusBar();
	this->initKeyBinds();

}


GameState::GameState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, int rows, int cols, int mines, int curLv)
	: State(window, supportedKeys, states)
{
	this->initVariables(rows, cols, mines, curLv);
	this->initFonts();
	this->initCells();
	this->initStatusBar();
	this->initKeyBinds();
	//this->initBackground();
}

GameState::GameState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, int rows, int cols, int mines, int curLv, GameOptions* gameOptions)
	: State(window, supportedKeys, states, gameOptions)
{
	this->initVariables(rows, cols, mines, curLv);
	this->initFonts();
	this->initCells();
	this->initStatusBar();
	this->initKeyBinds();
	//this->initBackground();
}

GameState::~GameState()
{
	delete this->cellController;
	delete this->statusBar;
}

void GameState::adjustCells(const int totalX, const int totalY)
{
	int xx = totalX / this->columns;
	int yy = totalY / this->rows;
	this->width = this->height = std::min(totalX / this->columns, totalY / this->rows);
}

Vector2u GameState::setCenter(const int totalX, const int totalY)
{
	int x = totalX / 2 - this->columns * this->width / 2;
	int y = totalY / 2 - this->rows * this->height / 2;
	return Vector2u(x, y);
}

bool GameState::checkLastPlay()
{
	return this->lastPlay;
}

void GameState::updateEvents()
{
	switch (this->ev.type)
	{
	case Event::Closed:
		this->cellController->saveGame();
		this->endState();
		break;
	default:
		break;
	}
}

void GameState::updateInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player.move(dt, -1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player.move(dt, 0.f, -1.f);
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player.move(dt, 1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player.move(dt, 0.f, 1.f);
	
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void GameState::updateCells()
{
	cellController->update(this->mousePosView);
}

void GameState::updateStatusBar()
{
	int playTime = 0;
	std::string info = this->getMode();
	if (this->cellController->checkStarted()) {
		playTime = (int)this->cellController->getPlayTime();
	}
	

	if (this->cellController->checkLose()) {
		this->statusBar->setTextExitButton("BACK  AND \n REVENGE!!");
	}	
	
	if (this->cellController->checkWin()) {
		this->statusBar->setTextExitButton("             YOU WIN \n BACK AND PLAY AGAIN!");
		int score = this->cellController->updateHighScore();
		info += " | Point: " + to_string(score);
	}

	this->statusBar->update(this->cellController->getCurrentFlags(), playTime, this->mousePosView, info);

	if (this->statusBar->isQuit()) {
		this->cellController->saveGame();
		this->endState();
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePos();
	this->updateInput(dt);
	this->updateCells();
	this->updateStatusBar();
	this->player.update(dt);
}

void GameState::render(RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	//target->draw(this->background);
	this->player.render(target);

	this->renderCells(target);
	this->renderStatusBar(target);
}

void GameState::renderCells(RenderTarget* target)
{
	this->cellController->render(target);
}

void GameState::renderStatusBar(RenderTarget* target)
{
	this->statusBar->render(target);
}
