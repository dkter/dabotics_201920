// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    20, 11          
// ShaftRight           motor         3               
// ShaftLeft            motor         10              
// CenterWheel          motor         16              
// Vision7              vision        7               
// Claw                 motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    20, 11          
// ShaftRight           motor         3               
// ShaftLeft            motor         2               
// CenterWheel          motor         16              
// Vision7              vision        7               
// Claw                 motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    20, 11          
// ShaftRight           motor         3               
// ShaftLeft            motor         4               
// CenterWheel          motor         16              
// Vision7              vision        7               
// Claw                 motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    20, 11          
// ShaftRight           motor         3               
// ShaftLeft            motor         2               
// CenterWheel          motor         16              
// Vision7              vision        7               
// Claw                 motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    20, 11          
// ShaftRight           motor         3               
// ShaftLeft            motor         10              
// CenterWheel          motor         16              
// Vision7              vision        7               
// Claw                 motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\me                                               */
/*    Created:      Fri Nov 22 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Claw                 motor         1               
// Drivetrain           drivetrain    20, 11          
// ShaftRight          motor         2               
// ShaftLeft           motor         10              
// CenterWheel          motor         16              
// Vision7              vision        7               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "auto.h"
#include "main.h"

using namespace vex;

competition Competition;

int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();
    
    ShaftLeft.setStopping(hold);
    ShaftRight.setStopping(hold);
    Claw.setStopping(hold);

    Competition.autonomous(autonomous);
    Competition.drivercontrol(selfControl);
}

void selfControl(){
    int shaftSpeed = 50;
    int clawSpeed = 50;
    int preciseSub = 40;
    int visionWidth = 316;
    int offset = 20;

    int p = 0;

    while (true){
        // Precision hold
        if (Controller1.ButtonA.pressing()){
            p = 0;
        }
        else{
            p = preciseSub;
        }

        // Shaft control
        if (Controller1.ButtonUp.pressing()){
            ShaftLeft.spin(forward, shaftSpeed - p, percent);
            ShaftRight.spin(forward, shaftSpeed - p, percent);
        }
        else if (Controller1.ButtonDown.pressing()){
            ShaftLeft.spin(reverse, shaftSpeed - p, percent);
            ShaftRight.spin(reverse, shaftSpeed - p, percent);
        }
        else {
            ShaftLeft.stop();
            ShaftRight.stop();
        }

        // Claw control
        if (Controller1.ButtonL2.pressing()){
            Claw.spin(forward, clawSpeed - p, percent);
        }
        else if (Controller1.ButtonR2.pressing()){
            Claw.spin(reverse, clawSpeed - p, percent);
        }
        else {
            Claw.stop();
        }

        // Center wheel control
        if (Controller1.Axis4.position() < 0){
            CenterWheel.spin(forward, Controller1.Axis4.position(percent) - p, percent);
        }
        else if (Controller1.Axis4.position() > 0) {
            CenterWheel.spin(forward, Controller1.Axis4.position(percent) + p, percent);
        } 
        else {
            CenterWheel.setVelocity(0, percent);
        }

        if (Controller1.ButtonB.pressing()) {align(visionWidth, offset);}
    }
}

// Green must be set up
void align(int visionWidth, int offset){

    double sprintTime = 0.5;

    Vision7.takeSnapshot(Vision7__SIG_1);

    if (Vision7.objects[0].centerX > (visionWidth/2 + offset)){
        CenterWheel.spin(reverse, 30, percent);
        wait(sprintTime, seconds);
        CenterWheel.stop();
    } 
    else if (Vision7.objects[0].centerX < (visionWidth/2 - offset)){
        CenterWheel.spin(forward, 30, percent);
        wait(sprintTime, seconds);
        CenterWheel.stop();
    }

}