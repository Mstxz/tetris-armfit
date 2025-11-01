#ifndef SHAPEJ_HPP
#define SHAPEJ_HPP

#include "Shape.hpp"

class ShapeJ : public Shape
{

	public:

		ShapeJ();
		~ShapeJ();

		void rotateLeft();
		void rotateRight();
		Shape *clone();

};

#endif
