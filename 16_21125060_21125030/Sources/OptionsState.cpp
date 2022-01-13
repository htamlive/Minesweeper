#include "OptionsState.h"
#include "MainMenuState.h"
#include <iostream>


void OptionsState::initVariables()
{

}

void OptionsState::initBackground()
{
	this->background.setSize(Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)
	)
	);
	//std::cout << system("dir")<<"\n";
	std::cout << this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg2.png");

	this->background.setTexture(&this->backgroundTexture);
}

void OptionsState::initFonts()
{
	if (this->font.loadFromFile("Fonts/UVNBachTuyet_R.ttf")) {
		//throw("COULD NOT LOAD FRONTS IN MMS");
	}
}

void OptionsState::initKeyBinds()
{
	this->keybinds.emplace("MOVE_LEFT", this->supportedKeys->at("A"));
	this->keybinds.emplace("MOVE_UP", this->supportedKeys->at("W"));
	this->keybinds.emplace("MOVE_RIGHT", this->supportedKeys->at("D"));
	this->keybinds.emplace("MOVE_DOWN", this->supportedKeys->at("S"));
}
void OptionsState::initButtons()
{
	this->buttons["RESET_HIGHSCORE"] = new Button(250, 150, 75, 25,
		&this->font, "RESET",
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));

	this->textSet["RESET_HIGHSCORE"] = new Text();
	this->textSet["RESET_HIGHSCORE"]->setString("- Reset high scores");
	this->textSet["RESET_HIGHSCORE"]->setPosition(Vector2f(50.f, 150.f));
	this->textSet["RESET_HIGHSCORE"]->setCharacterSize(20);
	this->textSet["RESET_HIGHSCORE"]->setFillColor(Color::Black);
	this->textSet["RESET_HIGHSCORE"]->setFont(this->font);

	this->buttons["SOUND"] = new Button(250, 200, 75, 25,
		&this->font, "ON",
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));
	if (!this->gameOptions->checkSound()) this->buttons["SOUND"]->setText("OFF");

	this->textSet["SOUND"] = new Text();
	this->textSet["SOUND"]->setString("- Sound");
	this->textSet["SOUND"]->setPosition(Vector2f(50.f, 200.f));
	this->textSet["SOUND"]->setCharacterSize(20);
	this->textSet["SOUND"]->setFillColor(Color::Black);
	this->textSet["SOUND"]->setFont(this->font);
	
	
	this->buttons["MUSIC"] = new Button(250, 250, 75, 25,
		&this->font, "ON",
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));
	if (!this->gameOptions->checkMusic()) this->buttons["MUSIC"]->setText("OFF");

	this->textSet["MUSIC"] = new Text();
	this->textSet["MUSIC"]->setString("- Music");
	this->textSet["MUSIC"]->setPosition(Vector2f(50.f, 250.f));
	this->textSet["MUSIC"]->setCharacterSize(20);
	this->textSet["MUSIC"]->setFillColor(Color::Black);
	this->textSet["MUSIC"]->setFont(this->font);

	this->buttons["EXIT_STATE"] = new Button(50, 650, 150, 50,
		&this->font, "BACK",
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));

}
OptionsState::OptionsState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeyBinds();
	this->initButtons();

}

OptionsState::OptionsState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, GameOptions* gameOptions)
	: State(window, supportedKeys, states, gameOptions)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeyBinds();
	this->initButtons();

}

OptionsState::~OptionsState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {

		delete it->second;
	}
}


void OptionsState::updateEvents()
{
}

void OptionsState::updateInput(const float& dt)
{

}

void OptionsState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["EXIT_STATE"]->isPressedLeft()) {
		this->endState();
	}		
	
	if (this->buttons["SOUND"]->isPressedLeft()) {
		if (this->gameOptions->checkSound()) {
			this->gameOptions->setMuteSound();
			this->buttons["SOUND"]->setText("OFF");
		}
		else {
			this->gameOptions->setSound();
			this->buttons["SOUND"]->setText("ON");
		}
	}	
	
	if (this->buttons["MUSIC"]->isPressedLeft()) {
		if (this->gameOptions->checkMusic()) {
			this->gameOptions->setMuteMusic();
			this->buttons["MUSIC"]->setText("OFF");
		}
		else {
			this->gameOptions->setMusic();
			this->buttons["MUSIC"]->setText("ON");
		}
	}	
	
	if (this->buttons["RESET_HIGHSCORE"]->isPressedLeft()) {
		ofstream ofs("Data/highScore.txt");
		ofs << 0 << "\n" << 0 << "\n" << 0;
		ofs.close();
	}

}

void OptionsState::update(const float& dt)
{
	this->updateMousePos();
	this->updateInput(dt);

	this->updateButtons();

	//system("cls");
	//std::cout << this->mosePosView.x << " " << this->mosePosView.y << "\n";
}

void OptionsState::renderButtons(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}	
	
	for (auto& it : this->textSet)
	{
		target->draw(*it.second);
	}

}

void OptionsState::render(RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(target);

	//this->gamestate_btn->render(target);
}
