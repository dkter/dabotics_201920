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

void XDrivetrain::drive(double angle, rotationUnits angle_units) {
    double angle_radians = _angleToRadians(angle, angle_units);
    double positive_vel = cos(angle_radians + M_PI_4) * 100;
    double negative_vel = sin(angle_radians + M_PI_4) * 100;

    FrontLeftWheel.spin(directionType::fwd, positive_vel, percentUnits::pct);
    FrontRightWheel.spin(directionType::rev, negative_vel, percentUnits::pct);
    BackLeftWheel.spin(directionType::fwd, negative_vel, percentUnits::pct);
    BackRightWheel.spin(directionType::rev, positive_vel, percentUnits::pct);
}

void XDrivetrain::driveFor(double angle, rotationUnits angle_units, double distance, distanceUnits distance_units) {
    double angle_radians = _angleToRadians(angle, angle_units);
    double positive_vel = cos(angle_radians + M_PI_4) * 100;
    double negative_vel = sin(angle_radians + M_PI_4) * 100;
    double distance_inches = _distanceToInches(distance, distance_units);
    double revs = distance_inches / wheel_circumference;

    FrontLeftWheel.spinFor(directionType::fwd, revs, rotationUnits::rev, positive_vel, velocityUnits::pct, false);
    FrontRightWheel.spinFor(directionType::rev, revs, rotationUnits::rev, negative_vel, velocityUnits::pct, false);
    BackLeftWheel.spinFor(directionType::fwd, revs, rotationUnits::rev, negative_vel, velocityUnits::pct, false);
    BackRightWheel.spinFor(directionType::rev, revs, rotationUnits::rev, positive_vel, velocityUnits::pct, false);
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

    FrontLeftWheel.spinFor(wheel_direction, revs, rotationUnits::rev, false);
    FrontRightWheel.spinFor(wheel_direction, revs, rotationUnits::rev, false);
    BackLeftWheel.spinFor(wheel_direction, revs, rotationUnits::rev, false);
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
    else std::__throw_invalid_argument("angle_units must be one of deg, rev, raw");
    return 0;
}

double XDrivetrain::_distanceToInches(double distance, distanceUnits distance_units) {
    if (distance_units == distanceUnits::in)
        return distance;
    else if (distance_units == distanceUnits::cm)
        return distance * 2.54;
    else if (distance_units == distanceUnits::mm)
        return distance * 25.4;
    else std::__throw_invalid_argument("distance_units must be one of in, cm, mm");
    return 0;
}

directionType XDrivetrain::_getWheelDirection(turnType direction) {
    if (direction == turnType::right)
        return directionType::fwd;
    else if (direction == turnType::left)
        return directionType::rev;
    
    return directionType::fwd;
}
