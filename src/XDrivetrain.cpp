#include <cmath>
#include "XDrivetrain.h"

XDrivetrain::XDrivetrain (motor frontLeftWheel,
                          motor frontRightWheel,
                          motor backLeftWheel,
                          motor backRightWheel,
                          double width,
                          double height,
                          double wheel_diameter)
    : FrontLeftWheel(frontLeftWheel),
      FrontRightWheel(frontRightWheel),
      BackLeftWheel(backLeftWheel),
      BackRightWheel(backRightWheel)
{
    radius = sqrt(width*width + height*height) / 2;
    wheel_circumference = M_PI * wheel_diameter;
}

void XDrivetrain::turn(turnType direction) {
    directionType wheel_direction = _getWheelDirection(direction);

    FrontLeftWheel.spin(wheel_direction);
    FrontRightWheel.spin(wheel_direction);
    BackLeftWheel.spin(wheel_direction);
    BackRightWheel.spin(wheel_direction);
}

void XDrivetrain::turnFor(turnType direction, double angle, rotationUnits angle_units) {
    directionType wheel_direction = _getWheelDirection(direction);
    double angle_radians = _angleToRadians(angle, angle_units);
    double dist = angle_radians * radius;
    double revs = dist / wheel_circumference;

    FrontLeftWheel.spinFor(wheel_direction, revs, rotationUnits::rev);
    FrontRightWheel.spinFor(wheel_direction, revs, rotationUnits::rev);
    BackLeftWheel.spinFor(wheel_direction, revs, rotationUnits::rev);
    BackRightWheel.spinFor(wheel_direction, revs, rotationUnits::rev);
}

void XDrivetrain::stop() {
    FrontLeftWheel.stop();
    FrontRightWheel.stop();
    BackLeftWheel.stop();
    BackRightWheel.stop();
}

double XDrivetrain::_angleToRadians(double angle, rotationUnits angle_units) {
    if (angle_units == rotationUnits::deg)
        return angle * M_PI / 180;
    else if (angle_units == rotationUnits::rev)
        return angle * M_PI * 2;
    else if (angle_units == rotationUnits::raw)
        // 960 encoder units in one revolution
        return angle * M_PI / 480;
    
    return 0;
}

directionType XDrivetrain::_getWheelDirection(turnType direction) {
    if (direction == turnType::right)
        return directionType::fwd;
    else if (direction == turnType::left)
        return directionType::rev;
    
    return directionType::fwd;
}
