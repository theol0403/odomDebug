#pragma once
#include "main.h"

class OdomDebug {

public:

  lv_obj_t* container = nullptr;
  std::shared_ptr<OdomChassisController> tracker = nullptr;

  lv_obj_t* field = nullptr;
  double fieldDim = 0;

  pros::Task task;

  OdomDebug(lv_obj_t*, std::shared_ptr<OdomChassisController>);
  OdomDebug(lv_obj_t*, lv_color_t, std::shared_ptr<OdomChassisController>);
  ~OdomDebug();

  static lv_res_t tileAction(lv_obj_t*);
  static lv_res_t resetAction(lv_obj_t*);
  static lv_res_t btnmAction(lv_obj_t*);

  void run();
  static void taskFnc(void*);

};

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