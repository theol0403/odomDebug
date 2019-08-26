#pragma once
#include "main.h"

class OdomDebug {

public:

  lv_obj_t* container = nullptr; // lvgl parent container

  lv_obj_t* field = nullptr; // lvgl field container
  double fieldDim = 0; // width/height of field container

  /**
   * @brief  Constructs the OdomDebug object.
   * @param  parent   The lvgl parent, inherits color
   * @param  tracker  The okapi OdomChassisController
   */
  OdomDebug(lv_obj_t* parent);

  /**
   * @brief  Constructs the OdomDebug object.
   * @param  parent    The lvgl parent
   * @param  mainColor  The main color for the display
   * @param  tracker    The okapi OdomChassisController
   */
  OdomDebug(lv_obj_t* pqarent, lv_color_t mainColor);

  ~OdomDebug();

  static lv_res_t tileAction(lv_obj_t*); // action when tile is pressed
  static lv_res_t resetAction(lv_obj_t*); // action when reset button is pressed
  
};

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