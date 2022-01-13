#include "Button.h"


void Button::updateByMouse(const Vector2f mousePos)
{
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->buttonState = BTN_HOVER;

		if (Mouse::isButtonPressed(Mouse::Left) && this->clock.getElapsedTime().asSeconds() > this->delay) {
			this->buttonState = BTN_ACTIVE_L;
			clock.restart();
		}

		if (Mouse::isButtonPressed(Mouse::Right) && this->clock.getElapsedTime().asSeconds() > this->delay) {
			this->buttonState = BTN_ACTIVE_R;
			clock.restart();
		}
	}
	else this->buttonState = BTN_IDLE;
}

void Button::updateType()
{
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_ACTIVE_L:
		this->shape.setFillColor(this->activeColor);
		break;
	case BTN_ACTIVE_R:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(Color::Red);
		break;
	}
}

Button::Button(float x, float y, float width, float height, Font* font, std::string text, Color idleColor, Color hoverColor, Color activeColor)
{
	this->clock.restart();
	this->delay = .25f;

	this->buttonState = BTN_IDLE;

	this->shape.setPosition(Vector2f(x, y));
	this->shape.setSize(Vector2f(width, height));
	this->texture = new Texture();

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(16);
	this->setCenter();

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
}

void Button::setTextSize(int size)
{
	this->text.setCharacterSize(size);
}

void Button::setCenter()
{
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width - this->text.getGlobalBounds().width) / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height - this->text.getGlobalBounds().height) / 2.f
	);
}

bool Button::setTexture(std::string filePath) {
	bool isSuccess = this->texture->loadFromFile(filePath);
	if(isSuccess)
		this->shape.setTexture(this->texture);
	return isSuccess;
}

bool Button::isPressedLeft()
{
	if (this->buttonState == BTN_ACTIVE_L) {
		this->buttonState == BTN_HOVER;
		return true;
	}
	return false;
}

bool Button::isPressedRight()
{
	if (this->buttonState == BTN_ACTIVE_R) {
		this->buttonState == BTN_HOVER;
		return true;
	}
	return false;
}

void Button::setText(std::string text) {
	this->text.setString(text);
}

void Button::setPosition(Vector2f pos)
{
	this->shape.setPosition(pos);
}

std::string Button::getText(){
	return this->text.getString();
}

void Button::update(const Vector2f mousePos)
{
	updateByMouse(mousePos);
	updateType();
}

void Button::render(RenderTarget* target)
{
	target->draw(this->shape);

	target->draw(this->text);
}
