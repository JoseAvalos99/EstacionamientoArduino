#include "Class/Sensor.h"
Sensor irSensor;
int irSensorPIN = 2;
void setup()
{
	irSensor = Sensor(irSensorPIN, true, false);
	Serial.begin(9600);
}
void loop()
{
	int value = irSensor.getValue();
	if(value == 1)
		Serial.println("No hay nada");
	else
		Serial.println("Hay algo");
	
	delay(1000);
}