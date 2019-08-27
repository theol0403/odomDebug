#include "odomDebug.hpp"

/**
 * Okapi units that represent a tile (2ft) and a court(12ft)
 * Literals are `_tl` and `_crt`, respectivly
 */
namespace okapi {
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
}

/**
 * Constructs the OdomDebug object.
 * @param parent the lvgl parent, color is inherited
 */
OdomDebug::OdomDebug(lv_obj_t* parent) 
: OdomDebug(parent, lv_obj_get_style(parent)->body.main_color) {}

/**
 * Constructs the OdomDebug object.
 * @param parent the lvgl parent
 * @param mainColor The main color for the display
 */
OdomDebug::OdomDebug(lv_obj_t* parent, lv_color_t mainColor) 
: container(lv_obj_create(parent, NULL)) {

  lv_obj_set_size(container, lv_obj_get_width(parent), lv_obj_get_height(parent));
  lv_obj_align(container, NULL, LV_ALIGN_CENTER, 0, 0);

  /**
   * Container Style
   */
  lv_style_copy(&cStyle, &lv_style_plain_color);
  cStyle.body.main_color = mainColor;
  cStyle.body.grad_color = mainColor;
  cStyle.body.border.width = 0;
  cStyle.body.radius = 0;
  lv_obj_set_style(container, &cStyle);

  /**
  * Field
  */
  lv_obj_t* field = lv_obj_create(container, NULL);
  fieldDim = std::min(lv_obj_get_width(container), lv_obj_get_height(container));
  lv_obj_set_size(field, fieldDim, fieldDim);
  lv_obj_align(field, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);

  /**
   * Field Style
   */
  lv_style_copy(&fStyle, &cStyle);
  fStyle.body.main_color = LV_COLOR_WHITE;
  fStyle.body.grad_color = LV_COLOR_WHITE;
  lv_obj_set_style(field, &fStyle);

  /**
   * Tile Styles
   */
  lv_style_copy(&grey, &lv_style_plain);
  grey.body.main_color = LV_COLOR_HEX(0x828F8F);
  grey.body.grad_color = LV_COLOR_HEX(0x828F8F);
  grey.body.border.width = 1;
  grey.body.radius = 0;
  grey.body.border.color = LV_COLOR_WHITE;

  lv_style_copy(&red, &grey);
  red.body.main_color = LV_COLOR_HEX(0xD42630);
  red.body.grad_color = LV_COLOR_HEX(0xD42630);
  lv_style_copy(&blue, &grey);
  blue.body.main_color = LV_COLOR_HEX(0x0077C9);
  blue.body.grad_color = LV_COLOR_HEX(0x0077C9);

  /**
   * Tile Layout
   */
  std::vector<std::vector<lv_style_t*>> tileData = {
    {&grey, &grey, &grey, &grey, &grey, &grey},
    {&grey, &grey, &grey, &grey, &grey, &grey},
    {&red , &grey, &grey, &grey, &grey, &blue},
    {&grey, &grey, &grey, &grey, &grey, &grey},
    {&red , &grey, &grey, &grey, &grey, &blue},
    {&grey, &grey, &grey, &grey, &grey, &grey}
  };

  double tileDim = fieldDim / tileData.size(); // tile dimention

  /**
   * Create tile matrix, register callbacks, assign each tile an ID
   */
  for(double y = 0; y < 6; y++) {
    for(double x = 0; x < 6; x++) {
      lv_obj_t* tileObj = lv_btn_create(field, NULL);
      lv_obj_set_pos(tileObj, x * tileDim, y * tileDim);
      lv_obj_set_size(tileObj, tileDim, tileDim);
      lv_btn_set_action(tileObj, LV_BTN_ACTION_CLICK, tileAction);
      lv_obj_set_free_num(tileObj, y * 6 + x);
      lv_obj_set_free_ptr(tileObj, this);
      lv_btn_set_toggle(tileObj, false);
      lv_btn_set_style(tileObj, LV_BTN_STYLE_PR, tileData[y][x]);
      lv_btn_set_style(tileObj, LV_BTN_STYLE_REL, tileData[y][x]);
    }
  }

  /**
   * Robot point using lvgl led
   */
  led = lv_led_create(field, NULL);
  lv_led_on(led);
  lv_obj_set_size(led, fieldDim / 15, fieldDim / 15);

  lv_style_copy(&ledStyle, &lv_style_plain);
  ledStyle.body.radius = LV_RADIUS_CIRCLE;
  ledStyle.body.main_color = mainColor;
  ledStyle.body.grad_color = mainColor;
  ledStyle.body.border.color = LV_COLOR_WHITE;
  ledStyle.body.border.width = 2;
  ledStyle.body.border.opa = LV_OPA_100;
  lv_obj_set_style(led, &ledStyle);
  

  /**
   * Robot line
   */
  line = lv_line_create(field, NULL);
  lv_line_set_points(line, linePoints.data(), linePoints.size());
  lv_obj_set_pos(line, 0, 0);

  lineWidth = 3;
  lineLength = fieldDim / 6;

  lv_style_copy(&lineStyle, &lv_style_plain);
  lineStyle.line.width = 3;
  lineStyle.line.opa = LV_OPA_100;
  lineStyle.line.color = mainColor;
  lv_obj_set_style(line, &lineStyle);
  
  /**
   * Status Label
   */
  lv_obj_t* statusLabel = lv_label_create(container, NULL);
  lv_style_copy(&textStyle, &lv_style_plain);
  textStyle.text.color = LV_COLOR_WHITE;
  textStyle.text.opa = LV_OPA_100;
  lv_obj_set_style(statusLabel, &textStyle);

  /**
  * Reset Button
  */
  {
    lv_obj_t* btn = lv_btn_create(container, NULL);
    lv_obj_set_size(btn, 100, 40);
    lv_obj_align(btn, NULL, LV_ALIGN_IN_TOP_MID, -lv_obj_get_width(container)/2 + (lv_obj_get_width(container) - fieldDim)/2, 0);
    lv_obj_set_free_ptr(btn, this);
    lv_btn_set_action(btn, LV_BTN_ACTION_PR, resetAction);

    /**
     * Button Style
     */
    lv_style_copy(&resetRel, &lv_style_btn_tgl_rel);
    resetRel.body.main_color = mainColor;
    resetRel.body.grad_color = mainColor;
    resetRel.body.border.color = LV_COLOR_WHITE;
    resetRel.body.border.width = 2;
    resetRel.body.border.opa = LV_OPA_100;
    resetRel.body.radius = 2;
    resetRel.text.color = LV_COLOR_WHITE;

    lv_style_copy(&resetPr, &resetRel);
    resetPr.body.main_color = LV_COLOR_WHITE;
    resetPr.body.grad_color = LV_COLOR_WHITE;
    resetPr.text.color = mainColor;

    lv_btn_set_style(btn, LV_BTN_STYLE_REL, &resetRel);
    lv_btn_set_style(btn, LV_BTN_STYLE_PR, &resetPr);

    /**
    * Reset Button Label
    */
    lv_obj_t* label = lv_label_create(btn, NULL);
    lv_obj_set_style(label, &textStyle);
    lv_label_set_text(label, "Reset");
  }

}

