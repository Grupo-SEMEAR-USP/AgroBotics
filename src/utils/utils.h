#ifndef utils_h
#define utils_h

#include <Arduino.h>

class Utils {
  protected:
    int _m1, _m2, _m3, _m4;
    double _e1, _e2;
  public:
    Utils(int m1, int m2, int m3, int m4);
    void followLine ();
}

#endif