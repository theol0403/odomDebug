#include "main.h"
#include "odomDebug/odomDebug.hpp"

void setState(OdomDebug::state_t state) {
	// set your odometry position to these cartesian coordenates
	// to access the values, call `state.x`, `state.y`, and `state.theta`
	// to convert the QUnits to doubles, call
	// `state.x.convert(inch)` or `state.theta.convert(radian)`
	// you can use any length or angle unit
	// example commands:
	// odomSetPosition(state.x, state.y, state.theta);
	// odomSetPosition(state.x.convert(inch), state.y.convert(inch), state.theta.convert(radian));
}

void resetSensors() {
	// reset sensors and reset odometry
	// example commands:
	// odomResetSensors();
	// odomSetPosition(0, 0, 0);
}

void opcontrol() {

	OdomDebug display(lv_scr_act(), LV_COLOR_ORANGE);
	display.setStateCallback(setState);
	display.setResetCallback(resetSensors);

	while(true) {

   	// set your odometry data here (position and sensor data)
   	// you can use QUnits for the x, y, and theta,
   	// or you can use doubles, in inches and radians
    // the last `middle` paramiter is optional, depending on your robot
    // display.setData({x, y, theta}, {left, right, middle});
    
    // display.setData({0, 0, 0}, {0, 0});
    // display.setData({0_in, 0_in, 0_deg}, {0, 0, 0});

    pros::delay(20);
  }

}
