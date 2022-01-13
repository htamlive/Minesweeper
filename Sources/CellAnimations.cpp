#include "CellAnimations.h"

#include <iostream>

void CellAnimations::initModel()
{
	//255, 72, 0
	this->revealedModel2 = new Cell(0.f, 0.f, this->width, this->height, nullptr, "",
		Color(52, 190, 130), Color(52, 190, 130), Color(52, 190, 130));

	//47, 221, 146
	this->revealedModel1 = new Cell(0.f, 0.f, this->width, this->height, nullptr, "",
		Color(47, 221, 146), Color(47, 221, 146), Color(47, 221, 146));

	//Color(9, 139, 213, 255), Color(55, 169, 231, 255), Color(42, 180, 245, 255)
	this->model1 = new Cell(0.f, 0.f, this->width, this->height, nullptr, "",
		Color(85, 85, 85, 255), Color(169, 169, 169, 255), Color(169, 169, 169, 255));

	//Color(0, 40, 193, 255), Color(19, 73, 217, 255), Color(1, 94, 247, 255)
	this->model2 = new Cell(0.f, 0.f, this->width, this->height, nullptr, "",
		Color(24, 23, 22, 255), Color(57, 52, 51, 255), Color(87, 80, 77, 255));	
	
	this->lockModel = new Cell(0.f, 0.f, this->width/2, this->height/2, nullptr, "",
		Color(255,255, 255, 255), Color(55, 169, 231, 0), Color(42, 180, 245, 0));
	
	this->blackModel = new Cell(0.f, 0.f, this->width, this->height, nullptr, "",
		Color(0,0, 0), Color(0, 0, 0), Color(0, 0, 0));

	std::cout << this->lockModel->setTexture("Resources/Images/lock.png");
	
	this->bombModel = new Cell(0.f, 0.f, this->width, this->height, nullptr, "",
		Color(160,32, 240, 255), Color(160, 32, 240, 255), Color(160, 32, 240, 255));

	this->numsTexture.resize(8);
	for (int i = 0; i < 8; ++i) {
		this->numsTexture[i].loadFromFile("Resources/Images/Numbers/Num" + std::to_string(i + 1)+".png");
	}

}

CellAnimations::CellAnimations(std::vector<std::vector<Cell*>>* cells,
		std::vector<std::vector<float>>* timeOpen, std::vector<std::vector<float>>* timeFlag,
		float width, float height, bool *isOver, bool *isWin)
{
	this->isOver = isOver;
	this->isWin = isWin;
	this->cells = cells;
	this->timeOpen = timeOpen;
	this->timeFlag = timeFlag;
	this->width = width;
	this->height = height;

	this->initModel();

	for (size_t i = 0; i < (*this->cells).size(); ++i) {
		for (size_t j = 0; j < (*this->cells)[0].size(); ++j) {
			if ((i + j) & 1) (*this->cells)[i][j] = new Cell(*this->model2);
			else (*this->cells)[i][j] = new Cell(*this->model1);
		}
	}
}

CellAnimations::CellAnimations(std::vector<std::vector<Cell*>>* cells, GameExecution* gameExec,
	std::vector<std::vector<float>>* timeOpen, std::vector<std::vector<float>>* timeFlag,
	float width, float height, bool* isOver, bool* isWin)
{
	this->isOver = isOver;
	this->isWin = isWin;
	this->cells = cells;
	this->gameExec = gameExec;
	this->timeOpen = timeOpen;
	this->timeFlag = timeFlag;
	this->width = width;
	this->height = height;

	this->initModel();

	for (size_t i = 0; i < (*this->cells).size(); ++i) {
		for (size_t j = 0; j < (*this->cells)[0].size(); ++j) {
			if ((i + j) & 1) (*this->cells)[i][j] = new Cell(*this->model2);
			else (*this->cells)[i][j] = new Cell(*this->model1);
		}
	}
}

CellAnimations::CellAnimations(std::vector<std::vector<Cell*>>* cells, std::vector<std::vector<int>>* test,
	std::vector<std::vector<float>>* timeOpen, std::vector<std::vector<float>>* timeFlag, float width, float height, bool* isOver, bool* isWin)
{
	this->isOver = isOver;
	this->isWin = isWin;
	this->cells = cells;
	this->test = test;

	this->timeOpen = timeOpen;
	this->timeFlag = timeFlag;
	this->width = width;
	this->height = height;

	this->initModel();

	for (size_t i = 0; i < (*this->cells).size(); ++i) {
		for (size_t j = 0; j < (*this->cells)[0].size(); ++j) {
			if ((i + j) & 1) (*this->cells)[i][j] = new Cell(*this->model2);
			else (*this->cells)[i][j] = new Cell(*this->model1);
		}
	}


}


void CellAnimations::openCellAnimation(short row, short col, RenderTarget* target, float seconds)
{
	if ((*this->timeOpen)[row][col] > 0 && (seconds - (*this->timeOpen)[row][col]) <= OPEN_DURATION) {
		float ratio = 1 - (seconds - (*this->timeOpen)[row][col]) / OPEN_DURATION;
		Cell* tmp;

		if ((row + col) & 1)
			tmp = new Cell(*this->model2);
		else
			tmp = new Cell(*this->model1);

		tmp->setSize(Vector2f(this->width * ratio, this->height * ratio));
		tmp->setPosition((*this->cells)[row][col]->get_x() + this->width * (1 - ratio) / 2, (*this->cells)[row][col]->get_y() + this->height * (1 - ratio) / 2);
		tmp->render(target);
	}
}

