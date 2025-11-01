#include "ShapeFactory.hpp"

void	ShapeFactory::init()
{
	std::srand(random());
}

Shape	*ShapeFactory::createShape()
{
	int r = std::rand() % 5;
	switch (r)
	{
		case 0: return (new ShapeI());
		case 1: return (new ShapeJ());
		case 2: return (new ShapeL());
		case 3: return (new ShapeO());
		case 4: return (new ShapeT());
		default: return (new ShapeI());
	}
}
