#include "vex.h"

using namespace vex;

class XDrivetrain {
    public:
        XDrivetrain (motor frontLeftWheel,
                     motor frontRightWheel,
                     motor backLeftWheel,
                     motor backRightWheel,
                     double width,
                     double height);

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

        directionType _getWheelDirection(turnType direction);
};