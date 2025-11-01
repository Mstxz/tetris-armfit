#include <Arduino.h>
#include <LedControl.h>
#include <type_traits>
#include "TetrisGame.hpp"

// 4 MAX7219 modules → 32x8 matrix
// DIN → 12, CLK → 11, CS → 10
LedControl lc = LedControl(12, 11, 10, 4);

TetrisGame game;

void setup() {
	Serial.begin(115200);

	// Wake up displays
	for (int i = 0; i < 4; ++i) {
		lc.shutdown(i, false);
		lc.setIntensity(i, 8);
		lc.clearDisplay(i);
	}
}

# define X_OFFSET 356
# define Y_OFFSET 367

void loop() {
	static unsigned long lastInput = 0;
	t_event ev = IDLE;

	// TODO: Change input into using mpu6050
	/*
	if (millis() - lastInput > INPUT_DELAY)
	{
		if (x_val < -100)
			game.KeyEvent(MOVE_LEFT);
		else if (x_val > 100)
			game.KeyEvent(MOVE_RIGHT);
		else if (y_val > 150 && millis() - game.getShapeSpawnTime() > POLLING_RATE)
			game.KeyEvent(MOVE_DOWNWARD);
		else if (digitalRead(2) == LOW)
			game.KeyEvent(ROTATE_RIGHT);
		lastInput = millis();
	}
	*/

	if (ev != IDLE) game.KeyEvent(ev);

	game.updateGame();
	game.render();
}
