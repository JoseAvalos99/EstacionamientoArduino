#include "Sensor.h"
#include "ServomotorSensor.h"
#include "Box.h"
static String lastParkingStatusMsg = "";

class ParkingLotSystem
{
private:
    ServomotorSensor servoEntry;
    Sensor irEntrySensor;
    Sensor irExitSensor;
    Box box1;
    Box box2;
    Box box3;

    long timeWaiting = 0;
    int state = 0;
    /**
     * State = 0 Vacio
     * State = 1 Uno o mas autos dentro
     * */

public:
    ParkingLotSystem(/* args */);
    Sensor getSensorEntry() { return irEntrySensor; }
    Sensor getSensorExit() { return irExitSensor; }
    Box getBox1() { return box1; }
    Box getBox2() { return box2; }
    Box getBox3() { return box3; }
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
        //Hay alguien en la salida
        if (isSomeoneAtTheExit())
        {
            move();
            return;
        }
        //Cuantas cajas tenemos llenas
        findBusyBoxes();
        //Cuantas cajas tenemos vacias
        findEmptyBoxes();
        //Enviar info a rabbit
        updateData();
    }
    void move()
    {
        servoEntry.rotateUp(120);
        delay(2500);
        servoEntry.rotateDown(120, 1);
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
                Serial.println("Caja 1 ocupada");
            }
        }
        if (box2.isEmpty)
        {
            if (box2.isSomeOneThere())
            {
                box2.isEmpty = false;
                Serial.println("Caja 2 ocupada");
            }
        }
        if (box3.isEmpty)
        {
            if (box3.isSomeOneThere())
            {
                box3.isEmpty = false;
                Serial.println("Caja 3 ocupada");
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
            if (!box1.isSomeOneThere())
            {
                box1.isEmpty = true;
                Serial.println("Caja 1 vacia");
            }
        }
        if (!box2.isEmpty)
        {
            if (!box2.isSomeOneThere())
            {
                Serial.println("Caja 2 vacia");
                box2.isEmpty = true;
            }
        }
        if (!box3.isEmpty)
        {
            if (!box3.isSomeOneThere())
            {
                Serial.println("Caja 3 vacia");
                box3.isEmpty = true;
            }
        }
        return 0;
    }
    void updateData()
    {
        if (timeWaiting >= millis())
            return;
        String msgW = "[";
        msgW += String(box1.isSomeOneThere()) + ",";
        msgW += String(box2.isSomeOneThere()) + ",";
        msgW += String(box3.isSomeOneThere()) + "";
        msgW += "]";
        if (msgW != lastParkingStatusMsg)
        {
            lastParkingStatusMsg = msgW;
            delay(10);
            Serial.println("ParkingSystemMsgRoutingKey|" + msgW);
            esp8266.println("ParkingSystemMsgRoutingKey|"+msgW);
        }
        else
            Serial.println("");
        timeWaiting = millis() + 5000;
    }
    ~ParkingLotSystem();
};

ParkingLotSystem::ParkingLotSystem(/* args */)
{
    servoEntry = ServomotorSensor(4, true, false);
    // servoEntry.attach();
    irEntrySensor = Sensor(A0, false, false);
    irEntrySensor.isInput();
    irExitSensor = Sensor(A1, false, false);
    irExitSensor.isInput();

    box1 = Box(A2, false, false, 1);
    box1.getSensor().isInput();

    box2 = Box(A3, false, false, 2);
    box2.getSensor().isInput();

    box3 = Box(A4, false, false, 2);
    box3.getSensor().isInput();
}

ParkingLotSystem::~ParkingLotSystem()
{
}
