#ifndef SHAPEL_HPP
#define SHAPEL_HPP

#include "Shape.hpp"

class ShapeL : public Shape
{

	public:

		ShapeL();
		~ShapeL();
	
		void rotateLeft();
		void rotateRight();
		Shape *clone();

};

#endif