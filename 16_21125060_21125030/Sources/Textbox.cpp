#include "Textbox.h"

void Textbox::initVariables()
{
	this->isSelected = false;
	this->hasLimit = false;
	this->limit = 0;
	this->isLock = false;
}

void Textbox::inputLogic(int charTyped)
{
	if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
		text << static_cast<char>(charTyped);
	}
	else if (charTyped == DELETE_KEY) {
		if (text.str().length() > 0) {
			deleteLastChar();
		}
	}
	textValue.setString(text.str() + "|");
}

void Textbox::deleteLastChar()
{
	std::string t = text.str();
	std::string newT = "";
	for (int i = 0; i < t.length() - 1; ++i) {
		newT += t[i];
	}
	text.str("");
	text << newT;

	textValue.setString(text.str());
}

Textbox::Textbox()
{
	this->initVariables();
}

Textbox::Textbox(int fontSize, float boxWidth, float boxHeight, Color textColor, Color bgColor)
{
	this->initVariables();
	this->textValue.setCharacterSize(fontSize);
	this->textValue.setFillColor(textColor);
	this->shape.setFillColor(bgColor);
	this->shape.setSize(Vector2f(boxWidth, boxHeight));

}

void Textbox::lockBox()
{
	this->isLock = true;
}

void Textbox::setFont(Font& font)
{
	textValue.setFont(font);
}

void Textbox::setPosition(Vector2f pos)
{
	this->shape.setPosition(pos);
	this->textValue.setPosition(Vector2f(pos.x + 5.f, pos.y + 2.f));
}



void Textbox::setLimt(bool ToF)
{
	this->hasLimit = ToF;
}

void Textbox::setLimit(bool ToF, int lim)
{
	this->hasLimit = ToF;
	this->limit = lim - 1;

}

void Textbox::setInitText(std::string s)
{
	this->textValue.setString(s);
	this->text.str(s);
}

void Textbox::setSelected(bool sel)
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
	this->textValue.setString(newT);
}

std::string Textbox::getText()
{
	return text.str();
}

void Textbox::render(RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->textValue);
}

bool Textbox::updateByMouse(const Vector2f mousePos)
{
	if (this->shape.getGlobalBounds().contains(mousePos) && !this->isLock) {
		if (Mouse::isButtonPressed(Mouse::Left))
			this->setSelected(true);
	}
	else {
		this->setSelected(false);
	}
	return false;
}

void Textbox::update(Event input)
{
	if (this->isSelected && !this->isLock) {
		int charTyped = input.text.unicode;
		if (charTyped < 128) {
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