void CellAnimations::setOpenCell(int row, int col)
{
	if ((row + col) & 1)
		(*this->cells)[row][col]->copyColor(this->revealedModel2);
	else
		(*this->cells)[row][col]->copyColor(this->revealedModel1);
}

void CellAnimations::winningAnimation(int row, int col, RenderTarget* target, float seconds)
{
	if (this->checkIsWin() && (((int)(2*seconds)) & 1) && ((*this->cells)[row][col]->checkOpened())) {
		Cell* tmp = this->blackModel;
		tmp->setPosition((*this->cells)[row][col]->get_x() , (*this->cells)[row][col]->get_y());
		tmp->render(target);
		if ((row + col) & 1) {
			tmp = this->revealedModel1;
		}
		else {
			tmp = this->revealedModel2;
		}
		tmp->setPosition((*this->cells)[row][col]->get_x() ,(*this->cells)[row][col]->get_y());
		tmp->render(target);
	}
}

void CellAnimations::flagCellAnimation(short row, short col, RenderTarget* target, float seconds)
{
	if ((*this->timeFlag)[row][col] > 0) {
		float ratio = (seconds - (*this->timeFlag)[row][col]) < FLAG_DURATION ? (seconds - (*this->timeFlag)[row][col]) / FLAG_DURATION : 1;
		if ((*this->cells)[row][col]->checkFlag()) {
			Cell* tmp = this->lockModel;
			tmp->setSize(Vector2f(this->width/2, this->height/2));
			tmp->setPosition((*this->cells)[row][col]->get_x()*(1 + ratio)/2 + (this->width - tmp->get_width()) / 2, (*this->cells)[row][col]->get_y() * (1 + ratio) / 2 + (this->height - tmp->get_height()) / 2 + (ratio - 1));
			tmp->render(target);
		}	else {
			ratio = 1 - ratio;
			Cell* tmp = this->lockModel;
			tmp->setSize(Vector2f(this->width * ratio, this->height * ratio));
			tmp->setPosition((*this->cells)[row][col]->get_x() + this->width * (1 - ratio) / 2,
				(*this->cells)[row][col]->get_y() + this->height * (1 - ratio) / 2);
			tmp->render(target);
		}
	}
}

void CellAnimations::setFlagCell(int row, int col, float seconds)
{

}

void CellAnimations::bombAnimation(int row, int col)
{
	//std::cout << "\nIt's over?" << *this->isOver;
	if (this->checkIsLose() && (*this->cells)[row][col]->checkBomb()) {
		//std::cout << "\nHell\n";
		(*this->cells)[row][col]->copyColor(this->bombModel);
	}
}

void CellAnimations::showNumber(int row, int col, RenderTarget* target)
{
	if ((*this->cells)[row][col]->checkOpened() && (*this->cells)[row][col]->checkNum()) {
		RectangleShape rec;
		if ((*this->gameExec).status(row + 1, col + 1) - 1 < 0) {
			//std::cout << "\n" << (*this->gameExec).status(row + 1, col + 1) - 1;
			return;
		}
		rec.setTexture(&this->numsTexture[(*this->gameExec).status(row + 1, col + 1) - 1]);
		float ratio = 0.6;
		rec.setSize(Vector2f((*this->cells)[row][col]->get_width()*ratio, (*this->cells)[row][col]->get_height()*ratio));

		rec.setPosition((*this->cells)[row][col]->get_x() + ((*this->cells)[row][col]->get_width() - rec.getSize().x) / 2,
			(*this->cells)[row][col]->get_y() + ((*this->cells)[row][col]->get_height() - rec.getSize().y) / 2);

		target->draw(rec);
	}
}

void CellAnimations::render(RenderTarget* target, float seconds)
{
	int rows = (* this->cells).size();
	int cols = (* this->cells)[0].size();

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			(*this->cells)[i][j]->render(target);
			this->openCellAnimation(i, j, target, seconds);
			this->bombAnimation(i, j);
			this->winningAnimation(i, j, target, seconds);
			this->showNumber(i, j, target);
			this->flagCellAnimation(i, j, target, seconds);

		}
	}

	/*
		RectangleShape rec;
	rec.setTexture(&this->numsTexture[1]);
	rec.setSize(Vector2f(50.f, 50.f));
	target->draw(rec);
	*/

}

bool CellAnimations::checkIsOver()
{
	return *this->isOver;
}

bool CellAnimations::checkIsWin()
{
	return (* this->isOver) && (*this->isWin);
}

bool CellAnimations::checkIsLose()
{
	return (*this->isOver) && !(*this->isWin);
}

CellAnimations::~CellAnimations()
{

	delete this->revealedModel1;
	delete this->revealedModel2;
	delete this->model1;
	delete this->model2;

	delete this->bombModel;
	delete this->lockModel;
}
