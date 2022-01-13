#include "GameSounds.h"

void GameSounds::initSound()
{
	this->lostBuffer.loadFromFile("Resources/Sounds/Sad-trumpet-sound.wav");
	this->winBuffer.loadFromFile("Resources/Sounds/Sound effect-Win.wav");
	this->openCellBuffer.loadFromFile("Resources/Sounds/Suction Pop sound effects pack_01.wav");
	this->lockBuffer.loadFromFile("Resources/Sounds/mixkit-gaming-lock-2848.wav");


	if (this->gameOptions->checkSound()) this->sound.setVolume(80);
	else this->sound.setVolume(0);
}

GameSounds::GameSounds()
{
	this->initSound();
}

GameSounds::GameSounds(GameOptions* gameOptions)
{
	this->gameOptions = gameOptions;
	initSound();
}

GameSounds::~GameSounds()
{

}

void GameSounds::openSound()
{
	this->sound.setBuffer(this->openCellBuffer);
	sound.play();
}

void GameSounds::winningSound()
{
	this->sound.setBuffer(this->winBuffer);
	sound.play();
}

void GameSounds::losingSound()
{
	this->sound.setBuffer(this->lostBuffer);
	sound.play();
}

void GameSounds::lockSound()
{
	this->sound.setBuffer(this->lockBuffer);
	sound.play();
}
