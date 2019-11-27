using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor LeftDriveSmart;
extern motor RightDriveSmart;
extern drivetrain Drivetrain;
extern motor ShaftRight;
extern motor ShaftLeft;
extern motor CenterWheel;
extern signature Vision7__SIG_1;
extern signature Vision7__SIG_2;
extern signature Vision7__SIG_3;
extern signature Vision7__SIG_4;
extern signature Vision7__SIG_5;
extern signature Vision7__SIG_6;
extern signature Vision7__SIG_7;
extern vision Vision7;
extern motor Claw;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );