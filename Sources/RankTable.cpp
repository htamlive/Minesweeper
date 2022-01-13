#include "RankTable.h"
#include <sstream>
#include <cstdio>

RankTable::RankTable(std::map<std::string, Numbox*>* numboxes, Font *font)
{
	this->numboxes = numboxes;
	(*this->numboxes)["SCORE_EASY"] = new Numbox(30, 100, 40, Color(15, 255, 80), Color(0, 0, 0, 0));
	this->numboxes->at("SCORE_EASY")->setFont(*font);
	this->numboxes->at("SCORE_EASY")->setPosition(Vector2f(210.f, 315.f));
	this->numboxes->at("SCORE_EASY")->lockBox();

	(*this->numboxes)["SCORE_MEDIUM"] = new Numbox(30, 100, 40, Color(204, 48, 255), Color(0, 0, 0, 0));
	this->numboxes->at("SCORE_MEDIUM")->setFont(*font);
	this->numboxes->at("SCORE_MEDIUM")->setPosition(Vector2f(210.f, 378.f));
	this->numboxes->at("SCORE_MEDIUM")->lockBox();

	(*this->numboxes)["SCORE_HARD"] = new Numbox(30, 100, 40, Color(254,27,23), Color(0, 0, 0, 0));
	this->numboxes->at("SCORE_HARD")->setFont(*font);
	this->numboxes->at("SCORE_HARD")->setPosition(Vector2f(210.f, 445.f));
	this->numboxes->at("SCORE_HARD")->lockBox();

	this->updateData();
}

RankTable::~RankTable()
{
}

void RankTable::updateData()
{
	std::ifstream ifs("Data/highScore.txt");
	int dummy;
	ifs >> dummy;
	this->numboxes->at("SCORE_EASY")->setInitText(std::to_string(dummy) + " pt" + ((dummy == 1) ? "" : "s"));
	ifs >> dummy;
	this->numboxes->at("SCORE_MEDIUM")->setInitText(std::to_string(dummy) + " pt" + ((dummy == 1) ? "" : "s"));
	ifs >> dummy;
	this->numboxes->at("SCORE_HARD")->setInitText(std::to_string(dummy) + " pt" + ((dummy == 1) ? "" : "s"));

}
