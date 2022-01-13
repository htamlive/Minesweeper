#include "Numbox.h"

void Numbox::initVariables()
{
	this->isSelected = false;
	this->hasLimit = false;
	this->limit = 0;
	this->isLock = false;
}

void Numbox::inputLogic(int charTyped)
{
	if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
		text << static_cast<char>(charTyped);
	}
	else if (charTyped == DELETE_KEY) {
		if (text.str().length() > 0) {
			deleteLastChar();
		}
	}
	numValue.setString(text.str() + "|");
}

void Numbox::deleteLastChar()
{
	std::string t = text.str();
	std::string newT = "";
	for (int i = 0; i < t.length() - 1; ++i) {
		newT += t[i];
	}
	text.str("");
	text << newT;

	numValue.setString(text.str());
}

Numbox::Numbox()
{
	this->initVariables();
}

Numbox::Numbox(int fontSize, float boxWidth, float boxHeight, Color textColor, Color bgColor)
{
	this->initVariables();
	this->numValue.setCharacterSize(fontSize);
	this->numValue.setFillColor(textColor);
	this->shape.setFillColor(bgColor);
	this->shape.setSize(Vector2f(boxWidth, boxHeight));

}

void Numbox::lockBox()
{
	this->isLock = true;
}

void Numbox::setFont(Font& font)
{
	numValue.setFont(font);
}

void Numbox::setPosition(Vector2f pos)
{
	this->shape.setPosition(pos);
	this->numValue.setPosition(Vector2f(pos.x + 5.f, pos.y + 2.f));
}



void Numbox::setLimt(bool ToF)
{
	this->hasLimit = ToF;
}

void Numbox::setLimit(bool ToF, int lim)
{
	this->hasLimit = ToF;
	this->limit = lim - 1;

}

void Numbox::setInitText(std::string s)
{
	this->numValue.setString(s);
	this->text.str(s);
}

void Numbox::setSelected(bool sel)
{
	this->isSelected = sel;
	std::string t = text.str();
	std::string newT = "";
	for (size_t i = 0; i < t.length(); ++i) {
		newT += t[i];
	}
	if (sel) {
		newT += "|";
	}
	this->numValue.setString(newT);
}

std::string Numbox::getText()
{
	return text.str();
}

void Numbox::render(RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->numValue);
}

bool Numbox::updateByMouse(const Vector2f mousePos)
{
	if (this->shape.getGlobalBounds().contains(mousePos) && !this->isLock) {
		if(Mouse::isButtonPressed(Mouse::Left))
			this->setSelected(true);
	}
	else {
		this->setSelected(false);
	}
	return false;
}

void Numbox::update(Event input)
{
	if (this->isSelected && !this->isLock) {
		int charTyped = input.text.unicode;
		if (charTyped == 8 || (47 < charTyped && charTyped < 58)) {
			if (this->hasLimit) {
				if (this->text.str().length() <= limit) {
					this->inputLogic(charTyped);
				}
				else if (this->text.str().length() > this->limit && charTyped == DELETE_KEY) {
					this->deleteLastChar();
				}
			}
		}
	}
}
