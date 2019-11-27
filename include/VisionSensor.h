/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature GREEN_CUBE = vex::vision::signature (1, -7665, -4477, -6071, -4051, -1627, -2839, 2.6, 0);
vex::vision::signature PURPLE_CUBE = vex::vision::signature (2, 469, 1861, 1165, 3767, 8479, 6123, 2, 0);
vex::vision::signature ORANGE_CUBE = vex::vision::signature (3, 5845, 8139, 6992, -1937, -1069, -1503, 3, 0);
vex::vision::signature JAKOB = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision VisionSensor = vex::vision (vex::PORT6, 48, GREEN_CUBE, PURPLE_CUBE, ORANGE_CUBE, JAKOB, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/