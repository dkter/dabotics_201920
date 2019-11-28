#include "auto.h"
#include "vex.h"
#include "VisionSensor.h"

constexpr float ROBOT_LENGTH = 18;
constexpr float CUBE_WIDTH = 5.5;
constexpr float LENGTH_TO_CLAW = ROBOT_LENGTH - (CUBE_WIDTH / 2);
constexpr float TILE_LENGTH = 24;
constexpr int VERY_SLOW_SPEED = 25; //rpm

void autonomous() {
    blue_left4();
}

void blue_left4() {
    Drivetrain.driveFor(16, inches);
    grab();
    lift(60);
    Drivetrain.driveFor(-12, inches);
    Drivetrain.turnFor(-90, degrees);
    CenterWheel.spinFor(1, seconds, -100, rpm );
    Drivetrain.setDriveVelocity(VERY_SLOW_SPEED, rpm);
    Drivetrain.drive(forward);
    task::sleep(1000);
    Drivetrain.stop();
    Drivetrain.turnFor(-45, degrees);
    Drivetrain.drive(forward);
    task::sleep(1000);
    Drivetrain.stop();
    lift(-50);
    drop();
    Drivetrain.driveFor(-10, inches);
}

void red_left4() {
    Drivetrain.driveFor(16, inches);
    grab();
    lift(60);
    Drivetrain.driveFor(-12, inches);
    Drivetrain.turnFor(90, degrees);
    CenterWheel.spinFor(1, seconds, 100, rpm );
    Drivetrain.setDriveVelocity(VERY_SLOW_SPEED, rpm);
    Drivetrain.drive(forward);
    task::sleep(1000);
    Drivetrain.stop();
    Drivetrain.turnFor(45, degrees);
    Drivetrain.drive(forward);
    task::sleep(1000);
    Drivetrain.stop();
    lift(-50);
    drop();
    Drivetrain.driveFor(-10, inches);
}

void blue_right_tower() {
    // Drive forward to first green cube
    Drivetrain.driveFor(TILE_LENGTH - LENGTH_TO_CLAW, inches);

    // pick it up and move it out of the way
    grab();
    lift(60);
    Drivetrain.turnFor(45, degrees);
    drop();
    Drivetrain.turnFor(-45, degrees);
    lift(-60);

    // drive forward to stack of 4
    Drivetrain.driveFor(TILE_LENGTH, inches);

    // grab
    grab();
    lift(60);

    // tHIS MIGHT NOT WORK
    // turn towards corner
    Drivetrain.turnFor(-135, degrees);
    Drivetrain.driveFor(TILE_LENGTH * sqrt(2), inches);

    // try to align with corner
    Drivetrain.setDriveVelocity(VERY_SLOW_SPEED, rpm);
    Drivetrain.drive(forward);
    task::sleep(2000);
    Drivetrain.stop();

    // drop
    lift(-50);
    drop();

    Drivetrain.driveFor(-10, inches);
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
    task::sleep(1000);
    Claw.stop();
}

void drop() {
    Claw.spin(forward);
    task::sleep(1000);
    Claw.stop();
}

void lift(int deg) {
    ShaftLeft.spinFor(deg, degrees);
    ShaftRight.spinFor(deg, degrees);
}

// void turn(int deg) {
//     const double WHEELBASE_RAD = 13.25 * sqrt(2);
//     double radians = deg * 3.14159 / 180.0;
//     double distance = WHEELBASE_RAD * deg;
//     LeftDriveSmart.spinFor(distance, degrees, false);
//     RightDriveSmart.spinFor(-distance, degrees, false);
// }