#include "ShapeO.hpp"

ShapeO::ShapeO(): Shape()
{
	bitmap[1][1] = true;
	bitmap[1][2] = true;
	bitmap[2][1] = true;
	bitmap[2][2] = true;
}

ShapeO::~ShapeO() {}

void	ShapeO::rotateLeft() {}

void	ShapeO::rotateRight() {}

Shape	*ShapeO::clone()
{
	ShapeO *newShape = new ShapeO();
	std::memcpy(newShape->bitmap, bitmap, sizeof(bitmap));
	newShape->posX = posX;
	newShape->posY = posY;
	return newShape;
}
