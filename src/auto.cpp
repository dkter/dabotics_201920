#include "auto.h"
#include "vex.h"
#include "VisionSensor.h"

constexpr float ROBOT_LENGTH = 18;
constexpr float CUBE_WIDTH = 5.5;
constexpr float LENGTH_TO_CLAW = ROBOT_LENGTH - (CUBE_WIDTH / 2);
constexpr float TILE_LENGTH = 24;
constexpr float CUBE_HEIGHT_DEG = 75;
constexpr int VERY_SLOW_SPEED = 25; //rpm

void autonomous() {
    left4(Alliance::blue);
}

void left4(Alliance alliance) {
    // go to cube and drop cube on top
    grab();
    lift(CUBE_HEIGHT_DEG, false);
    Drivetrain.driveFor(16, inches);
    drop();
    lift(-CUBE_HEIGHT_DEG);

    // grab new stack of 2
    grab();
    lift(60, false);

    // go backwards
    Drivetrain.driveFor(-12, inches);
    if (alliance == Alliance::blue) {
        Drivetrain.turnFor(-90, degrees);
    }
    else if (alliance == Alliance::red) {
        Drivetrain.turnFor(90, degrees);
    }

    // go towards corner
    Drivetrain.setDriveVelocity(VERY_SLOW_SPEED, rpm);
    Drivetrain.drive(forward);
    task::sleep(2000);
    Drivetrain.stop();

    // drop
    lift(-50);
    drop();
    Drivetrain.driveFor(-10, inches);
}

void left4_pickup3(Alliance alliance) {
    // go to cube and drop cube on top
    grab();
    lift(CUBE_HEIGHT_DEG, false);
    Drivetrain.driveFor(16, inches);
    drop();
    lift(-CUBE_HEIGHT_DEG);

    // grab new stack of 2
    grab();
    lift(CUBE_HEIGHT_DEG, false);

    // go forward and put on top of other cube
    Drivetrain.driveFor(CUBE_WIDTH, inches);
    drop();
    lift(-CUBE_HEIGHT_DEG);
    grab();
    lift(60);

    // go backwards
    Drivetrain.driveFor(-12 - CUBE_WIDTH, inches);
    if (alliance == Alliance::blue) {
        Drivetrain.turnFor(-90, degrees);
    }
    else if (alliance == Alliance::red) {
        Drivetrain.turnFor(90, degrees);
    }

    // go towards corner
    Drivetrain.setDriveVelocity(VERY_SLOW_SPEED, rpm);
    Drivetrain.drive(forward);
    task::sleep(2000);
    Drivetrain.stop();

    // drop
    lift(-50);
    drop();
    Drivetrain.driveFor(-10, inches);
}

void far_right_1(Alliance alliance) {
    // go to cube and drop cube on top
    grab();
    lift(CUBE_HEIGHT_DEG, false);
    Drivetrain.driveFor(TILE_LENGTH - LENGTH_TO_CLAW, inches);
    drop();
    lift(-CUBE_HEIGHT_DEG);

    // grab stack of 2
    grab();
    lift(60);

    // turn towards corner and drive forward
    if (alliance == Alliance::blue)
        Drivetrain.turnFor(-135, degrees);
    else if (alliance == Alliance::red)
        Drivetrain.turnFor(135, degrees);

    Drivetrain.setDriveVelocity(VERY_SLOW_SPEED, rpm);
    Drivetrain.drive(forward);
    task::sleep(2000);
    Drivetrain.stop();

    // drop cubes
    lift(-50);
    drop();

    Drivetrain.driveFor(-10, inches);
}

void just_drop_cube() {
    // pick up cube
    grab();
    lift(60);

    // move forward extremely slowly
    Drivetrain.setDriveVelocity(VERY_SLOW_SPEED, rpm);
    Drivetrain.drive(forward);
    task::sleep(1000);
    Drivetrain.stop();

    // drop cube
    lift(-50);
    drop();
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
    lift(deg, true);
}

void lift(int deg, bool waitForCompletion) {
    ShaftLeft.spinFor(deg, degrees, false);
    ShaftRight.spinFor(deg, degrees, waitForCompletion);
}

// void turn(int deg) {
//     const double WHEELBASE_RAD = 13.25 * sqrt(2);
//     double radians = deg * 3.14159 / 180.0;
//     double distance = WHEELBASE_RAD * deg;
//     LeftDriveSmart.spinFor(distance, degrees, false);
//     RightDriveSmart.spinFor(-distance, degrees, false);
// }
