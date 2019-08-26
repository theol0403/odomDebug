#pragma once
#include "main.h"

class OdomDebug {

public:

  /**
   * Constructs the OdomDebug object.
   * @param parent the lvgl parent, color is inherited
   */
  OdomDebug(lv_obj_t* parent);

  /**
   * Constructs the OdomDebug object.
   * @param parent the lvgl parent
   * @param mainColor The main color for the display
   */
  OdomDebug(lv_obj_t* parent, lv_color_t mainColor);

  ~OdomDebug();

  /**
   * Sets the function to be called when a tile is pressed
   * @param callback a function that sets the odometry state
   */
  void setStateCallback(std::function<void(QLength x, QLength y, QAngle theta)> callback);

  /**
   * Sets the function to be called when the reset button is pressed
   * @param callback a function that resets the odometry and sensors
   */
  void setResetCallback(std::function<void()> callback);

  /**
   * Sets the position of the robot in QUnits
   * @param x     
   * @param y     
   * @param theta 
   */
  void setPosition(QLength x, QLength y, QAngle theta);

  /**
   * Sets the position of the robot
   * @param x     inches
   * @param y     inches
   * @param theta radians
   */
  void setPosition(double x, double y, double theta);

  /**
   * Sets the encoder values to the display
   * @param left  the left encoder value
   * @param right the right encoder value
   */
  void setSensorValues(double left, double right);

  /**
   * Sets the encoder values to the display
   * @param left   the left encoder value
   * @param right  the right encoder value
   * @param middle the middle encoder value
   */
  void setSensorValues(double left, double right, double middle);

private:

  lv_obj_t* container = nullptr; // lvgl parent container
  lv_style_t cStyle; // container style

  lv_obj_t* field = nullptr; // lvgl field container
  lv_style_t fStyle; // field style
  double fieldDim = 0; // width and height of field container

  // tile styles
  lv_style_t grey;
  lv_style_t red;
  lv_style_t blue;

  // external callbacks to interface with odometry
  std::function<void(QLength x, QLength y, QAngle theta)> stateCallback = nullptr;
  std::function<void()> resetCallback = nullptr;

  static lv_res_t tileAction(lv_obj_t*); // action when tile is pressed
  static lv_res_t resetAction(lv_obj_t*); // action when reset button is pressed

  /**
   * Okapi units that represent a tile (2ft) and a court(12ft)
   * Literals are `_tl` and `_crt`, respectivly
   */
  constexpr QLength tile = 2 * foot;
  constexpr QLength court = 12 * foot;
  inline namespace literals {
    constexpr QLength operator"" _tl(long double x) {
      return static_cast<double>(x) * tile;
    }
    constexpr QLength operator"" _crt(long double x) {
      return static_cast<double>(x) * court;
    }
    constexpr QLength operator"" _tl(unsigned long long int x) {
      return static_cast<double>(x) * tile;
    }
    constexpr QLength operator"" _crt(unsigned long long int x) {
      return static_cast<double>(x) * court;
    }
  }

};
