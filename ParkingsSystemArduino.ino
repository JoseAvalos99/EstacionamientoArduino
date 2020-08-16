#include "Class/ParkingLotSystem.h"
ParkingLotSystem parking;
ServomotorSensor servoEntry;
void setup()
{
	Serial.begin(9600);
	// servoEntry = ServomotorSensor(4,true,false);
	// servoEntry.attach();
	parking = ParkingLotSystem();
}
void loop()
{
	parking.main();
	delay(1000);
}