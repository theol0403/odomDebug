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
  void setPosition(QLength ix, QLength iy, QAngle itheta);

  /**
   * Sets the position of the robot
   * @param x     inches
   * @param y     inches
   * @param theta radians
   */
  void setPosition(double ix, double iy, double itheta);

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

  // parent container
  lv_obj_t* container = nullptr; 
  lv_style_t cStyle;

  // field
  lv_style_t fStyle; 
  double fieldDim = 0; // width and height of field container

  // tile styles
  lv_style_t grey;
  lv_style_t red;
  lv_style_t blue;

  // robot point
  lv_obj_t* led = nullptr; 
  lv_style_t ledStyle;

  // robot line
  lv_obj_t* line = nullptr; 
  lv_style_t lineStyle;
  std::vector<lv_point_t> linePoints = {{0, 0}, {0, 0}}; // lines positions
  int lineWidth = 0;
  int lineLength = 0;

  // status label
  lv_obj_t* statusLabel = nullptr;
  lv_style_t textStyle;

  // reset button styles
  lv_style_t resetRel;
  lv_style_t resetPr;

  // external callbacks to interface with odometry
  std::function<void(QLength x, QLength y, QAngle theta)> stateCallback = nullptr;
  std::function<void()> resetCallback = nullptr;

  static lv_res_t tileAction(lv_obj_t*); // action when tile is pressed
  static lv_res_t resetAction(lv_obj_t*); // action when reset button is pressed

};

