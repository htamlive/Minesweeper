#include "MainMenuState.h"
#include <iostream>


void MainMenuState::initVariables()
{
	this->curLv = LV_EASY;
}

void MainMenuState::initBackground()
{
	this->background.setSize(Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)
		)
	);
	//std::cout << system("dir")<<"\n";
	this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png");
	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (this->fontSquid.loadFromFile("Fonts/FzGameOfSquidsver202.ttf")) {
		//throw("COULD NOT LOAD FRONTS IN MMS");
	}	
	
	if (this->font.loadFromFile("Fonts/UVNBachTuyet_R.TTF")) {
		//throw("COULD NOT LOAD FRONTS IN MMS");
	}
}

void MainMenuState::initKeyBinds()
{
	this->keybinds.emplace("MOVE_LEFT", this->supportedKeys->at("A"));
	this->keybinds.emplace("MOVE_UP", this->supportedKeys->at("W"));
	this->keybinds.emplace("MOVE_RIGHT", this->supportedKeys->at("D"));
	this->keybinds.emplace("MOVE_DOWN", this->supportedKeys->at("S"));
}

void MainMenuState::initButtons()
{
	this->buttons["LOAD_STATE"] = new Button(420, 240, 150, 50,
		&this->font, "LOAD GAME",
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));

	this->buttons["GAME_STATE"] = new Button(420, 330, 150, 50,
		&this->font, "NEW GAME",
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));

	//this->buttons["GAME_STATE"]->setTextSize(20);
	//this->buttons["GAME_STATE"]->setCenter();

	this->buttons["OPTIONS_STATE"] = new Button(420, 530, 150, 50,
		&this->font, "OPTIONS",
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(420, 630, 150, 50,
		&this->font, "QUIT",
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));


	this->buttons["EASY_OPTION"] = new Button(445, 400, 100, 30,
		&this->font, "EASY",
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));

	this->buttons["EASY_OPTION"]->setTextSize(14);
	this->buttons["EASY_OPTION"]->setCenter();

	this->buttons["MEDIUM_OPTION"] = new Button(445, 440, 100, 30,
		&this->font, "MEDIUM",
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));

	this->buttons["MEDIUM_OPTION"]->setTextSize(14);
	this->buttons["MEDIUM_OPTION"]->setCenter();

	this->buttons["HARD_OPTION"] = new Button(445, 480, 100, 30,
		&this->font, "HARD",
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));

	this->buttons["HARD_OPTION"]->setTextSize(14);
	this->buttons["HARD_OPTION"]->setCenter();
}

void MainMenuState::initNumboxes()
{
	this->numboxes["INPUT_ROWS"] = new Numbox(30, 47, 40, Color::Black,Color::White);
	this->numboxes["INPUT_ROWS"]->setFont(this->font);
	this->numboxes["INPUT_ROWS"]->setPosition(Vector2f(700.f, 320.f));
	this->numboxes["INPUT_ROWS"]->setLimit(true, 2);
	this->numboxes["INPUT_ROWS"]->setInitText("8");

	this->numboxes["INPUT_COLS"] = new Numbox(30, 47, 40, Color::Black, Color::White);
	this->numboxes["INPUT_COLS"]->setFont(this->font);
	this->numboxes["INPUT_COLS"]->setPosition(Vector2f(700.f, 382.f));
	this->numboxes["INPUT_COLS"]->setLimit(true, 2);
	this->numboxes["INPUT_COLS"]->setInitText("10");

	this->numboxes["INPUT_MINES"] = new Numbox(30, 47, 40, Color::Black, Color::White);
	this->numboxes["INPUT_MINES"]->setFont(this->font);
	this->numboxes["INPUT_MINES"]->setPosition(Vector2f(700.f, 450.f));
	this->numboxes["INPUT_MINES"]->setLimit(true, 2);
	this->numboxes["INPUT_MINES"]->setInitText("10");

	
	//std::cout << "\n Hello " << this->numboxes["INPUT_ROWS"]->isSelected;
}

void MainMenuState::initData()
{
	std::ifstream ifs("Data/default.txt");
	if (ifs.is_open()) {
		for (int i = LV_EASY; i <= LV_HARD; i++)
		{
			ifs >> this->levelRows[i];
			ifs >> this->levelCols[i];
			ifs >> this->levelMines[i];
		}

	}
	ifs.close();

	ifs.open("Data/lastPlay.txt");
	if (ifs.is_open()) {
		ifs >> this->lastPlay; 
	}
	//this->lastPlay = true;
	ifs.close();

}

void MainMenuState::initRankTable()
{
	this->rankTable = new RankTable(&this->numboxes, &this->font);
}

bool MainMenuState::getInput(int& rows, int& cols, int& mines)
{
	if (this->numboxes["INPUT_ROWS"]->getText() != "" && this->numboxes["INPUT_COLS"]->getText() != ""
		&& this->numboxes["INPUT_MINES"]->getText() != "") {
		rows = std::stoi(this->numboxes["INPUT_ROWS"]->getText());
		cols = std::stoi(this->numboxes["INPUT_COLS"]->getText());
		mines = std::stoi(this->numboxes["INPUT_MINES"]->getText());
		return mines < cols * rows;
	}
	return false;
}

