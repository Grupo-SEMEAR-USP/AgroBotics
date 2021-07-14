#ifndef utils_h
#define utils_h

#include <Arduino.h>

class Utils {
  protected:
    int _m1, _m2, _m3, _m4;
    double _e1, _e2;
    char _ir1, _ir2, _ir3, _ir4, _ir5;
    int countCurves;
    
  public:
    Utils(
      int m1, int m2, int m3, int m4, 
      int e1, int e2,
      char ir1, char ir2, char ir3, char ir4, char ir5);
      
    int followLine ();
    void moveRobot (int moveType, int speed);
    void returnBase ();
};

#endif
