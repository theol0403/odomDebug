#include "main.h"
#include "odomDebug/odomDebug.hpp"

/**
* Runs the operator control code. This function will be started in its own task
* with the default priority and stack size whenever the robot is enabled via
* the Field Management System or the VEX Competition Switch in the operator
* control mode.
*
* If no competition control is connected, this function will run immediately
* following initialize().
*
* If the robot is disabled or communications is lost, the
* operator control task will be stopped. Re-enabling the robot will restart the
* task, not resume it from where it left off.
*/
void opcontrol() {

 auto chassis = ChassisControllerBuilder()
 .withMotors(1, -2)
 .withDimensions({{4_in, 11_in}, imev5RedTPR})
 .withMaxVelocity(50)
 .withOdometry()
 .buildOdometry();

 OdomDebug display(lv_scr_act(), LV_COLOR_ORANGE, chassis);

 // chassis->moveDistance(1_ft);
 // chassis->turnAngle(4.0/11.0 * 360.0 * degree);
 //arcade code goes here
 pros::delay(40000000);

}
