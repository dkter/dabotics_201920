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
                     double wheelDiameter);

        void drive(double angle, rotationUnits angle_units);
        void driveFor(double angle, rotationUnits angle_units,
                      double distance, distanceUnits distance_units);
        void setDriveVelocity(double velocity, velocityUnits velocity_units);

        void turn(turnType direction);
        void turnFor(turnType direction, double angle, rotationUnits angle_units);
        void setTurnVelocity(double velocity, velocityUnits velocity_units);

        void stop();


    private:
        motor FrontLeftWheel;
        motor FrontRightWheel;
        motor BackLeftWheel;
        motor BackRightWheel;
        double radius;
        double wheelCircumference;
        double driveVelocity{100};
        velocityUnits driveVelocityUnits{velocityUnits::pct};

        double _angleToRadians(double angle, rotationUnits angle_units);
        double _distanceToInches(double distance, distanceUnits distance_units);
        double _velocityToPct(double velocity, velocityUnits velocity_units);
        directionType _getWheelDirection(turnType direction);
};