#include "StatusBar.h"

void StatusBar::initButtons()
{
	int width = 250, height = 80;
	int x = this->shape.getPosition().x + this->shape.getSize().x - width - 20;
	int y = this->shape.getPosition().y + this->shape.getSize().y - height - 10;
	this->buttons["EXIT_STATE"] = new Button(x, y,width, height,this->font, "BACK",
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));
	this->buttons["EXIT_STATE"]->setTextSize(18);
	this->buttons["EXIT_STATE"]->setCenter();

}

void StatusBar::updateCurrentTime(int playTime)
{
	this->playTime.setString("Time: " + std::to_string(playTime) + " s");
	this->playTime.setPosition(Vector2f(this->shape.getPosition().x + (this->shape.getGlobalBounds().width - this->currentFlags.getGlobalBounds().width) / 2 - 40.f,
	this->shape.getPosition().y + (this->shape.getGlobalBounds().height - this->playTime.getGlobalBounds().height) / 2 + 10.f));
}

void StatusBar::updateCurrentFlags(int currentFlags)
{
	this->currentFlags.setString("Flags: " + std::to_string(currentFlags));
}

void StatusBar::updateCurLevel(std::string text)
{
	this->currentLevel.setString(text);
	this->currentLevel.setPosition(Vector2f(20.f + this->shape.getPosition().x + (this->shape.getGlobalBounds().width - this->currentFlags.getGlobalBounds().width) / 2 - 40.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height - this->playTime.getGlobalBounds().height) / 2 - 40.f));
}

StatusBar::StatusBar(float x, float y, float width, float height, Font* font, Color color)
{
	this->shape.setPosition(Vector2f(x, y));
	this->shape.setSize(Vector2f(width, height));
	this->shape.setFillColor(color);

	this->font = font;

	quit = false;

	this->playTime.setFont(*this->font);
	this->playTime.setCharacterSize(40);
	this->currentFlags.setFont(*this->font);
	this->currentFlags.setCharacterSize(40);
	this->currentFlags.setPosition(Vector2f(x, y + (height - this->currentFlags.getGlobalBounds().height) / 2 - 5.f));
	this->currentLevel.setFont(*this->font);
	this->currentLevel.setCharacterSize(20);

	this->initButtons();
}

StatusBar::~StatusBar()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

bool StatusBar::isQuit()
{
	return this->quit;
}

void StatusBar::setTextExitButton(std::string text)
{
	this->buttons["EXIT_STATE"]->setText(text);
	this->buttons["EXIT_STATE"]->setCenter();
}

void StatusBar::updateButtons(Vector2f mousePosView)
{
	for (auto& it : this->buttons)
	{
		it.second->update(mousePosView);
	}

	if (this->buttons["EXIT_STATE"]->isPressedLeft()) {
		this->quit = true;
	}
}

void StatusBar::update(int currentFlags, int playTime, Vector2f mousePosView, std::string mode)
{
	this->updateCurrentFlags(currentFlags);
	this->updateCurrentTime(playTime);
	this->updateButtons(mousePosView);
	this->updateCurLevel(mode);
}

void StatusBar::renderButtons(RenderTarget* target)
{
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void StatusBar::render(RenderTarget* target)
{
	target->draw(this->shape);
	
	target->draw(this->currentFlags);

	target->draw(this->playTime);

	target->draw(this->currentLevel);

	renderButtons(target);
}
