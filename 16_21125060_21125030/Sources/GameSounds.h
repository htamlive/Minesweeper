#pragma once
#include "SFML/Audio.hpp"
#include "GameOptions.h"

using namespace sf;

class GameSounds
{
private:
	SoundBuffer lostBuffer;
	SoundBuffer winBuffer;
	SoundBuffer openCellBuffer;
	SoundBuffer lockBuffer;
	Sound sound;
	GameOptions* gameOptions;
	void initSound();
public:
	GameSounds();
	GameSounds(GameOptions* gameOptions);
	virtual ~GameSounds();
	void openSound();
	void winningSound();
	void losingSound();
	void lockSound();
};

