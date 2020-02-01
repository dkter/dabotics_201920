#include "auto.h"
#include "robot-config.h"
#include "vex.h"
#include "VisionSensor.h"

constexpr float ROBOT_LENGTH = 18;
constexpr float CUBE_WIDTH = 5.5;
constexpr float LENGTH_TO_CLAW = ROBOT_LENGTH - (CUBE_WIDTH / 2);
constexpr float TILE_LENGTH = 24;
constexpr float CUBE_HEIGHT_DEG = 100;
constexpr int VERY_SLOW_SPEED = 25; //rpm

void autonomous() {
    far_right_1(Alliance::red);
}

void left4(Alliance alliance) {
    // go to cube and drop cube on top
    grab();
    lift(CUBE_HEIGHT_DEG, false);
    Drivetrain.driveFor(0, degrees, TILE_LENGTH + 2*CUBE_WIDTH - ROBOT_LENGTH, inches);
    drop();
    lift(-CUBE_HEIGHT_DEG);

    // grab new stack of 2
    Drivetrain.driveFor(180, degrees, 0.5, inches);
    grab();
    lift(60, false);

    // go backwards
    Drivetrain.driveFor(180, degrees, 11, inches);
    if (alliance == Alliance::blue) {
        Drivetrain.turnFor(left, 90, degrees);
    }
    else if (alliance == Alliance::red) {
        Drivetrain.turnFor(right, 90, degrees);
    }

    // go towards corner
    Drivetrain.driveFor(0, degrees, 6, inches);

    // get right up at corner
    if (alliance == Alliance::blue)
        Drivetrain.turnFor(left, 45, degrees);
    else if (alliance == Alliance::red)
        Drivetrain.turnFor(right, 45, degrees);
    Drivetrain.drive(0, degrees);
    task::sleep(2000);
    lift(-50);
    Drivetrain.stop(); // TODO implement holding mode if this doesn't work

    // drop
    drop();
    lift(180);

    // push back
    Drivetrain.driveFor(180, degrees, 3, inches);
    lift(-150);
    grab();
    Drivetrain.driveFor(0, degrees, 3, inches);
    drop();
    Drivetrain.driveFor(180, degrees, 10, inches);
}

void left4_pickup3(Alliance alliance) {
    // go to cube and drop cube on top
    grab();
    lift(CUBE_HEIGHT_DEG, false);
    Drivetrain.driveFor(0, degrees, TILE_LENGTH + 2*CUBE_WIDTH - ROBOT_LENGTH, inches);
    drop();
    lift(-CUBE_HEIGHT_DEG);

    // grab new stack of 2
    grab();
    lift(CUBE_HEIGHT_DEG);

    // go forward and put on top of other cube
    Drivetrain.driveFor(0, degrees, CUBE_WIDTH, inches);
    drop();
    lift(-CUBE_HEIGHT_DEG);
    grab();
    lift(60, false);

    // go backwards
    Drivetrain.driveFor(180, degrees, 11 + CUBE_WIDTH, inches);
    if (alliance == Alliance::blue) {
        Drivetrain.turnFor(left, 90, degrees);
    }
    else if (alliance == Alliance::red) {
        Drivetrain.turnFor(right, 90, degrees);
    }

    // go towards corner
    Drivetrain.setDriveVelocity(VERY_SLOW_SPEED, rpm);
    Drivetrain.drive(0, degrees);
    task::sleep(2000);
    Drivetrain.stop();

    // get right up at corner
    if (alliance == Alliance::blue)
        Drivetrain.turnFor(left, 45, degrees);
    else if (alliance == Alliance::red)
        Drivetrain.turnFor(right, 45, degrees);
    Drivetrain.drive(0, degrees);
    task::sleep(3000);
    Drivetrain.stop();

    // drop
    lift(-50);
    drop();
    lift(270);
    Drivetrain.driveFor(180, degrees, 10, inches);
}

void far_right_1(Alliance alliance) {
    // go to cube and drop cube on top
    grab();
    lift(CUBE_HEIGHT_DEG, false);
    Drivetrain.driveFor(0, degrees, TILE_LENGTH - LENGTH_TO_CLAW + 1.5, inches);
    drop();
    lift(-CUBE_HEIGHT_DEG);

    // grab stack of 2
    Drivetrain.driveFor(180, degrees, 1, inches);
    grab();
    lift(60);

    // drive forward a bit
    Drivetrain.driveFor(0, degrees, 10, inches);

    // turn towards corner and drive forward
    if (alliance == Alliance::blue)
        Drivetrain.turnFor(right, 135, degrees);
    else if (alliance == Alliance::red)
        Drivetrain.turnFor(left, 135, degrees);
    Drivetrain.driveFor(0, degrees, 10, inches);

    Drivetrain.setDriveVelocity(VERY_SLOW_SPEED, rpm);
    Drivetrain.drive(0, degrees);
    task::sleep(2400);
    Drivetrain.stop();

    // drop cubes
    lift(-50);
    drop();
    lift(120);

    Drivetrain.driveFor(180, degrees, 10, inches);
}

void just_drop_cube(Alliance alliance) {
    // pick up cube
    grab();
    lift(60);

    // move forward extremely slowly
    Drivetrain.setDriveVelocity(VERY_SLOW_SPEED, rpm);
    Drivetrain.drive(0, degrees);
    task::sleep(1000);
    Drivetrain.stop();

    if (alliance == Alliance::blue)
        Drivetrain.turnFor(left, 45, degrees);
    else if (alliance == Alliance::red)
        Drivetrain.turnFor(right, 45, degrees);
    Drivetrain.drive(0, degrees);
    lift(-50, false);
    task::sleep(2500);
    Drivetrain.stop();

    // drop cube
    drop();
    Drivetrain.driveFor(180, degrees, 20, inches);
}

void blue_right_tower() {
    // Drive forward to first green cube
    Drivetrain.driveFor(0, degrees, TILE_LENGTH - LENGTH_TO_CLAW, inches);

    // pick it up and move it out of the way
    grab();
    lift(60);
    Drivetrain.turnFor(right, 45, degrees);
    drop();
    Drivetrain.turnFor(left, 45, degrees);
    lift(-60);

    // drive forward to stack of 4
    Drivetrain.driveFor(0, degrees, TILE_LENGTH, inches);

    // grab
    grab();
    lift(60);

    // tHIS MIGHT NOT WORK
    // turn towards corner
    Drivetrain.turnFor(left, 135, degrees);
    Drivetrain.driveFor(0, degrees, TILE_LENGTH * sqrt(2), inches);

    // try to align with corner
    Drivetrain.setDriveVelocity(VERY_SLOW_SPEED, rpm);
    Drivetrain.drive(0, degrees);
    task::sleep(2000);
    Drivetrain.stop();

    // drop
    lift(-50);
    drop();

    Drivetrain.driveFor(180, degrees, 10, inches);
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
                Drivetrain.driveFor(-90, degrees, 1, inches);
            }
            else {
                // go right
                Brain.Screen.print("Right");
                Drivetrain.driveFor(90, degrees, 1, inches);
            }
        }
    } while (abs(difference) > TOLERANCE);
}

void grab() {
    Claw.spin(reverse);
    task::sleep(1000);
    //Claw.stop();
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
    LiftL.spinFor(deg, degrees, false);
    LiftR.spinFor(deg, degrees, waitForCompletion);
}