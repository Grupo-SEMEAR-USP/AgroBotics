#include <Arduino.h>

#include "utils.h"

Utils::Utils (
    int m1, int m2, int m3, int m4, 
    int e1, int e2,
    char ir1, char ir2, char ir3, char ir4, char ir5
) 
{
   
    //Motores
    _m1 = m1;
    _m2 = m2;
    _m3 = m3;
    _m4 = m4;

    //Ponte h
    _e1 = e1;
    _e2 = e2;

    //Sensor de linha (IR5)
    _ir1 = ir1;
    _ir2 = ir2;
    _ir3 = ir3;
    _ir4 = ir4;
    _ir5 = ir5;

    //Right side
    pinMode(_m1, OUTPUT);
    pinMode(_m2, OUTPUT);
    pinMode(_e1, OUTPUT);

    //Left side
    pinMode(_m3, OUTPUT);
    pinMode(_m4, OUTPUT);
    pinMode(_e2, OUTPUT);

    //Sensors
    pinMode(_ir1, INPUT);
    pinMode(_ir2, INPUT);
    pinMode(_ir3, INPUT);
    pinMode(_ir4, INPUT);
    pinMode(_ir5, INPUT);

    //AttachPin
    ledcAttachPin(_e1, 0);
    ledcAttachPin(_e2, 1);
    
    //Setup
    const int freq = 5000;
    const int resolution = 8;
    ledcSetup(0, freq, resolution);
    ledcSetup(1, freq, resolution);
}

void Utils::followLine (int speed) {
    //Reading Sensor Values
    int s1 = digitalRead(_ir1);  //Left Most Sensor
    int s2 = digitalRead(_ir2);  //Left Sensor
    int s3 = digitalRead(_ir3);  //Middle Sensor
    int s4 = digitalRead(_ir4);  //Right Sensor
    int s5 = digitalRead(_ir5);  //Right Most Sensor

    //if only middle sensor detects black line
    if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1))
    {
        //going forward with full speed 
        ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
        ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(_m1, HIGH);
        digitalWrite(_m2, LOW);
        digitalWrite(_m3, HIGH);
        digitalWrite(_m4, LOW);
    }

    //if only left sensor detects black line
    if((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
    {
        //going right with full speed 
        ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
        ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(_m1, HIGH);
        digitalWrite(_m2, LOW);
        digitalWrite(_m3, LOW);
        digitalWrite(_m4, LOW);
    }

    //if only left most sensor detects black line
    if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
    {
        //going right with full speed 
        ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
        ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(_m1, HIGH);
        digitalWrite(_m2, LOW);
        digitalWrite(_m3, LOW);
        digitalWrite(_m4, HIGH);
    }

    //if only right sensor detects black line
    if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1))
    {
        //going left with full speed 
        ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
        ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(_m1, LOW);
        digitalWrite(_m2, LOW);
        digitalWrite(_m3, HIGH);
        digitalWrite(_m4, LOW);
    }

    //if only right most sensor detects black line
    if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))
    {
        //going left with full speed 
        ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
        ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(_m1, LOW);
        digitalWrite(_m2, HIGH);
        digitalWrite(_m3, HIGH);
        digitalWrite(_m4, LOW);
    }

    //if middle and right sensor detects black line
    if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))
    {
        //going left with full speed 
        ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
        ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(_m1, LOW);
        digitalWrite(_m2, LOW);
        digitalWrite(_m3, HIGH);
        digitalWrite(_m4, LOW);
    }

    //if middle and left sensor detects black line
    if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
    {
        //going right with full speed 
        ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
        ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(_m1, HIGH);
        digitalWrite(_m2, LOW);
        digitalWrite(_m3, LOW);
        digitalWrite(_m4, LOW);
    }

    //if middle, left and left most sensor detects black line
    if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
    {
        //going right with full speed 
        ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
        ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(_m1, HIGH);
        digitalWrite(_m2, LOW);
        digitalWrite(_m3, LOW);
        digitalWrite(_m4, LOW);
    }

    //if middle, right and right most sensor detects black line
    if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
    {
        //going left with full speed 
        ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
        ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(_m1, LOW);
        digitalWrite(_m2, LOW);
        digitalWrite(_m3, HIGH);
        digitalWrite(_m4, LOW);
    }

    //if all sensors are on a black line
    if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
    {
        //stop
        digitalWrite(_m1, LOW);
        digitalWrite(_m2, LOW);
        digitalWrite(_m3, LOW);
        digitalWrite(_m4, LOW);
    }
}
