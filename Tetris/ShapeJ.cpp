#include "ShapeJ.hpp"

ShapeJ::ShapeJ(): Shape()
{
	bitmap[0][0] = true;
	bitmap[1][0] = true;
	bitmap[2][0] = true;
	bitmap[2][1] = true;
}

ShapeJ::~ShapeJ() {}

void	ShapeJ::rotateLeft()
{
	bool tmp[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[3 - j][i] = bitmap[i][j];
	memcpy(bitmap, tmp, sizeof(bitmap));
}

void	ShapeJ::rotateRight()
{
	bool tmp[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[j][3 - i] = bitmap[i][j];
	memcpy(bitmap, tmp, sizeof(bitmap));
}

Shape	*ShapeJ::clone()
{
	ShapeJ *newShape = new ShapeJ();
	memcpy(newShape->bitmap, bitmap, sizeof(bitmap));
	newShape->posX = posX;
	newShape->posY = posY;
	return newShape;
}