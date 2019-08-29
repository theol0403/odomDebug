#include "main.h"
#include "odomDebug/odomDebug.hpp"


void setState(QLength x, QLength y, QAngle theta) {
	// set these values to your odometry
	// to convert the QUnits to doubles, call
	// `x.convert(inch)` or `theta.convert(radian)`
	// you can use any length or angle unit
}

void resetSensors() {
	// reset sensors
	// reset odometry
}

void opcontrol() {

	OdomDebug display(lv_scr_act(), LV_COLOR_ORANGE);
	display.setStateCallback(setState);
	display.setResetCallback(resetSensors);

	while(true) {

   	// set your odometry data here (position and sensor data)
   	// you can use QUnits for the x, y, and theta
   	// or you can use doubles, in inches and radians
    // the last `middle` paramiter is optional, depending on your robot
    // display.setData(x, y, theta, left, right, middle);
    
    // display.setData(0, 0, 0, 0, 0, 0);
    display.setData({0_in, 0_in, 0_deg}, {0, 0, 0});

    pros::delay(20);
  }

}
