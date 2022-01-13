#include "Cell.h"

#include <iostream>
Cell::Cell(float x, float y, float width, float height,
	Font* font, std::string text, Color idleColor, Color hoverColor, Color activeColor) :
	Button(x, y, width, height, font, text, idleColor, hoverColor, activeColor)
{
	this->cellType = C_NULL;
	this->isOpened = false;
	this->isFlaged = false;
}

void Cell::setPosition(const float x, const float y)
{
	this->shape.setPosition(Vector2f(x, y));
}

void Cell::setSize(Vector2f size) {
	this->shape.setSize(size);
}


void Cell::updateState(const int state)
{
	this->cellType = state;
}

short Cell::getState()
{
	return this->cellType;
}

float Cell::get_x()
{
	return this->shape.getPosition().x;
}

float Cell::get_y()
{
	return this->shape.getPosition().y;
}

float Cell::get_height()
{
	return this->shape.getGlobalBounds().height;
}

float Cell::get_width()
{
	return this->shape.getGlobalBounds().width;
}

RectangleShape Cell::getCellObject()
{
	return shape;
}


bool Cell::checkOpened()
{
	return this->isOpened;
}

bool Cell::checkNum()
{
	return this->cellType == C_NUM;
}

bool Cell::checkBomb()
{
	return this->cellType == C_BOMB;
}

bool Cell::checkNull()
{
	return this->cellType == C_NULL;
}

bool Cell::checkFlag()
{
	return this->isFlaged;
}


bool Cell::closeCell()
{
	if (this->checkOpened()) {
		this->isOpened = false;
		return true;
	}
	return false;
}

bool Cell::openCell()
{
	if (!this->checkOpened()) {
		this->isOpened = true;
		return true;
	}
	return false;
}

bool Cell::flagCell()
{
	if (!this->isFlaged) {
		this->isFlaged = true;;
		return true;
	}
	return false;
}

bool Cell::unFlagCell()
{
	if (this->isFlaged) {
		this->isFlaged = false;
		return true;
	}
	return false;
}


bool Cell::bombCell()
{
	if (!(this->cellType == C_BOMB)) {
		this->cellType = C_BOMB;
		
		return true;
	}
	return false;
}

bool Cell::numCell()
{
	if (!(this->cellType == C_NUM)) {
		this->cellType = C_NUM;
		return true;
	}
	return false;
}

bool Cell::defaultCell()
{
	if (!(this->cellType == C_NULL)) {
		this->cellType = C_NULL;
		return true;
	}
	return false;
}

void Cell::copyColor(Cell* target)
{
	this->idleColor = target->idleColor;
	this->hoverColor = target->hoverColor;
	this->activeColor = target->activeColor;
}



