#include "CellController.h"

#include <iostream>

CellController::~CellController()
{
	for (int i = 0; i < this->cells.size(); ++i) {
		for (int j = 0; j < this->cells[0].size(); ++j) {
			delete this->cells[i][j];
		}
	}

	this->cells.clear();
	this->timeOpen.clear();
	this->timeFlag.clear();
	delete this->cellAnimations;
	delete this->gameExec;
	delete this->gameSound;
}

CellController::CellController(int x, int y, int rows, int cols, int mines, float width, float height)
{
	clock.restart();
	this->height = height;
	this->width = width;
	this->mines = this->currentFlags = mines;
	this->cellsLeft = cols * rows - mines;
	
	this->timeOpen.resize(rows, std::vector<float>(cols, -1.f));
	this->timeFlag.resize(rows, std::vector<float>(cols, -1.f));
	this->cells.resize(rows, std::vector<Cell*>(cols));

	this->isOver = false;
	this->isWin = false;

	this->totalTime = 0;
	this->lastPlayTime = 0;
	this->startTime = -1;
	gameExec = new GameExecution(&timeOpen, &timeFlag, this->lastPlayTime, currentFlags, this->cellsLeft);
	//cout << "\ngameExec: " << this->lastPlayTime << " " << currentFlags << " " << this->cellsLeft;


	if (this->gameExec->checkClicked()) {
		this->startTime = 0.1f;
	}


	this->cellAnimations = new CellAnimations(&this->cells, this->gameExec, &this->timeOpen, &this->timeFlag, width, height, &this->isOver, &this->isWin);
	this->gameSound = new GameSounds();

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			this->cells[i][j]->setPosition(x + this->width * j, y + this->height * i);
			if (this->gameExec->checkFlaged(i + 1, j + 1)) {
				this->cells[i][j]->flagCell();
			}else if (this->gameExec->checkOpened(i + 1, j + 1)) {
				this->cellAnimations->setOpenCell(i, j);
				this->cells[i][j]->openCell();
				if (this->gameExec->status(i + 1, j + 1) >= 1) this->cells[i][j]->numCell();

			}
		}
	}


}

CellController::CellController(int x, int y, int rows, int cols, int mines, float width, float height, GameOptions* gameOptions)
{
	this->gameOptions = gameOptions;
	clock.restart();
	this->height = height;
	this->width = width;
	this->mines = this->currentFlags = mines;
	this->cellsLeft = cols * rows - mines;

	this->timeOpen.resize(rows, std::vector<float>(cols, -1.f));
	this->timeFlag.resize(rows, std::vector<float>(cols, -1.f));
	this->cells.resize(rows, std::vector<Cell*>(cols));

	this->isOver = false;
	this->isWin = false;

	this->totalTime = 0;
	this->lastPlayTime = 0;
	this->startTime = -1;
	gameExec = new GameExecution(&timeOpen, &timeFlag, this->lastPlayTime, currentFlags, this->cellsLeft);
	//cout << "\ngameExec: " << this->lastPlayTime << " " << currentFlags << " " << this->cellsLeft;


	if (this->gameExec->checkClicked()) {
		this->startTime = 0.1f;
	}


	this->cellAnimations = new CellAnimations(&this->cells, this->gameExec, &this->timeOpen, &this->timeFlag, width, height, &this->isOver, &this->isWin);
	this->gameSound = new GameSounds(this->gameOptions);

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			this->cells[i][j]->setPosition(x + this->width * j, y + this->height * i);
			if (this->gameExec->checkFlaged(i + 1, j + 1)) {
				this->cells[i][j]->flagCell();
			}
			else if (this->gameExec->checkOpened(i + 1, j + 1)) {
				this->cellAnimations->setOpenCell(i, j);
				this->cells[i][j]->openCell();
				if (this->gameExec->status(i + 1, j + 1) >= 1) this->cells[i][j]->numCell();

			}
		}
	}
}



bool CellController::checkStarted()
{
	return this->startTime > 0;
}

bool CellController::checkWin()
{
	return this->isOver && this->isWin;
}

bool CellController::checkLose()
{
	return this->isOver && !this->isWin;
}

bool CellController::openCell(short row, short col)
{
	//std::cout << "\n" << row << " " << col << " " << this->cells[row][col]->checkOpened();
	if (this->cells[row][col]->checkFlag() || this->cells[row][col]->checkOpened()) {
		return false;
	}

	this->gameExec->askOpen(row + 1, col + 1);
	this->updateOpenCells();
	return true;
}

