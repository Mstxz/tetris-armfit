#ifndef SHAPEO_HPP
#define SHAPEO_HPP

#include "Shape.hpp"

class ShapeO : public Shape
{

	public:

		ShapeO();
		~ShapeO();

		void rotateLeft();
		void rotateRight();
		Shape *clone();

};

#endif
