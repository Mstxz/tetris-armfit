#include "TetrisGame.hpp"
#include "Shape.hpp"
#include "ShapeFactory.hpp"
#include <LedControl.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <ctime>

extern LedControl lc;

TetrisGame::TetrisGame()
{
	std::memset(board, 0, sizeof(board));
	curShape = nullptr;
	moveSpeed = 200;
	lastUpdate = millis();
	ShapeFactory::init();
	restartGame();
}

TetrisGame::~TetrisGame()
{
	if (curShape)
		delete curShape;
}

// Restart the game
void TetrisGame::restartGame()
{
	std::memset(board, 0, sizeof(board));

	if (curShape)
	{
		delete curShape;
		curShape = nullptr;
	}

	// Create a new random shape
	curShape = ShapeFactory::createShape();
}

// Handle key events (left, right, rotate, down)
int TetrisGame::KeyEvent(t_event event)
{
	Shape	*tmp;

	if (!curShape) return -1;
	switch (event)
	{
		case MOVE_LEFT:
			curShape->moveLeft(board);
			break;
		case MOVE_RIGHT:
			curShape->moveRight(board);
			break;
		case MOVE_DOWNWARD:
			curShape->moveDown(board);
			break;
		case ROTATE_LEFT:
			tmp = curShape->clone();
			tmp->rotateLeft();
			if (!tmp->checkCollision(board, tmp->getX(), tmp->getY(), tmp->bitmap))
				curShape->rotateLeft();
			delete tmp;
			break;
		case ROTATE_RIGHT:
			tmp = curShape->clone();
			tmp->rotateRight();
			if (!tmp->checkCollision(board, tmp->getX(), tmp->getY(), tmp->bitmap))
				curShape->rotateRight();
			delete tmp;
			break;
		default: break;
	}
	return 0;
}

// Game update: move shape down automatically, lock when it collides
void TetrisGame::updateGame()
{
	unsigned long	currentTime = millis();

	if (!curShape) return;

	if (currentTime - lastUpdate >= moveSpeed)
	{
		if (!curShape->checkCollision(board, curShape->posX, curShape->posY + 1, curShape->bitmap))
		{
			curShape->posY++;
		}
		else
		{
			// Lock shape to board
			curShape->draw(board);

			// clear full lines
			clearFullLines();

			// Spawn new shape
			delete curShape;
			curShape = ShapeFactory::createShape();
	
			if (curShape->checkCollision(board, curShape->getX(), curShape->getY(), curShape->bitmap)) {
				restartGame(); // Game over - restart
			}
		}
		this->lastUpdate = currentTime;
	}
}

void TetrisGame::clearFullLines() {
	bool fullLine;
	int linesCleared = 0;
		
	// Check from bottom up
	for (int y = 31; y >= 0; y--) {
		fullLine = true;
		// Check if entire row is filled
		for (int x = 0; x < 8; x++) {
			if (!board[y][x]) {
				fullLine = false;
				break;
			}
		}
		
		if (fullLine) {
			linesCleared++;
			// Shift all lines above down
			for (int shiftY = y; shiftY > 0; shiftY--) {
				for (int x = 0; x < 8; x++) {
					board[shiftY][x] = board[shiftY - 1][x];
				}
			}
			// Clear top row
			for (int x = 0; x < 8; x++) {
				board[0][x] = false;
			}
			// Check same row again (might have new full line)
			y++; // Don't skip checking this row
		}
	}
		
	// Adjust speed based on lines cleared
	if (linesCleared > 0) {
		moveSpeed = max(50, moveSpeed - linesCleared * 25);
	}
}

void TetrisGame::render()
{
	// Make a temporary copy of the board
	bool tempBoard[32][8];
	std::memcpy(tempBoard, board, sizeof(board));

	// Draw current falling shape on top
	if (curShape)
		curShape->draw(tempBoard);

	// Send the combined board to the actual display
	display(tempBoard);
}

// Example display function (to be implemented for your hardware)
void TetrisGame::display(bool (*board)[8])
{
	for (int dev = 0; dev < 4; dev++) {
		int realDev = 3 - dev;
		for (int row = 0; row < 8; row++) {
			byte colData = 0;
			for (int col = 0; col < 8; col++) {
				int boardX = row;
				int boardY = dev * 8 + col;
				if (boardY < 32 && board[boardY][boardX])
					colData |= (1 << (7 - col));
			}
			lc.setRow(realDev, row, colData);
		}
	}
}
