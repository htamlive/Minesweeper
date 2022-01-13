#pragma once
#include "Numbox.h"
#include <fstream>

class RankTable
{
private:
	std::map<std::string, Numbox*> *numboxes;
public:
	RankTable(std::map<std::string, Numbox*> *numboxes, Font* font);
	virtual ~RankTable();

	void updateData();
};

