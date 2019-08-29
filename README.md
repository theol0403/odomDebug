# OdomDebug
Display the robot on a VEX field using odometry and LVGL.

![odomDebug](https://github.com/theol0403/odomDebug/raw/master/odomDebug.png)

# Installation
## Use in External Project
### Building
To build, clone the repository and run `prosv5 make template`.

Then run `prosv5 c fetch <template>` to import the package into PROS.

Finally, run `prosv5 c apply odomDebug --force-apply` in your destination project to install the package.

You can now use odomDebug in your project.

### Use Pre-built Package
Instead of building the project yourself you can use a pre-built package to use in your external project.
Download <a href="https://github.com/theol0403/odomDebug/raw/master/odomDebug%401.1.0.zip" target="_blank">`odomDebug@1.1.0.zip`</a> from the repository and then fetch into PROS as described above.

## Use as Standalone Project
You can also use this repository as a standalone project and run it directly on the robot.
Build by running `prosv5 make`.

There is an example program in `src/opcontrol.cpp`. You will have to provide your own odometry.

# Use
Include the header into your file:
`#include "odomDebug/odomDebug.hpp"`

OdomDebug needs you to make two callback functions. The first function is for when a tile is pressed, and should set the odometry position to the given coordenates. The second function is for when the reset button is pressed on the screen, and should reset your robot's encoders and odometry. Here is the template:

```cpp
void setState(OdomDebug::state_t state) {
	// set your odometry position to these cartesian coordenates
	// to access the values, call `state.x`, `state.y`, and `state.theta`
	// to convert the QUnits to doubles, call
	// `state.x.convert(inch)` or `state.theta.convert(radian)`
	// you can use any length or angle unit
	// example commands:
	odomSetPosition(state.x, state.y, state.theta);
	odomSetPosition(state.x.convert(inch), state.y.convert(inch), state.theta.convert(radian));
}

void resetSensors() {
	// reset sensors and reset odometry
	// example commands:
	odomResetSensors();
	odomSetPosition(0, 0, 0);
}
```

Then, initialize the debugger
```cpp
OdomDebug display(lv_scr_act(), LV_COLOR_ORANGE);
```

You then need to register your callback functions:
```cpp
display.setStateCallback(setState);
display.setResetCallback(resetSensors);
```

To update the robot's position on the screen, you need to call `setData` in a loop. The syntax to do so is `display.setData({x, y, theta}, {left, right, middle});`
Here are a few examples:
```cpp
display.setData({0_in, 0_in, 0_deg}, {0, 0, 0}); // QUnits used for state
display.setData({0, 0, 0}, {0, 0}); // middle sensor ommited
```
You can give the state QUnits, or you can give it numbers in these units: inch, inch, radian.
The last middle sensor paramiter is optional.

The complete example of use is in `opcontrol.cpp`
