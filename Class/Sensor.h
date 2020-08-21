#include "SoftwareSerial.h"
SoftwareSerial esp8266(2, 3); // RX, TX

class Sensor
{
protected:
	int pin;
	int value;
	bool isDigital;
	bool isPWM;
	void notify(String topic, String value)
	{
	}

public:
	Sensor();

	Sensor(int Pin, bool IsDigital, bool IsPWM);
	void isInput()
	{
		pinMode(pin, INPUT);
	}
	void isOutput()
	{
		pinMode(pin, OUTPUT);
	}

	int getValue()
	{
		int value = 0;
		if (isDigital && !isPWM)
			value = digitalRead(pin);
		else
			value = analogRead(pin);
		delay(10);
		return value;
	}
	void setValue(int value)
	{
		if (isDigital && !isPWM)
			digitalWrite(pin, value);
		else
			analogWrite(pin, value);
		delay(10);
	}
	~Sensor();
};
Sensor::Sensor()
{
}
Sensor::Sensor(int Pin, bool IsDigital, bool IsPWM)
{
	pin = Pin;
	isDigital = IsDigital;
	isPWM = IsPWM;
}
Sensor::~Sensor()
{
}