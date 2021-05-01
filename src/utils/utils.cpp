#include <Arduino.h>

#include "utils.h"

Utils::Utils (int m1, int m2, int m3, int m4, int e1, int e2) {
   
    _m1 = m1;
    _m2 = m2;
    _m3 = m3;
    _m4 = m4;

    _e1 = e1;
    _e2 = e2;

    //Right side
    pinMode(_m1, OUTPUT);
    pinMode(_m2, OUTPUT);
    pinMode(_e1, OUTPUT);

    //Left side
    pinMode(_m3, OUTPUT);
    pinMode(_m4, OUTPUT);
    pinMode(_e2, OUTPUT);
}

void Utils::followLine (int speed) {
    //Reading Sensor Values
    int s1 = digitalRead(ir1);  //Left Most Sensor
    int s2 = digitalRead(ir2);  //Left Sensor
    int s3 = digitalRead(ir3);  //Middle Sensor
    int s4 = digitalRead(ir4);  //Right Sensor
    int s5 = digitalRead(ir5);  //Right Most Sensor

    //if only middle sensor detects black line
    if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1))
    {
        //going forward with full speed 
        analogWrite(e1, speed); //you can adjust the speed of the motors from 0-255
        analogWrite(e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(m1, HIGH);
        digitalWrite(m2, LOW);
        digitalWrite(m3, HIGH);
        digitalWrite(m4, LOW);
    }

    //if only left sensor detects black line
    if((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
    {
        //going right with full speed 
        analogWrite(e1, speed); //you can adjust the speed of the motors from 0-255
        analogWrite(e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(m1, HIGH);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, LOW);
    }

    //if only left most sensor detects black line
    if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
    {
        //going right with full speed 
        analogWrite(e1, speed); //you can adjust the speed of the motors from 0-255
        analogWrite(e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(m1, HIGH);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, HIGH);
    }

    //if only right sensor detects black line
    if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1))
    {
        //going left with full speed 
        analogWrite(e1, speed); //you can adjust the speed of the motors from 0-255
        analogWrite(e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(m1, LOW);
        digitalWrite(m2, LOW);
        digitalWrite(m3, HIGH);
        digitalWrite(m4, LOW);
    }

    //if only right most sensor detects black line
    if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))
    {
        //going left with full speed 
        analogWrite(e1, speed); //you can adjust the speed of the motors from 0-255
        analogWrite(e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(m1, LOW);
        digitalWrite(m2, HIGH);
        digitalWrite(m3, HIGH);
        digitalWrite(m4, LOW);
    }

    //if middle and right sensor detects black line
    if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))
    {
        //going left with full speed 
        analogWrite(e1, speed); //you can adjust the speed of the motors from 0-255
        analogWrite(e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(m1, LOW);
        digitalWrite(m2, LOW);
        digitalWrite(m3, HIGH);
        digitalWrite(m4, LOW);
    }

    //if middle and left sensor detects black line
    if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
    {
        //going right with full speed 
        analogWrite(e1, speed); //you can adjust the speed of the motors from 0-255
        analogWrite(e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(m1, HIGH);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, LOW);
    }

    //if middle, left and left most sensor detects black line
    if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
    {
        //going right with full speed 
        analogWrite(e1, speed); //you can adjust the speed of the motors from 0-255
        analogWrite(e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(m1, HIGH);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, LOW);
    }

    //if middle, right and right most sensor detects black line
    if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
    {
        //going left with full speed 
        analogWrite(e1, speed); //you can adjust the speed of the motors from 0-255
        analogWrite(e2, speed); //you can adjust the speed of the motors from 0-255
        digitalWrite(m1, LOW);
        digitalWrite(m2, LOW);
        digitalWrite(m3, HIGH);
        digitalWrite(m4, LOW);
    }

    //if all sensors are on a black line
    if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
    {
        //stop
        digitalWrite(m1, LOW);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, LOW);
    }
}