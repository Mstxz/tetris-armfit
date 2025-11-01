#include "Shape.hpp"

Shape::Shape(): posX(3), posY(0)
{
	std::memset(this->bitmap, 0, sizeof(this->bitmap));
}

Shape::~Shape(){}

void	Shape::getMap(bool *buf)
{
	if (!buf)
		return ;
	std::memcpy(buf, bitmap, sizeof(bitmap));
}

int	Shape::getX()
{
	return posX;
}

int	Shape::getY()
{
	return posY;
}

void	Shape::setX(int x)
{
	this->posX = x;
}

void	Shape::setY(int y)
{
	this->posY = y;
}

void Shape::moveRight(bool (*board)[8])
{
	if (!checkCollision(board, posX - 1, posY, bitmap))
	{
		posX--; // move right
	}
}

void Shape::moveLeft(bool (*board)[8])
{
	if (!checkCollision(board, posX + 1, posY, bitmap))
	{
		posX++; // move left
	}
}

void Shape::moveDown(bool (*board)[8])
{
	// Only move down if no collision occurs
	while (!checkCollision(board, posX, posY + 1, bitmap))
	{
		posY++; // move the shape down by 1
	}
}

bool Shape::checkCollision(bool (*board)[8], int newX, int newY, bool newBitmap[4][4])
{
	for (int i = 0; i < 4; i++)	   // rows of the shape
	{
		for (int j = 0; j < 4; j++)   // columns of the shape
		{
			if (!newBitmap[i][j]) continue; // skip empty cells

			int boardX = newX + j;
			int boardY = newY + i;

			// Check boundaries
			if (boardX < 0 || boardX >= 8 || boardY < 0 || boardY >= 32)
				return true; // collision

			// Check if board cell is already occupied
			if (board[boardY][boardX])
				return true; // collision
		}
	}
	return false; // no collision
}

void	Shape::draw(bool (*board)[8])
{
	for (int i = 0; i < 4; i++) // rows of shape
	{
		for (int j = 0; j < 4; j++) // columns of shape
		{
			if (!bitmap[i][j]) continue; // skip empty cells

			int boardX = this->posX + j;
			int boardY = this->posY + i;

			// Check boundaries
			if (boardX >= 0 && boardX < 8 && boardY >= 0 && boardY < 32)
			{
				board[boardY][boardX] = true; // turn on pixel
			}
		}
	}
}
