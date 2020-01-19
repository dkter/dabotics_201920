#include "XDrivetrain.h"

XDrivetrain::XDrivetrain (motor frontLeftWheel,
                          motor frontRightWheel,
                          motor backLeftWheel,
                          motor backRightWheel,
                          double width,
                          double height)
    : FrontLeftWheel(frontLeftWheel),
      FrontRightWheel(frontRightWheel),
      BackLeftWheel(backLeftWheel),
      BackRightWheel(backRightWheel)
{
    radius = sqrt(width*width + height*height) / 2;
}

void XDrivetrain::turn(turnType direction) {
    directionType wheel_direction = _getWheelDirection(direction);

    FrontLeftWheel.spin(wheel_direction);
    FrontRightWheel.spin(wheel_direction);
    BackLeftWheel.spin(wheel_direction);
    BackRightWheel.spin(wheel_direction);
}

void XDrivetrain::stop() {
    FrontLeftWheel.stop();
    FrontRightWheel.stop();
    BackLeftWheel.stop();
    BackRightWheel.stop();
}

directionType XDrivetrain::_getWheelDirection(turnType direction) {
    if (direction == turnType::right)
        return directionType::fwd;
    else if (direction == turnType::left)
        return directionType::rev;
    
    return directionType::fwd;
}
