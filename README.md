# OdomDebug
Display the robot on a VEX field using information from Okapilib odometry and LVGL.

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
Download <a href="https://github.com/theol0403/odomDebug/raw/master/odomDebug%401.0.0.zip" target="_blank">`odomDebug@1.0.0.zip`</a> from the repository and then fetch into PROS as above.

## Use as Standalone Project
You can also use this repository as a standalone project and run it directly on the robot.
Build by running `prosv5 make`.

`src/opcontrol.cpp` contains an example program.

# Use
Include the header into your file:
`#include "odomDebug/odomDebug.hpp"`

Initialize your chassis:
```cpp
auto chassis = ChassisControllerBuilder()
.withMotors(1, -2)
.withDimensions({{4_in, 11_in}, imev5GreenTPR})
.withOdometry()
.buildOdometry();
```
Initialize the debugger
```cpp
OdomDebug display(lv_scr_act(), LV_COLOR_ORANGE, chassis);
```
You can then run any operator control code and watch the display update.
