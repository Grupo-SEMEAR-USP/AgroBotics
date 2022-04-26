#ifndef utils_h
#define utils_h

#include <Arduino.h>

#include <Wire.h>
#include <VL53L0X.h>

class Utils {
  protected:
    int _m1_1, _m1_2, _m2_1, _m2_2, _m3_1, _m3_2, _m4_1, _m4_2;
    int _e1, _e2, _e3, _e4;
    int _ir1, _ir2, _ir3, _ir4, _ir5;
    int _shut_1, _shut_2, _shut_3, _shut_4;
    int countCurves;
    float _dist1, _dist2, _dist3, _dist4;
    
  public:
    Utils(
      int m1_1, int m1_2 ,int m2_1, int m2_2,int m3_1, int m3_2, int m4_1, int m4_2,
      int e1, int e2, int e3, int e4,
      int ir1, int ir2, int ir3, int ir4, int ir5);
      
    void sensorInit ();
    void getDist (int sensor);
    int followLine ();
    void moveRobot (int moveType, int speed);
    void returnBase ();
};

#endif
