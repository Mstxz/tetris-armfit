#ifndef SHAPE_HPP
# define SHAPE_HPP

// # include <LedControl.h>
# include <cstring>
// # include "TetrisGame.hpp"

class LedControl;

class Shape
{

	public:
		
		bool		bitmap[4][4]; // bitmap[y][x]
		int			posX;
		int			posY;
		Shape();
		virtual ~Shape();

		void	getMap(bool *buf);
		int		getX();
		int		getY();

		void	setX(int x);
		void	setY(int y);

		virtual void	rotateLeft() = 0;
		virtual void	rotateRight() = 0;
		void	moveLeft(bool (*board)[8]);
		void	moveRight(bool (*board)[8]);
		void	moveDown(bool (*board)[8]);
		bool	checkCollision(bool (*board)[8], int newX, int newY, bool newBitmap[4][4]);

		void	draw(bool (*board)[8]);
		virtual Shape	*clone() = 0;
		// virtual void	draw(LedControl &lcd) = 0;

};

#endif
