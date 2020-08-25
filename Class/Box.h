class Box 
{
private:
    /* data */
    Sensor sensor;
public:
    int number;
    bool isEmpty;
    Box(/* args */);
    Box(int Pin, bool IsDigital, bool IsPWM, int Number);
    Sensor getSensor() { return sensor; }
    bool isSomeOneThere()
    {
        if (sensor.getValue() < 100)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    ~Box();
};

Box::Box(/* args */)
{
}
Box::Box(int Pin, bool IsDigital, bool IsPWM, int Number)
{
    sensor = Sensor(Pin, IsDigital, IsPWM);
    isEmpty = true;
    number = number;
}

Box::~Box()
{
}
