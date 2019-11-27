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
    Brain.Screen.clearScreen();
    if (VisionSensor.largestObject.exists && VisionSensor.largestObject.width > 50) {
      Brain.Screen.print(VisionSensor.largestObject.centerX);
      difference = VisionSensor.largestObject.centerX - (VISION_CENTRE + OFFSET);
      if (difference < 0) {
        // go left
        Brain.Screen.print("Left");
        CenterWheel.spinFor(-5, degrees);
      }
      else {
        // go right
        Brain.Screen.print("Right");
        CenterWheel.spinFor(5, degrees);
      }
    }
  } while (abs(difference) > TOLERANCE);
}

void grab() {
  Claw.spin(reverse);
  task::sleep(500);
  Claw.stop();
}

void drop() {
  Claw.spin(forward);
  task::sleep(500);
  Claw.stop();
}

void lift(int deg) {
  ShaftLeft.spinFor(deg, degrees);
  ShaftRight.spinFor(deg, degrees);
}

void turn(int deg) {
  const double WHEELBASE_RAD = 16 * sqrt(2);
  double radians = deg * 3.14159 / 180.0;
  double distance = WHEELBASE_RAD * deg;
  LeftDriveSmart.spinFor(distance, degrees);
  RightDriveSmart.spinFor(-distance, degrees);
}