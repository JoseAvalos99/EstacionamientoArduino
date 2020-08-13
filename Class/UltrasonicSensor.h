#include "Sensor.h"
#include <NewPing.h>

static unsigned int lastCentimeters = 0;
class UltrasonicSensor : public Sensor
{
private:
#define TRIGGER_PIN 05
#define ECHO_PIN 04
#define MAX_DISTANCE 200

    uint8_t trigger = 5;
    int CONFIG_LEVEL_SENSOR_TRIG_PIN = 5;
    // configurar aqui el pin echo del sensor
    int CONFIG_LEVEL_SENSOR_ECHO_PIN = 4;
    // configurar la distancia maxima a detectar
    long CONFIG_LEVEL_SENSOR_MAX_DISTANCE = 200;
    // configurar la capacidad máxima del recipiente
    long CONFIG_LEVEL_SENSOR_MAX_LITERS = 10;
    // configurar la distancia cuando el recipiente está lleno
    int CONFIG_LEVEL_SENSOR_FULL = 3; //3
    // configurar la distancia cuando el recipiente está vacío
    int CONFIG_LEVEL_SENSOR_EMPTY = 10;
    // configurar el nivel de porcentaje donde empezará a funcionar el led
    int CONFIG_LEVEL_SENSOR_ALERT_LEVEL = 20;
    NewPing sonar;

public:
    UltrasonicSensor(/* args */);
    UltrasonicSensor(int Pin, bool IsDigital, bool IsPWM);

    int getDistansceInCm()
    {
        int median = sonar.ping_cm();
        delay(10);
        return median;
    }
    ~UltrasonicSensor();
};

UltrasonicSensor::UltrasonicSensor(/* args */)
    : sonar(5, 4, 200)
    /**
     * 5 = TRIGGER_PIN
     * 4 = ECHO_PIN
     * 200 = CONFIG_LEVEL_SENSOR_MAX_DISTANCE
     */
{
}
UltrasonicSensor::UltrasonicSensor(int Pin, bool IsDigital, bool IsPWM)
    : sonar(5, 4, 200)
{
    pin = Pin;
    isDigital = IsDigital;
    isPWM = IsPWM;
}

UltrasonicSensor::~UltrasonicSensor()
{
}
