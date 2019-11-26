#include "auto.h"
#include "vex.h"
#include "VisionSensor.h"

void autonomous() {
  Drivetrain.driveFor(15, inches);
  grab();
  lift(30);
  Drivetrain.driveFor(-10, inches);
  drop();
  //align();
}

void align() {
  int TOLERANCE = 10;
  int OFFSET = 0;
  int VISION_CENTRE = 158;
  int difference = 0;

  do {
    VisionSensor.takeSnapshot(GREEN_CUBE);
    if (VisionSensor.largestObject.exists && VisionSensor.largestObject.width > 50) {
      difference = VisionSensor.largestObject.centerX - (VISION_CENTRE + OFFSET);
      if (difference < 0) {
        // go left
        CenterWheel.spinFor(-5, degrees);
      }
      else {
        // go right
        CenterWheel.spinFor(5, degrees);
      }
    }
  } while (abs(difference) > TOLERANCE);
}

void grab() {
  Claw.spinFor(-90, degrees);
}

void drop() {
  Claw.spinFor(90, degrees);
}

void lift(int deg) {
  ShaftLeft.spinFor(-deg, degrees);
  ShaftRight.spinFor(-deg, degrees);
}