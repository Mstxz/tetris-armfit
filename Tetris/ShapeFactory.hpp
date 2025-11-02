#ifndef SHAPEFACTORY_HPP
# define SHAPEFACTORY_HPP

# include <stdlib.h>
# include <time.h>

# include <Arduino.h>
# include "Shape.hpp"
#include "ShapeI.hpp"
#include "ShapeJ.hpp"
#include "ShapeL.hpp"
#include "ShapeO.hpp"
#include "ShapeT.hpp"

class ShapeFactory
{

	public:

		static void		init();
		static Shape	*createShape();

};

#endif
