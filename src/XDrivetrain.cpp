#include <cmath>
#include "XDrivetrain.h"

XDrivetrain::XDrivetrain (motor frontLeftWheel,
                          motor frontRightWheel,
                          motor backLeftWheel,
                          motor backRightWheel,
                          double width,
                          double height,
                          double wheelDiameter)
    : FrontLeftWheel(frontLeftWheel),
      FrontRightWheel(frontRightWheel),
      BackLeftWheel(backLeftWheel),
      BackRightWheel(backRightWheel)
{
    radius = sqrt(width*width + height*height) / 2;
    wheelCircumference = M_PI * wheelDiameter;
}

void XDrivetrain::drive(double angle) {
    double positive_vel = cos(angle + M_PI_4) * driveVelocity;
    double negative_vel = sin(angle + M_PI_4) * driveVelocity;

    FrontLeftWheel.spin(directionType::fwd, positive_vel, driveVelocityUnits);
    FrontRightWheel.spin(directionType::rev, negative_vel, driveVelocityUnits);
    BackLeftWheel.spin(directionType::fwd, negative_vel, driveVelocityUnits);
    BackRightWheel.spin(directionType::rev, positive_vel, driveVelocityUnits);
}

void XDrivetrain::drive(double angle, rotationUnits angle_units) {
    double angle_radians = _angleToRadians(angle, angle_units);
    drive(angle_radians);
}

void XDrivetrain::driveFor(double angle, rotationUnits angle_units, double distance, distanceUnits distance_units) {
    double angle_radians = _angleToRadians(angle, angle_units);
    double positive_vel = cos(angle_radians + M_PI_4) * driveVelocity;
    double negative_vel = sin(angle_radians + M_PI_4) * driveVelocity;
    double distance_inches = _distanceToInches(distance, distance_units);
    double revs = distance_inches / wheelCircumference;

    FrontLeftWheel.spinFor(directionType::fwd, revs, rotationUnits::rev, positive_vel, driveVelocityUnits, false);
    FrontRightWheel.spinFor(directionType::rev, revs, rotationUnits::rev, negative_vel, driveVelocityUnits, false);
    BackLeftWheel.spinFor(directionType::fwd, revs, rotationUnits::rev, negative_vel, driveVelocityUnits, false);
    BackRightWheel.spinFor(directionType::rev, revs, rotationUnits::rev, positive_vel, driveVelocityUnits, false);
}

void XDrivetrain::setDriveVelocity(double velocity, velocityUnits velocity_units) {
    driveVelocity = velocity;
    driveVelocityUnits = velocity_units;
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
    double revs = dist / wheelCircumference;

    FrontLeftWheel.spinFor(wheel_direction, revs, rotationUnits::rev, false);
    FrontRightWheel.spinFor(wheel_direction, revs, rotationUnits::rev, false);
    BackLeftWheel.spinFor(wheel_direction, revs, rotationUnits::rev, false);
    BackRightWheel.spinFor(wheel_direction, revs, rotationUnits::rev);
}

void XDrivetrain::setTurnVelocity(double velocity, velocityUnits velocity_units) {
    FrontLeftWheel.setVelocity(velocity, velocity_units);
    FrontRightWheel.setVelocity(velocity, velocity_units);
    BackLeftWheel.setVelocity(velocity, velocity_units);
    BackRightWheel.setVelocity(velocity, velocity_units);
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
