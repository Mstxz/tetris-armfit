#include "ShapeI.hpp"

ShapeI::ShapeI(): Shape()
{
	// Clear bitmap first
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			bitmap[i][j] = false;

	// I shape: vertical line initially
	for (int i = 0; i < 4; i++)
		bitmap[i][0] = true;
}

// Destructor
ShapeI::~ShapeI() {}

// Rotate left (90° counterclockwise)
void ShapeI::rotateLeft()
{
	bool tmp[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[3 - j][i] = bitmap[i][j];
	std::memcpy(bitmap, tmp, sizeof(bitmap));
}

// Rotate right (90° clockwise)
void ShapeI::rotateRight()
{
	bool tmp[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[j][3 - i] = bitmap[i][j];
	std::memcpy(bitmap, tmp, sizeof(bitmap));
}

// Clone method: returns a new copy of this shape
Shape* ShapeI::clone()
{
	ShapeI* newShape = new ShapeI();
	std::memcpy(newShape->bitmap, bitmap, sizeof(bitmap));
	newShape->posX = posX;
	newShape->posY = posY;
	return newShape;
}
