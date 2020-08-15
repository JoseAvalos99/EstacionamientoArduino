class Box : public Sensor
{
private:
    /* data */
public:
    int number;
    bool isEmpty;
    Box(/* args */);
    Box(int Pin, bool IsDigital, bool IsPWM, int Number);
    bool isSomeOneThere()
    {
        if (getValue() < 100)
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
    pin = Pin;
    isDigital = IsDigital;
    isPWM = IsPWM;
    isEmpty = true;
    number = number;
}

Box::~Box()
{
}
