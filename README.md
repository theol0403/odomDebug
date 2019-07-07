# OdomDebug
Display the robot on a VEX field using information from Okapilib odometry and LVGL.
## Instalation
### Building for External Project
To build, clone the repository and run `prosv5 make template`.

Then run `prosv5 c fetch <template>` to import the package into PROS.

Finally, run `prosv5 c apply odomDebug --force-apply` in your destination project.

You can now use odomDebug in your existing project.

### Use as Standalone Project
Build by running `prosv5 make`.

`src/opcontrol.cpp` contains an example program.

You can upload and test straight from here.

## Use
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