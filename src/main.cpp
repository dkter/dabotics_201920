#include <cmath>
#include <tuple>

#include "vex.h"
#include "auto.h"
#include "main.h"

#include "robot-config.h"

using namespace vex;

competition Competition;

int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();
    
    LiftL.setBrake(hold);
    LiftL2.setBrake(hold);
    LiftR.setBrake(hold);
    Claw.setBrake(hold);
    Claw.setStopping(hold);

    Competition.autonomous(autonomous);
    Competition.drivercontrol(selfControl);
}

void selfControl(){
    int CLAW_ANGLE = 35;

    int visionWidth = 316;
    int offset = 20;

    bool p = false;
    int driveSpeedAdj;
    int liftSpeed;
    int clawSpeed;

    while (true){
        // Precision hold
        p = Controller1.ButtonA.pressing();
        if (p) {
            driveSpeedAdj = 0;
            liftSpeed = 100;
            clawSpeed = 50;
        }
        else {
            driveSpeedAdj = 30;
            liftSpeed = 40;
            clawSpeed = 20;
        }

        // Driving
        double angle;
        double velocity;
        std::tie(angle, velocity) = getJoystickVector();
        velocity *= (100.0 - driveSpeedAdj) / 100.0;
        // Turning
        double turn = Controller1.Axis1.position(percentUnits::pct);
        turn *= (100.0 - driveSpeedAdj) / 100.0;

        // Move robot
        if (velocity) {
            Drivetrain.setDriveVelocity(velocity, velocityUnits::pct);
            Drivetrain.drive(angle);
        } else if (turn) {
            Drivetrain.setTurnVelocity(turn, velocityUnits::pct);
            Drivetrain.turn(turnType::right);
        }
        else {
            Drivetrain.stop();
        }

        // Lift control
        if (Controller1.ButtonUp.pressing()){
            LiftL.spin(forward, liftSpeed, percent);
            LiftL2.spin(forward, liftSpeed, percent);
            LiftR.spin(forward, liftSpeed, percent);
        }
        else if (Controller1.ButtonDown.pressing()){
            LiftL.spin(reverse, liftSpeed, percent);
            LiftL2.spin(reverse, liftSpeed, percent);
            LiftR.spin(reverse, liftSpeed, percent);
        }
        else {
            LiftL.stop();
            LiftL2.stop();
            LiftR.stop();
        }

        // Claw control
        /*
        if (Controller1.ButtonL2.pressing()){
            Claw.spinTo(CLAW_ANGLE, degrees);
            //Claw.spin(forward, 100, percent);
        }
        else if (Controller1.ButtonR2.pressing()){
            Claw.spin(reverse, 100, percent);
        }
        else {
            //Claw.stop(hold);
        }
        */
        // Claw control
        if (Controller1.ButtonL2.pressing()){
            Claw.spin(forward, clawSpeed, percent);
        }
        else if (Controller1.ButtonR2.pressing()){
            Claw.spin(reverse, clawSpeed, percent);
        }
        else {
            Claw.stop();
        }

        if (Controller1.ButtonB.pressing()) {align(visionWidth, offset);}
    }
}

std::tuple<double, double> getJoystickVector() {
    double x = Controller1.Axis4.position(percentUnits::pct);
    double y = Controller1.Axis3.position(percentUnits::pct);
    double angle = atan2(x, y);
    double value = sqrt(x*x + y*y);
    return std::make_tuple(angle, value);
}

// Green must be set up
void align(int visionWidth, int offset){

    double sprintTime = 0.5;

    Vision7.takeSnapshot(Vision7__SIG_1);

    if (Vision7.objects[0].centerX > (visionWidth/2 + offset)){
        Drivetrain.drive(M_PI_2);
        wait(sprintTime, seconds);
        Drivetrain.stop();
    } 
    else if (Vision7.objects[0].centerX < (visionWidth/2 - offset)){
        Drivetrain.drive(-M_PI_2);
        wait(sprintTime, seconds);
        Drivetrain.stop();
    }

}