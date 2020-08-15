#include "Sensor.h"
#include "ServomotorSensor.h"
#include "Box.h"

class ParkingLotSystem
{
private:
    ServomotorSensor servoEntry;
    Sensor irEntrySensor;
    Sensor irExitSensor;
    Box box1;
    Box box2;
    Box box3;
    int lastBoxBusy = 0;
    int lastBoxEmpty = 0;
    int state = 0;
    /**
     * State = 0 Vacio
     * State = 1 Uno o mas autos dentro
     * */

public:
    ParkingLotSystem(/* args */);
    Sensor getSensorEntry() { return irEntrySensor; }
    Sensor getSensorExit() { return irExitSensor; }
    Sensor getBox1() { return box1; }
    Sensor getBox2() { return box2; }
    Sensor getBox3() { return box3; }
    ServomotorSensor getServoEntry() { return servoEntry; }

    void main()
    {
        // Hay alguien en la entrada
        if (isSomeoneAtTheEntry())
        {
            //Lo hay
            move(); // Mueve la  barra
            return;
        }
        if (isSomeoneAtTheExit())
        {
            move();
            return;
        }
        if (state == 0)
        {
            int value = findBusyBoxes();
            if (value == 0)
                return;
            else
            {
                lastBoxBusy = value;
                state = 1;
            }
        }
        else if (state == 1)
        {
            int value = findEmptyBoxes();
            if (value == 0)
            {
                state = 0;
                return;
            }
            else
            {
                lastBoxEmpty = value;
                state = 1;
            }
        }
    }
    void move()
    {
        servoEntry.rotateUp(130);
        delay(1000);
        servoEntry.rotateDown(130, 1);
    }
    bool isSomeoneAtTheEntry()
    {
        if (irEntrySensor.getValue() < 100)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool isSomeoneAtTheExit()
    {
        if (irExitSensor.getValue() < 100)
            return true;
        else
            return false;
    }
    int findBusyBoxes()
    {
        //¿Esta vacia la caja 1?
        if (box1.isEmpty)
        {
            //¿El sensor marca algo?
            if (box1.isSomeOneThere())
            {
                box1.isEmpty = false;
                return 1;
            }
        }
        if (box2.isEmpty)
        {
            if (box2.isSomeOneThere())
            {
                box2.isEmpty = false;
                return 2;
            }
        }
        if (box3.isEmpty)
        {
            if (box3.isSomeOneThere())
            {
                box3.isEmpty = false;
                return 3;
            }
        }
        return 0;
    }
    int findEmptyBoxes()
    {
        //¿Esta vacia la caja 1?
        if (!box1.isEmpty)
        {
            //¿El sensor marca algo?
            if (box1.isSomeOneThere())
            {
                box1.isEmpty = true;
                return 1;
            }
        }
        if (!box2.isEmpty)
        {
            if (box2.isSomeOneThere())
            {
                box2.isEmpty = true;
                return 2;
            }
        }
        if (!box3.isEmpty)
        {
            if (box3.isSomeOneThere())
            {
                box3.isEmpty = true;
                return 3;
            }
        }
        return 0;
    }
    ~ParkingLotSystem();
};

ParkingLotSystem::ParkingLotSystem(/* args */)
{
    servoEntry = ServomotorSensor(4, true, false);
    irEntrySensor = Sensor(A0, false, false);
    irEntrySensor.isInput();
    irExitSensor = Sensor(A1, false, false);
    irExitSensor.isInput();

    box1 = Box(A2, false, false, 1);
    box1.isInput();

    box2 = Box(A3, false, false, 2);
    box2.isInput();

    box3 = Box(A4, false, false, 2);
    box3.isInput();

    // servoEntry.attach();
}

ParkingLotSystem::~ParkingLotSystem()
{
}