OdomDebug::~OdomDebug() {
  lv_obj_del(container);
}


/**
 * Sets the function to be called when a tile is pressed
 * @param callback a function that sets the odometry state
 */
void OdomDebug::setStateCallback(std::function<void(QLength x, QLength y, QAngle theta)> callback) {
  stateCallback = callback;
}

/**
 * Sets the function to be called when the reset button is pressed
 * @param callback a function that resets the odometry and sensors
 */
void OdomDebug::setResetCallback(std::function<void()> callback) {
  resetCallback = callback;
}

/**
 * Sets the position of the robot in QUnits
 * @param x     
 * @param y     
 * @param theta 
 */
void OdomDebug::setPosition(QLength ix, QLength iy, QAngle itheta) {
  double x = ix.convert(court);
  double y = (1_crt - iy).convert(court);
  double theta = itheta.convert(radian);

  // place point on field
  lv_obj_set_pos(led, (x * fieldDim) - lv_obj_get_width(led)/2, (y * fieldDim) - lv_obj_get_height(led)/2 - 1);

  // move start and end of line
  linePoints[0] = {(int16_t)((x * fieldDim)), (int16_t)((y * fieldDim) - (lineWidth/2))};
  double newY = lineLength * cos(theta);
  double newX = lineLength * sin(theta);
  linePoints[1] = {(int16_t)(newX + linePoints[0].x), (int16_t)(-newY + linePoints[0].y)};

  lv_line_set_points(line, linePoints.data(), linePoints.size());
  lv_obj_invalidate(line);
}

/**
 * Sets the position of the robot
 * @param x     inches
 * @param y     inches
 * @param theta radians
 */
void OdomDebug::setPosition(double ix, double iy, double itheta) {
  setPosition(ix * inch, iy * inch, itheta * radian);
}

/**
 * Sets the encoder values to the display
 * @param left  the left encoder value
 * @param right the right encoder value
 */
void OdomDebug::setSensorValues(double left, double right) {

}

/**
 * Sets the encoder values to the display
 * @param left   the left encoder value
 * @param right  the right encoder value
 * @param middle the middle encoder value
 */
void OdomDebug::setSensorValues(double left, double right, double middle) {

}

/**
 * Sets odom state when tile is pressed
 * Decodes tile ID to find position
 */
lv_res_t OdomDebug::tileAction(lv_obj_t* tileObj) {
  // OdomDebug* that = static_cast<OdomDebug*>(lv_obj_get_free_ptr(tileObj));
  // int num = lv_obj_get_free_num(tileObj);
  // int y = num / 6;
  // int x = num - y * 6;
  // that->tracker->setState({x * tile + 0.5_tl, 1_crt - y * tile - 0.5_tl, 0_deg}, StateMode::CARTESIAN);
  // return LV_RES_OK;
}

/**
 * Reset Sensors and Position
 */
lv_res_t OdomDebug::resetAction(lv_obj_t* btn) {
  // OdomDebug* that = static_cast<OdomDebug*>(lv_obj_get_free_ptr(btn));
  // that->tracker->resetSensors();
  // that->tracker->setState({0_in, 0_in});
  // return LV_RES_OK;
}


/**
 * Main Processing Loop
 */
// void OdomDebug::run() {




//   while(true) {

//     // get robot position


//     // assign labels
//     std::string text =
//     "X: " + std::to_string(tracker->getState(StateMode::CARTESIAN).x.convert(foot)) + "\n" +
//     "Y: " + std::to_string(tracker->getState(StateMode::CARTESIAN).y.convert(foot)) + "\n" +
//     "Theta: " + std::to_string(tracker->getState(StateMode::CARTESIAN).theta.convert(degree)) + "\n" +
//     "Left: " + std::to_string(tracker->getSensorVals()[0]) + "\n" +
//     "Right: " + std::to_string(tracker->getSensorVals()[1]);
//     lv_label_set_text(label, text.c_str());
//     lv_obj_align(label, container, LV_ALIGN_CENTER, -lv_obj_get_width(container)/2 + (lv_obj_get_width(container) - fieldDim)/2, 0);

//     pros::delay(50);
//   }

// }


// void OdomDebug::taskFnc(void* input) {
//   pros::delay(500);
//   OdomDebug* that = static_cast<OdomDebug*>(input);
//   that->run();
// }
