#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050	mpu;

unsigned long long	timer = 0;

sensors_event_t a, g, temp;

void setup()
{
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


void loop()
{	
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
