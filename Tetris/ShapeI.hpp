#ifndef SHAPEI_HPP
# define SHAPEI_HPP

# include "Shape.hpp"

class	ShapeI: public Shape
{

	public:

		ShapeI();
		~ShapeI();

		void	rotateLeft();
		void	rotateRight();

		Shape	*clone();

};

#endif