MainMenuState::MainMenuState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initData();
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeyBinds();
	this->initButtons();
	this->initNumboxes();
	this->initRankTable();
}

MainMenuState::MainMenuState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, GameOptions* gameOptions)
	: State(window, supportedKeys, states, gameOptions)
{
	this->initData();
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeyBinds();
	this->initButtons();
	this->initNumboxes();
	this->initRankTable();
}

MainMenuState::~MainMenuState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {

		delete it->second;
	}	
	for (auto it = this->numboxes.begin(); it != this->numboxes.end(); ++it) {

		delete it->second;
	}
}

void MainMenuState::showInputConditions(RenderTarget* target)
{
	Text noti;
	noti.setString("NOTE: \n - Please do not leave NULL \n - Please enter positive integers \n - For best experience, enter \nrows and columns less than 51 \n -  There is at least 1 safe cell");
	noti.setPosition(Vector2f(700.f, 545.f));
	noti.setCharacterSize(14);
	noti.setFillColor(Color::Black);
	noti.setFont(this->font);
	target->draw(noti);

}

void MainMenuState::updateEvents()
{
	switch (this->ev.type)
	{
	case Event::Closed:
		this->endState();
		break;
	case Event::TextEntered:

		this->updateNumboxes();
		//std::cout << "\n" << this->ev.text.unicode;
		break;
	default:
		break;
	}
}

void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["LOAD_STATE"]->isPressedLeft()) {
		this->states->push(new GameState(this->window, this->supportedKeys, this->states, this->gameOptions));
	}

	if (this->buttons["GAME_STATE"]->isPressedLeft()) {
		//std::cout << "hi";
		int rows, cols, mines;
		if (this->getInput(rows, cols, mines)) {
			//std::cout << "\n" << rows << " " << cols << " " << mines << " CurLv: " << this->curLv;
			if (rows != this->levelRows[this->curLv] || cols != this->levelCols[this->curLv] || mines != this->levelMines[this->curLv]) {
				this->curLv = LV_CUSTOM;
			}
			ofstream ofs("Data/lastPlay.txt"); ofs << 0; ofs.close();
			this->states->push(new GameState(this->window, this->supportedKeys, this->states, rows, cols, mines, this->curLv, this->gameOptions));
		}
	}
	
	if (this->buttons["EXIT_STATE"]->isPressedLeft()) {
		this->endState();
	}
	
	if (this->buttons["OPTIONS_STATE"]->isPressedLeft()) {
		this->states->push(new OptionsState(this->window, this->supportedKeys, this->states, this->gameOptions));
	}

	if (this->buttons["EASY_OPTION"]->isPressedLeft()) {
		//std::cout << "hi";
		this->numboxes["INPUT_ROWS"]->setInitText(std::to_string(this->levelRows[LV_EASY]));
		this->numboxes["INPUT_COLS"]->setInitText(std::to_string(this->levelCols[LV_EASY]));
		this->numboxes["INPUT_MINES"]->setInitText(std::to_string(this->levelMines[LV_EASY]));
		this->curLv = LV_EASY;
	}
	
	if (this->buttons["MEDIUM_OPTION"]->isPressedLeft()) {
		this->numboxes["INPUT_ROWS"]->setInitText(std::to_string(this->levelRows[LV_MEDIUM]));
		this->numboxes["INPUT_COLS"]->setInitText(std::to_string(this->levelCols[LV_MEDIUM]));
		this->numboxes["INPUT_MINES"]->setInitText(std::to_string(this->levelMines[LV_MEDIUM]));
		this->curLv = LV_MEDIUM;
	}
	
	if (this->buttons["HARD_OPTION"]->isPressedLeft()) {
		this->numboxes["INPUT_ROWS"]->setInitText(std::to_string(this->levelRows[LV_HARD]));
		this->numboxes["INPUT_COLS"]->setInitText(std::to_string(this->levelCols[LV_HARD]));
		this->numboxes["INPUT_MINES"]->setInitText(std::to_string(this->levelMines[LV_HARD]));
		this->curLv = LV_HARD;
	}
}

void MainMenuState::updateNumboxes()
{
	for (auto it : this->numboxes) {
		it.second->update(this->ev);
	}
}

void MainMenuState::update(const float& dt)
{

	ifstream ifs("Data/lastPlay.txt"); ifs >> this->lastPlay; ifs.close();

	if (!this->lastPlay) {
		this->buttons["LOAD_STATE"]->setPosition(Vector2f(420, 1230));
		this->buttons["LOAD_STATE"]->setCenter();
	}
	else {
		this->buttons["LOAD_STATE"]->setPosition(Vector2f(420, 245 ));
		this->buttons["LOAD_STATE"]->setCenter();
	}

	this->updateMousePos();

	this->updateInput(dt);

	this->updateButtons();

	for (auto it : this->numboxes) {
		it.second->updateByMouse(this->mousePosView);
	}

	this->rankTable->updateData();

	//system("cls");
	//std::cout << this->mosePosView.x << " " << this->mosePosView.y << "\n";
}

void MainMenuState::renderButtons(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::renderNumboxes(RenderTarget* target)
{
	for (auto it : this->numboxes) {
		it.second->render(target);
	}
}

void MainMenuState::render(RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(target);
	this->renderNumboxes(target);
	this->showInputConditions(target);
	//this->gamestate_btn->render(target);
}
