# OdomDebug
Display the robot on a VEX feild using information from Okapilib odometry and LVGL.
## Instalation
### Building for an external project
To build, clone the repository and run `prosv5 make template`.
Then run `prosv5 c fetch <template>` to import the package into PROS.
Finally, run `prosv5 c apply odomDebug --force-apply` in your destination project.
### Using as a standalone project
Build by running `prosv5 make`.
`src/opcontrol.cpp` contains an example test program.
### Use
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
You can then run any operator control code, make sure the scope you created the display in will not exit.