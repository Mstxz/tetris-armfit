#include <Arduino.h>
#include <LedControl.h>

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#include "TetrisGame.hpp"

# define BUTTON 9

Adafruit_MPU6050	mpu;
TetrisGame 			game;

unsigned long long	timer = 0;
sensors_event_t a, g, temp;

// 4 MAX7219 modules → 32x8 matrix
// DIN → 12, CLK → 11, CS → 10
LedControl lc = LedControl(12, 11, 10, 4);

      
void setup() {
	Serial.begin(115200);

	// Wake up displays
	for (int i = 0; i < 4; ++i) {
		lc.shutdown(i, false);
		lc.setIntensity(i, 4);
		lc.clearDisplay(i);
	}
	pinMode(BUTTON, INPUT_PULLUP);
	pinMode(LED_BUILTIN, OUTPUT);
	for (int i = 0; i < 3; i++)
	{
		digitalWrite(LED_BUILTIN, HIGH);
		delay(50);
		digitalWrite(LED_BUILTIN, LOW);
		delay(50);
	}
	Wire.setClock(100000);
	mpu.begin(0x68);
	delay(100);
	Serial.println("MPU6050 Found!");
	mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
	mpu.setGyroRange(MPU6050_RANGE_500_DEG);
	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
	pinMode(LED_BUILTIN, OUTPUT);
}

# define X_OFFSET 356
# define Y_OFFSET 367

void loop() {
	static unsigned long lastInput = 0;
	sensors_event_t a, g, temp;
	t_event ev = IDLE;

	mpu.getEvent(&a, &g, &temp);
	if (millis() - lastInput >= INPUT_DELAY)
	{
		Serial.print("Accel X: "); Serial.print(a.acceleration.x); // + = up
		Serial.print(", Y: "); Serial.print(a.acceleration.y); //focus this (-) = left (+) = right
		Serial.print(", Z: "); Serial.println(a.acceleration.z); 
		Serial.print("Gyro X: "); Serial.print(g.gyro.x); // + = up
		Serial.print(", Y: "); Serial.print(g.gyro.y); //focus this (-) = left (+) = right
		Serial.print(", Z: "); Serial.println(g.gyro.z); 
		if (a.acceleration.y < -4.25) 			//	if (g.gyro.x) < -15)	this will be rotate left (y is below -15)
			game.KeyEvent(MOVE_LEFT); 
		else if (a.acceleration.y > 4.25) 		//  if (g.gyro.x) > -14.25)this will be rotate right (y is above 15)
			game.KeyEvent(MOVE_RIGHT); 
		else if (a.acceleration.z < -10 && millis() - game.getShapeSpawnTime() > POLLING_RATE) 					//this will be move up (x is below -15)								
			game.KeyEvent(MOVE_DOWNWARD);
		else if (!digitalRead(BUTTON))
			game.KeyEvent(ROTATE_RIGHT);
		lastInput = millis();
	}
	if (ev != IDLE) game.KeyEvent(ev);
	game.updateGame();
	game.render();
}
