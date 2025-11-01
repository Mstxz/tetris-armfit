#include "ShapeL.hpp"

ShapeL::ShapeL(): Shape()
{
	bitmap[0][1] = true;
	bitmap[1][1] = true;
	bitmap[2][1] = true;
	bitmap[2][0] = true;
}

ShapeL::~ShapeL() {}

void	ShapeL::rotateLeft()
{
	bool tmp[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[3 - j][i] = bitmap[i][j];
	std::memcpy(bitmap, tmp, sizeof(bitmap));
}

void	ShapeL::rotateRight()
{
	bool tmp[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[j][3 - i] = bitmap[i][j];
	std::memcpy(bitmap, tmp, sizeof(bitmap));
}

Shape	*ShapeL::clone()
{
	ShapeL *newShape = new ShapeL();
	std::memcpy(newShape->bitmap, bitmap, sizeof(bitmap));
	newShape->posX = posX;
	newShape->posY = posY;
	return newShape;
}
