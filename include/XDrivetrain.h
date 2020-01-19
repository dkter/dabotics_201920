#include "vex.h"

using namespace vex;

class XDrivetrain {
    public:
        XDrivetrain (motor frontLeftWheel,
                     motor frontRightWheel,
                     motor backLeftWheel,
                     motor backRightWheel,
                     double width,
                     double height,
                     double wheel_diameter);

        void drive(double angle, rotationUnits angle_units);
        void driveFor(double angle, rotationUnits angle_units,
                      double distance, distanceUnits distance_units);

        void turn(turnType direction);
        void turnFor(turnType direction, double angle, rotationUnits angle_units);

        void stop();


    private:
        motor FrontLeftWheel;
        motor FrontRightWheel;
        motor BackLeftWheel;
        motor BackRightWheel;
        double radius;
        double wheel_circumference;

        double _angleToRadians(double angle, rotationUnits angle_units);
        double _distanceToInches(double distance, distanceUnits distance_units);
        directionType _getWheelDirection(turnType direction);
};