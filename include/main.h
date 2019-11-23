
class Car {
    public:
        static const int number = 4;
        int colour;
        int speed = 60;
        void go(int metres);
        Car(int colour);
    private:
        int odometer = 0;
};