#include <Servo.h>

class ServomotorSensor : public Sensor
{
private:
    Servo servoMotor;

public:
    ServomotorSensor(/* args */);
    ServomotorSensor(int Pin, bool IsDigital, bool IsPWM);
    void attach(){
        servoMotor.attach(pin);
    }
    void rotateUp(int gradesTotales)
    {
        for (int i = 0; i <= gradesTotales; i++)
        {
            servoMotor.write(i);
            delay(20);
        }
    }
    void rotateDown(int fromGrades, int toGrades)
    {
        for (int i = fromGrades; i > toGrades; i--)
        {
            servoMotor.write(i);
            delay(20);
        }
    }
    void setGrades(int grades){
        servoMotor.write(grades);
    }
    ~ServomotorSensor();
};

ServomotorSensor::ServomotorSensor(/* args */)
    : servoMotor()
{
}

ServomotorSensor::ServomotorSensor(int Pin, bool IsDigital, bool IsPWM)
    : servoMotor()
{
    // servoMotor.attach(pin);
    servoMotor.write(0);
    pin = Pin;
    isDigital = IsDigital;
    isPWM = IsPWM;
}

ServomotorSensor::~ServomotorSensor()
{
}
