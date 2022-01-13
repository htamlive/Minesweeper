#include "GameOptions.h"

GameOptions::GameOptions()
{
	this->isMusic = true;
	this->isSound = true;
}

GameOptions::~GameOptions()
{
}

bool GameOptions::setSound()
{
	if (this->isSound) return false;
	this->isSound = true;
	return true;
}

bool GameOptions::setMuteSound()
{
	if (!this->isSound) return false;
	this->isSound = false;
	return true;
}

bool GameOptions::setMusic()
{
	if (this->isMusic) return false;
	this->isMusic = true;
	return true;
}

bool GameOptions::setMuteMusic()
{
	if (!this->isMusic) return false;
	this->isMusic = false;
	return true;
}

bool GameOptions::checkSound()
{
	return this->isSound;
}

bool GameOptions::checkMusic()
{
	return this->isMusic;
}
