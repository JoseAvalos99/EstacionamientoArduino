#include "Class/ParkingLotSystem.h"
ParkingLotSystem parking;
ServomotorSensor servoEntry;
void setup()
{
	Serial.begin(9600);
	// servoEntry = ServomotorSensor(4,true,false);
	// servoEntry.attach();
	parking = ParkingLotSystem();
	parking.getServoEntry().attach();
}
void loop()
{
	// parking.main();
	// parking.Move();
	// Move();
	parking.findBusyBoxes();
	delay(1000);
}
void Move()
{
	servoEntry.rotateUp(180);
	servoEntry.rotateDown(180, 1);
}