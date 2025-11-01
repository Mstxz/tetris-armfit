#include "ShapeFactory.hpp"
#include <cstdlib>

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
		default: return (new ShapeI());
	}
}
