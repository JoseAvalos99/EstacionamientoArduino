#include "Class/ServomotorSensor.h"
// int irSensorPIN = 2;
ServomotorSensor servo;
void setup()
{
	//irSensor = Sensor(irSensorPIN, true, false);
	Serial.begin(9600);
	servo = ServomotorSensor(9, true, false);
}
void loop()
{
	for (int i = 0; i <= 190; i++)
	{
		// Desplazamos al ángulo correspondiente
		servo.setGrades(i);
		// Hacemos una pausa de 25ms
		delay(25);
	}

	// Para el sentido negativo
	for (int i = 189; i > 0; i--)
	{
		// Desplazamos al ángulo correspondiente
		servo.setGrades(i);
		// Hacemos una pausa de 25ms
		delay(25);
	}
}