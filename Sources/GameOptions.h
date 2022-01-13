#pragma once
class GameOptions
{
private:
	bool isSound, isMusic;
public:
	GameOptions();
	virtual ~GameOptions();
	bool setSound();
	bool setMuteSound();
	bool setMusic();
	bool setMuteMusic();
	bool checkSound();
	bool checkMusic();
};

