#pragma once
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"

using namespace sf;

enum button_states{BTN_IDLE = 0, BTN_HOVER = 1, BTN_ACTIVE_L = 2, BTN_ACTIVE_R = 3 };
class Button
{
private:
	void updateByMouse(const Vector2f mousePos);
	void updateType();

protected:
	short unsigned buttonState;

	RectangleShape shape;
	Texture* texture;
	Font* font;
	Text text;
	Clock clock;
	float delay;


	Color idleColor;
	Color hoverColor;
	Color activeColor;


public:
	Button(float x, float y, float width, float height, Font* font, std::string text, Color idleColor, Color hoverColor, Color activeColor);
	~Button();

	bool isPressedLeft();
	bool isPressedRight();
	void setTextSize(int size);
	void setCenter();
	bool setTexture(std::string filePath);
	void setText(std::string text);
	void setPosition(Vector2f pos);

	std::string getText();

	void update(const Vector2f mousePos);
	void render(RenderTarget* target);
};

