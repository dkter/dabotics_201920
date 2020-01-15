using namespace vex;

class XDrivetrain {
    public:
        XDrivetrain (motor FrontLeftWheel,
                     motor FrontRightWheel,
                     motor BackLeftWheel,
                     motor BackRightWheel,
                     double width,
                     double height);

        void drive(double angle, rotationUnits units);
        void driveFor(double angle, rotationUnits angle_units,
                      double distance, distanceUnits distance_units);

        void turn(directionType direction);
        void turnFor(directionType direction, double angle, rotationUnits angle_units);


    private:
        motor FrontLeftWheel;
        motor FrontRightWheel;
        motor BackLeftWheel;
        motor BackRightWheel;
        double width;
        double height;
};