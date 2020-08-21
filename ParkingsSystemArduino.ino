#include "Class/ParkingLotSystem.h"
#include "ArduinoJson.h"

ParkingLotSystem parking;
int ir = A0;

void setup()
{
	Serial.begin(9600);
	esp8266.begin(9600);
	parking = ParkingLotSystem();
	parking.getServoEntry().attach();
}
void loop()
{
	parking.main();
	controlEsp8266();
	delay(1000);
	
}
void controlEsp8266()
{
	if (esp8266.available())
	{
		String msg = esp8266.readString();
		if (!msg.startsWith("{"))
		{
			Serial.println(msg);
			return;
		}
		DynamicJsonBuffer jsonBuffer;
		JsonObject &root = jsonBuffer.parseObject(msg);
		String key = root["key"];
		String value  = root["value"];
		if (key == "helloWorld")
		{
			Serial.println(value);
			return;
		}
		else if (key == "openDoor")
		{
			parking.move();
			return;
		}
	}
}