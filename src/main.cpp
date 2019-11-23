#include "vex.h"
#include "VisionSensor.h"
#include "main.h"


using namespace vex;

motor        LeftMotor(PORT1, gearSetting::ratio18_1, false);
motor        RightMotor(PORT2, gearSetting::ratio18_1, true);
motor        SideMotor(PORT3, gearSetting::ratio18_1, false);
motor        LiftLMotor(PORT4, gearSetting::ratio36_1, true);
motor        LiftRMotor(PORT5, gearSetting::ratio36_1, false);
//drivetrain   Drivetrain = drivetrain(LeftMotor, RightMotor, 319, 295, distanceUnits::mm);
controller   Controller1;

using namespace vex;

double liftPos = 0;

int main() {
  //Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  LiftLMotor.setStopping(brakeType::hold);
  LiftRMotor.setStopping(brakeType::hold);

  while(true) {        
        LeftMotor.spin(directionType::fwd, Controller1.Axis3.value() + Controller1.Axis1.value(), velocityUnits::rpm);
        RightMotor.spin(directionType::fwd, Controller1.Axis3.value() - Controller1.Axis1.value(), velocityUnits::rpm);
        SideMotor.spin(directionType::fwd, Controller1.Axis4.value(), velocityUnits::rpm);
        //LiftLMotor.rotateTo(liftPos, rotationUnits::deg, false);
        //LiftRMotor.rotateTo(liftPos, rotationUnits::deg, false);

        if (Controller1.ButtonUp.pressing()) {
            LiftLMotor.spin(directionType::fwd, 50, velocityUnits::pct);
            LiftRMotor.spin(directionType::fwd, 50, velocityUnits::pct);
        }
        else if (Controller1.ButtonDown.pressing()) {
            LiftLMotor.spin(directionType::rev, 25, velocityUnits::pct);
            LiftRMotor.spin(directionType::rev, 25, velocityUnits::pct);
        }
        else {
            LiftLMotor.stop();
            LiftRMotor.stop();
        }

        VisionSensor.takeSnapshot(GREEN_CUBE);
        if (VisionSensor.largestObject.exists && VisionSensor.largestObject.width > 50) {
            Brain.Screen.setPenColor(vex::color::white);
            Brain.Screen.setFillColor(vex::color::green);
            Brain.Screen.drawRectangle(0,0, 480, 240);
        }
        else {
            VisionSensor.takeSnapshot(ORANGE_CUBE);
            if (VisionSensor.largestObject.exists && VisionSensor.largestObject.width > 50) {
                Brain.Screen.setPenColor(vex::color::white);
                Brain.Screen.setFillColor(vex::color::orange);
                Brain.Screen.drawRectangle(0,0, 480, 240);
            }
            else {
                VisionSensor.takeSnapshot(PURPLE_CUBE);
                if (VisionSensor.largestObject.exists && VisionSensor.largestObject.width > 50) {
                    Brain.Screen.setPenColor(vex::color::white);
                    Brain.Screen.setFillColor(vex::color::purple);
                    Brain.Screen.drawRectangle(0,0, 480, 240);
                }
                else {
                    Brain.Screen.clearScreen();
                }
            }
        }

        task::sleep(100);
    }
}