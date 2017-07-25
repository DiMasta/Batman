#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <climits>
#include <ctime>

#define M_PI 3.14159265358979323846

using namespace std;

const int DISPLAY_INPUT = 1;
const int USE_HARDCODED_INPUT = 0;

const int INVALID_COORD = -1;

enum Direction {
	U = 0,
	UR,
	R,
	DR,
	D,
	DL,
	L,
	UL,
};

class Game {
public:
	Game();
	~Game();

	void initGame();
	void gameLoop();
	void getGameInput();
	void getTurnInput();
	void turnBegin();
	void makeTurn();
	void turnEnd();
	void play();

	void debug() const;

private:
	int width;
	int height;
	int jumpsLeft;
	int xCoord;
	int yCoord;
	int minX;
	int maxX;
	int minY;
	int maxY;
	string bombDirection;

	int turnsCount;
};

//*************************************************************************************************************
//*************************************************************************************************************

Game::Game() : turnsCount(0) {
}

//*************************************************************************************************************
//*************************************************************************************************************

Game::~Game() {
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::initGame() {
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::gameLoop() {
	while (true) {
		getTurnInput();
		turnBegin();
		makeTurn();
		turnEnd();
	}
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::getGameInput() {
	if (USE_HARDCODED_INPUT) {
		width = 1;
		height = 80;
		jumpsLeft = 6;
		xCoord = 0;
		yCoord = 20;
	}
	else {
		cin >> width >> height >> jumpsLeft >> xCoord >> yCoord;

		minX = 0;
		maxX = width;
		minY = 0;
		maxY = height;
	}

	if (DISPLAY_INPUT) {
		cerr << width << " " << height << endl;
		cerr << jumpsLeft << endl;
		cerr << xCoord << " " << yCoord << endl;
	}
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::getTurnInput() {
	if (USE_HARDCODED_INPUT) {
		bombDirection = "D";
	}
	else {
		cin >> bombDirection;
	}

	if (DISPLAY_INPUT) {
		cerr << "Min X: " << minX << " Max X: " << maxX << endl;
		cerr << "Min Y: " << minY << " Max Y: " << maxY << endl;
		cerr << xCoord << " " << yCoord << endl;
		cerr << bombDirection << endl;
	}
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::turnBegin() {
	int tempX = xCoord;
	int tempY = yCoord;

	if (bombDirection.find('U') != string::npos) {
		yCoord -= (yCoord - minY) / 2;
		maxY = tempY;
	}

	if (bombDirection.find('D') != string::npos) {
		yCoord += (maxY - yCoord) / 2;
		minY = tempY;
	}

	if (bombDirection.find('L') != string::npos) {
		xCoord -= (xCoord - minX) / 2;
		maxX = tempX;
	}

	if (bombDirection.find('R') != string::npos) {
		xCoord += (maxX - xCoord) / 2;
		minX = tempX;
	}
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::makeTurn() {
	cout << xCoord << " " << yCoord << endl;
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::turnEnd() {
	++turnsCount;
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::play() {
	initGame();
	getGameInput();
	gameLoop();
}

//*************************************************************************************************************
//*************************************************************************************************************

void Game::debug() const {
}

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

#ifdef TESTS
#include "debug.h"
#endif // TESTS

int main(int argc, char** argv) {
#ifdef TESTS
	doctest::Context context;
	int res = context.run();
#else
	Game game;
	game.play();
#endif // TESTS

	return 0;
}