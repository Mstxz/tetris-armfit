#include <Arduino.h>
#include <LedControl.h>
#include <type_traits>

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#include "TetrisGame.hpp"

// 4 MAX7219 modules → 32x8 matrix
// DIN → 12, CLK → 11, CS → 10
LedControl lc = LedControl(12, 11, 10, 4);

Adafruit_MPU6050	mpu;

unsigned long long	timer = 0;

sensors_event_t a, g, temp;

int x_val = 0, y_val = 0;


TetrisGame game;

void setup() {
	Serial.begin(115200);

	// Wake up displays
	for (int i = 0; i < 4; ++i) {
		lc.shutdown(i, false);
		lc.setIntensity(i, 8);
		lc.clearDisplay(i);
	}

	/*gyro*/
	pinMode(LED_BUILTIN, OUTPUT);
	for (int i = 0; i < 3; i++)
	{
		digitalWrite(LED_BUILTIN, HIGH);
		delay(50);
		digitalWrite(LED_BUILTIN, LOW);
		delay(50);
	}
	Serial.begin(115200);
	Serial.println("begin test");
	delay(500);
	mpu.begin();
	Serial.println("MPU6050 Found!");
	mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
	mpu.setGyroRange(MPU6050_RANGE_500_DEG);
	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

# define X_OFFSET 356
# define Y_OFFSET 367

void loop() {
	static unsigned long lastInput = 0;
	t_event ev = IDLE;

	// TODO: Change input into using mpu6050

	if (millis() - lastInput > INPUT_DELAY)
	{
		if (y_val < -15) 								//this will be rotate left (y is below -15) 					/*x_val < -100*/
			game.KeyEvent(MOVE_LEFT); 
		else if (y_val > 15) 						//this will be rotate right (y is above 15)						/*x_val > 100*/
			game.KeyEvent(MOVE_RIGHT); 
		else if (x_val < -15) 					//this will be move up (x is below -15)								/*y_val > 150 && millis() - game.getShapeSpawnTime() > POLLING_RATE/*/
			game.KeyEvent(MOVE_DOWNWARD);
		else if (x_val > 15) 						//this will be move up (x is above 15)								/*digitalRead(2) == LOW*/
			game.KeyEvent(ROTATE_RIGHT);
		lastInput = millis();
	}


	if (ev != IDLE) game.KeyEvent(ev);

	game.updateGame();
	game.render();  
}
 
void gyroRead(){
	if (millis() - timer > 0)
	{
		sensors_event_t a, g, temp;
		mpu.getEvent(&a, &g, &temp);
		Serial.print("Accel X: "); Serial.print(a.acceleration.x); // + = up
		Serial.print(", Y: "); Serial.print(a.acceleration.y); //focus this (-) = left (+) = right
		Serial.print(", Z: "); Serial.println(a.acceleration.z); 
	
		Serial.print("Gyro X: "); Serial.print(g.gyro.x);
		Serial.print(", Y: "); Serial.print(g.gyro.y);
		Serial.print(", Z: "); Serial.println(g.gyro.z);
	
		Serial.print("Temp: "); Serial.print(temp.temperature);
		Serial.println(" °C");
	
		Serial.println();
		timer = millis();
	}
}
