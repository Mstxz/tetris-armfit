#ifndef TETRISGAME_HPP
# define TETRISGAME_HPP

# include <Arduino.h>
// # include <LedControl.h>
# include "ShapeFactory.hpp"
# include "Shape.hpp"
# include <string>

# define MAX_Y 32
# define MAX_X 8

typedef	enum e_event
{
	IDLE,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_DOWNWARD,
	ROTATE_LEFT,
	ROTATE_RIGHT
}	t_event;

class TetrisGame
{

	private:

		bool			board[32][8];
		unsigned long	lastUpdate;
		unsigned long	moveSpeed; // Time for piece to move.
		Shape			*curShape;

	public:

		TetrisGame();
		~TetrisGame();

		int		KeyEvent(t_event event);
		void	updateGame();
		void	restartGame();
		void	clearFullLines();

		void	render();
		void	display(bool (*board)[8]);

};

#endif