void CellController::setOpenCellStatus(int row, int col)
{
	if (this->gameExec->status(row + 1, col + 1) == GameExecution::Status::MINE) 
		this->cells[row][col]->bombCell();
	else if (this->gameExec->status(row + 1, col + 1) == GameExecution::Status::EMPTY) 
		this->cells[row][col]->defaultCell();
	else this->cells[row][col]->numCell();
}

void CellController::updateOpenCells()
{
	for (size_t i = 0; i < this->cells.size(); ++i) {
		for (size_t j = 0; j < this->cells[0].size(); ++j) {
			Cell* tmp = this->cells[i][j];
			if (this->gameExec->checkOpened(i + 1, j + 1) && !tmp->checkOpened()) {
				this->gameSound->openSound();
				if (tmp->checkFlag())
					this->flagOrUnflagCell(i, j);

				tmp->openCell();
				this->setOpenCellStatus(i, j);
				this->cellAnimations->setOpenCell(i, j);
				--this->cellsLeft;

				if (tmp->checkBomb()) {
					this->isWin = false;
					this->isOver = true;
					this->gameSound->losingSound();
				}
				else {
					this->timeOpen[i][j] = clock.getElapsedTime().asSeconds() + this->lastPlayTime;
				}
			}
		}
	}
	if (!this->isOver) {
		this->isWin = this->isOver = (this->cellsLeft == 0);
		if(this->isWin) this->gameSound->winningSound();
	}
}

bool CellController::flagOrUnflagCell(short row, short col)
{
	if (!this->cells[row][col]->checkOpened()) {
		if (!this->cells[row][col]->checkFlag()) {
			if (this->currentFlags == 0)
				return false;
			this->gameSound->lockSound();
			--this->currentFlags;
			this->cells[row][col]->flagCell();
			this->gameExec->askFlag(row + 1, col + 1);
		}
		else {
			if (this->mines == this->currentFlags)
				return false;
			this->gameSound->lockSound();
			++this->currentFlags;
			this->cells[row][col]->unFlagCell();
			this->gameExec->askUnFlag(row + 1, col + 1);
		}
			

		this->timeFlag[row][col] = clock.getElapsedTime().asSeconds() + this->lastPlayTime;
		return true;
	}
	return false;
}

void CellController::update(const Vector2f mousePos)
{
	int rows = this->cells.size();
	int cols = this->cells[0].size();
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			this->cells[i][j]->update(mousePos);
			if (!this->isOver) {
				if (this->cells[i][j]->isPressedLeft()) {
					if (this->startTime < 0) {
						this->startTime = this->clock.getElapsedTime().asSeconds();
					}
					this->openCell(i, j);
					this->saveGame();
				}
				if (this->cells[i][j]->isPressedRight()) {
					this->flagOrUnflagCell(i, j);
					this->saveGame();
				}
			}
		}
	}
}

void CellController::render(RenderTarget* target)
{
	this->cellAnimations->render(target, this->clock.getElapsedTime().asSeconds() + this->lastPlayTime);
}

float CellController::getStartTime()
{
	return this->startTime;
}

float CellController::getPlayTime()
{
	//cout << "\nHello this is time: " << this->isOver << this->totalTime << " " << this->lastPlayTime << " " << this->clock.getElapsedTime().asSeconds() << " " << this->getStartTime();
	if (!this->isOver) {
		this -> totalTime = this->lastPlayTime + this->clock.getElapsedTime().asSeconds() - this->getStartTime();
	}
	//cout << "\nTotal Time: " << totalTime;
	if (this->totalTime > 9999) {
		this->totalTime = 9999;
	}
	return this->totalTime < 0.f ? 0.f : this->totalTime;
}

float CellController::get_height()
{
	return this->height;
}

float CellController::get_width()
{
	return this->width;
}

int CellController::getCurrentFlags()
{
	return this->currentFlags;
}

int CellController::updateHighScore()
{
	return this->gameExec->updateHighScore(this->getPlayTime());
}

void CellController::saveGame()
{
	//cout << "\nCellCon: Check started: " << this->checkStarted();
	if(this->checkStarted() && !(this->checkLose()) && !(this->checkWin()))
		this->gameExec->save(&timeOpen, &timeFlag, this->getPlayTime() + 1, this->currentFlags, this->cellsLeft);
	else {
		ofstream ofs("Data/lastPlay.txt");
		ofs << 0; ofs.close();
	}

}
