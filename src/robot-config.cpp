#include "vex.h"
#include "XDrivetrain.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor FrontLeftWheel = motor(PORT3, ratio18_1, false);
motor FrontRightWheel = motor(PORT7, ratio18_1, false);
motor BackLeftWheel = motor(PORT5, ratio18_1, true);
motor BackRightWheel = motor(PORT6, ratio18_1, true);
XDrivetrain Drivetrain = XDrivetrain(FrontLeftWheel, FrontRightWheel, BackLeftWheel, BackRightWheel, 8.5, 14, 4);

/*vex-vision-config:begin*/
signature Vision7__SIG_1 = signature (1, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision7__SIG_2 = signature (2, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision7__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision7__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision7__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision7__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision7__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision Vision7 = vision (PORT7, 50, Vision7__SIG_1, Vision7__SIG_2, Vision7__SIG_3, Vision7__SIG_4, Vision7__SIG_5, Vision7__SIG_6, Vision7__SIG_7);
/*vex-vision-config:end*/
motor Claw = motor(PORT4, ratio18_1, false);
motor LiftL = motor(PORT11, ratio36_1, false);
motor LiftL2 = motor(PORT13, ratio18_1, false);
motor LiftR = motor(PORT12, ratio36_1, true);


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
}