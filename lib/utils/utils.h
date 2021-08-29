#ifndef utils_h
#define utils_h

#include <Arduino.h>

#include <Wire.h>
#include <VL53L0X.h>

class Utils {
  protected:
    int _m1, _m2, _m3, _m4;
    double _e1, _e2;
    char _ir1, _ir2, _ir3, _ir4, _ir5;
    int _shut_1, _shut_2, _shut_3, _shut_4;
    int countCurves;
    float _dist1, _dist2, _dist3, _dist4;
    
  public:
    Utils(
      int m1, int m2, int m3, int m4, 
      int e1, int e2,
      char ir1, char ir2, char ir3, char ir4, char ir5,
      int shut_1, int shut_2, int shut_3, int shut_4);
      
    void sensorInit ();
    void getDist (int sensor);
    int followLine ();
    void moveRobot (int moveType, int speed);
    void returnBase ();
};

#endif
