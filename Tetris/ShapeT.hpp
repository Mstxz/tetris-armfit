#ifndef SHAPET_HPP
#define SHAPET_HPP

#include "Shape.hpp"

class ShapeT : public Shape
{

	public:

		ShapeT();
		~ShapeT();

		void rotateLeft();
		void rotateRight();
		Shape *clone();

};

#endif
