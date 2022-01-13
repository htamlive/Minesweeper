#include <chrono>
#include <random>

#include "Game.h"
#include "Constant.h"
#include <vector>


void Game::initVariables()
{
	this->window = nullptr;
	this->dt = 0.f;
	this->fullscreen = false;
	this->gameOptions = new GameOptions();
	music.setLoop(true);
	music.openFromFile("Resources/Sounds/y2mate.com-William-Benckert-Fair-N-Square_1080p.wav");
	this->music.setVolume(20);
	this->music.play();
}

void Game::initWindow()
{

	this->videoModes = VideoMode::getFullscreenModes();

	this->videoMode.height = 750;
	this->videoMode.width = 1000;
	unsigned antialiasing_level = 0;

	this->fullscreen = false;
	this->windowSettings.antialiasingLevel = antialiasing_level;
	if (this->fullscreen) {
		this->window = new RenderWindow(this->videoMode, "Minesweeper", Style::Fullscreen, windowSettings);
	}
	else {
		
		
		std::string name;
		//name += "                                               ";
		//name += "                                                                 ";
		name += "Minesweeper";
		this->window = new RenderWindow(this->videoMode, "Minesweeper", Style::Titlebar | Style::Close, windowSettings);
		Image icon;
		icon.loadFromFile("Resources/icons/ico.png");
		this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		//this->window = new RenderWindow(this->videoMode, name, Style::Titlebar, windowSettings);
		//this->window = new RenderWindow(this->videoMode, "Minesweeper",Style::None, windowSettings);

	}
	this->window->setFramerateLimit(120);
	this->window->setVerticalSyncEnabled(false);

	
}

void Game::initState()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states, gameOptions));
}

void Game::initKeys()
{
	this->supportedKeys.emplace("Escape", Keyboard::Key::Escape);
	this->supportedKeys.emplace("A", Keyboard::Key::A);
	this->supportedKeys.emplace("W", Keyboard::Key::W);
	this->supportedKeys.emplace("D", Keyboard::Key::D);
	this->supportedKeys.emplace("S", Keyboard::Key::S);
}


Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initKeys();
	this->initState();
}

Game::~Game() {
	delete this->window;

	while(!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::updateEvents()
{
	switch (this->ev.type)
	{
	case Event::Closed:
		closeWindow();
		break;
	case Event::KeyReleased:
		keyReleasedProc();
		break;
	case Event::MouseButtonReleased:
		mouseProc();
	}
}

void Game::endApplication()
{
	//std::cout << "Ending application!\n";
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();

	//system("cls");
	//std::cout << this->dt << "\n";
}

void Game::updateMusic()
{
	if (this->gameOptions->checkMusic()) {
		this->music.setVolume(20);
		//this->music.setLoop(true); this->music.play();
	}
	else if (!this->gameOptions->checkMusic()) {
		this->music.setVolume(0);
		//this->music.setLoop(false); this->music.stop();
	}
}

void Game::updateSFMLEvents()
{
	if (!this->states.empty()) {
		while (this->window->pollEvent(this->states.top()->ev)) this->states.top()->updateEvents();
	}
	else {
		while (this->window->pollEvent(this->ev)) this->updateEvents();
	}
}

void Game::update()
{
	
	this->updateSFMLEvents();

	this->updateMusic();
	
	if (!this->states.empty()) {
		this->states.top()->update(this->dt);
		if (this->states.top()->getQuit()) {
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();

		}
	}
	else {
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();
	if (!this->states.empty()) {
		this->states.top()->render();
	}
	this->window->display();
}

void Game::run()
{
	while (this->running())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}


void Game::closeWindow()
{
	this->window->close();
}

void Game::keyReleasedProc()
{
	switch (ev.key.code)
	{
	case Keyboard::Enter:
		//field.restart();

	case Keyboard::Escape:
		this->window->close();
	}
}

void Game::mouseProc()
{
	switch (this->ev.mouseButton.button)
	{
	case Mouse::Left:
		std::cout << "\nLeft click " << Mouse::getPosition(*this->window).x << " " << Mouse::getPosition(*this->window).y;
		//field.open_cell(mouse_cell_x, mouse_cell_y);

		break;
	case sf::Mouse::Right:
		std::cout << "\nRight click";
		//field.flag_cell(mouse_cell_x, mouse_cell_y);
	}
}

