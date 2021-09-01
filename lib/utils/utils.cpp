#include <Arduino.h>

#include "utils.h"

// Instancia dois sensores
VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;
VL53L0X sensor4;

#define s2_NewAdress 42
#define s3_NewAdress 43
#define s4_NewAdress 44

Utils::Utils (
    int m1, int m2, int m3, int m4, 
    int e1, int e2,
    int ir1, int ir2, int ir3, int ir4, int ir5,
    int shut_1, int shut_2, int shut_3, int shut_4
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

    //Sensores de distância
    _shut_1 = shut_1;
    _shut_2 = shut_2;
    _shut_3 = shut_3;
    _shut_4 = shut_4;

    //Right side
    pinMode(_m1, OUTPUT);
    pinMode(_m2, OUTPUT);
    pinMode(_e1, OUTPUT);

    //Left side
    pinMode(_m3, OUTPUT);
    pinMode(_m4, OUTPUT);
    pinMode(_e2, OUTPUT);

    //Sensors line
    pinMode(_ir1, INPUT);
    pinMode(_ir2, INPUT);
    pinMode(_ir3, INPUT);
    pinMode(_ir4, INPUT);
    pinMode(_ir5, INPUT);

    //Sensors dist
    pinMode(_shut_1, OUTPUT);
    pinMode(_shut_2, OUTPUT);
    pinMode(_shut_3, OUTPUT);
    pinMode(_shut_4, OUTPUT);

    //AttachPin
    ledcAttachPin(_e1, 0);
    ledcAttachPin(_e2, 1);
    
    //Setup
    const int freq = 5000;
    const int resolution = 8;
    ledcSetup(0, freq, resolution);
    ledcSetup(1, freq, resolution);
}

int Utils::followLine () {
    int moveType;

    //Reading Sensor Values
    int s1 = digitalRead(_ir1);  //Left Most Sensor
    int s2 = digitalRead(_ir2);  //Left Sensor
    int s3 = digitalRead(_ir3);  //Middle Sensor
    int s4 = digitalRead(_ir4);  //Right Sensor
    int s5 = digitalRead(_ir5);  //Right Most Sensor

    //if only middle sensor detects black line
    if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1))
        moveType = 1;

    //if only left sensor detects black line
    if((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
        moveType = 2;

    //if only left most sensor detects black line
    if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
        moveType = 3;

    //if only right sensor detects black line
    if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1))
        moveType = 4;

    //if only right most sensor detects black line
    if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))
        moveType = 5;

    //if middle and right sensor detects black line
    if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))
        moveType = 6;

    //if middle and left sensor detects black line
    if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
        moveType = 7;

    //if middle, left and left most sensor detects black line
    if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
        moveType = 8;

    //if middle, right and right most sensor detects black line
    if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
        moveType = 9;

    //if all sensors are on a black line
    if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
        moveType = 10;
    
    return moveType;
}

void Utils::moveRobot(int moveType, int speed){
    switch (moveType){
        case 1:
            //going forward with full speed 
            ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
            ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
            digitalWrite(_m1, HIGH);
            digitalWrite(_m2, LOW);
            digitalWrite(_m3, HIGH);
            digitalWrite(_m4, LOW);
        case 2:
            //going right with full speed 
            ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
            ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
            digitalWrite(_m1, HIGH);
            digitalWrite(_m2, LOW);
            digitalWrite(_m3, LOW);
            digitalWrite(_m4, LOW);
        case 3:
            //going right with full speed 
            ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
            ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
            digitalWrite(_m1, HIGH);
            digitalWrite(_m2, LOW);
            digitalWrite(_m3, LOW);
            digitalWrite(_m4, HIGH);
        case 4:
            //going left with full speed 
            ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
            ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
            digitalWrite(_m1, LOW);
            digitalWrite(_m2, LOW);
            digitalWrite(_m3, HIGH);
            digitalWrite(_m4, LOW);
        case 5:
            //going left with full speed 
            ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
            ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
            digitalWrite(_m1, LOW);
            digitalWrite(_m2, HIGH);
            digitalWrite(_m3, HIGH);
            digitalWrite(_m4, LOW);
        case 6:
            //going left with full speed 
            ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
            ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
            digitalWrite(_m1, LOW);
            digitalWrite(_m2, LOW);
            digitalWrite(_m3, HIGH);
            digitalWrite(_m4, LOW);
        case 7:
            //going right with full speed 
            ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
            ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
            digitalWrite(_m1, HIGH);
            digitalWrite(_m2, LOW);
            digitalWrite(_m3, LOW);
            digitalWrite(_m4, LOW);
        case 8:
            //going right with full speed 
            ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
            ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
            digitalWrite(_m1, HIGH);
            digitalWrite(_m2, LOW);
            digitalWrite(_m3, LOW);
            digitalWrite(_m4, LOW);
        case 9:
            //going left with full speed 
            ledcWrite(_e1, speed); //you can adjust the speed of the motors from 0-255
            ledcWrite(_e2, speed); //you can adjust the speed of the motors from 0-255
            digitalWrite(_m1, LOW);
            digitalWrite(_m2, LOW);
            digitalWrite(_m3, HIGH);
            digitalWrite(_m4, LOW);
        case 10:
             //stop
            digitalWrite(_m1, LOW);
            digitalWrite(_m2, LOW);
            digitalWrite(_m3, LOW);
            digitalWrite(_m4, LOW);
        default:
            digitalWrite(_m1, LOW);
            digitalWrite(_m2, LOW);
            digitalWrite(_m3, LOW);
            digitalWrite(_m4, LOW);
    }
}

void Utils::sensorInit () {
    digitalWrite(_shut_1, LOW);
    delay(2);
    digitalWrite(_shut_3, LOW);
    delay(2);
    digitalWrite(_shut_4, LOW);
    delay(2);

    // Define o novo endereço de cada sensor
    // Define o sensor 2 como entrada para fazer o pino SHUT_2 ficar em nível alto
    pinMode(_shut_2, INPUT);
    delay(10); //For power-up procedure t-boot max 1.2ms
    sensor2.setAddress(s2_NewAdress);

    pinMode(_shut_3, INPUT);
    delay(10); //For power-up procedure t-boot max 1.2ms
    sensor3.setAddress(s3_NewAdress);

    pinMode(_shut_4, INPUT);
    delay(10); //For power-up procedure t-boot max 1.2ms
    sensor4.setAddress(s4_NewAdress);

    // Religa o sensor 1 definindo ele como entrada
    pinMode(_shut_1, INPUT);
    delay(10); //For power-up procedure t-boot max 1.2ms
    //sensor1.setAddress(41);

    // Inicializa sensores
    sensor1.init();
    sensor2.init();
    sensor3.init();
    sensor4.init();

    sensor1.setTimeout(500);
    sensor2.setTimeout(500);
    sensor3.setTimeout(500);
    sensor4.setTimeout(500);

    // Inicializa modo contínuo
    // Para timed mode, colocar intervalo de medidas na entrada
    sensor1.startContinuous();
    sensor2.startContinuous();
    sensor3.startContinuous();
    sensor4.startContinuous();

    delay(200);

    Serial.println("");
    Serial.println("Sensores ativados\n\n");
}

void Utils::getDist (int typeSensor) {
    switch (typeSensor) {
        case 1:
            _dist1 = sensor1.readRangeContinuousMillimeters();
            if (sensor1.timeoutOccurred()) {Serial.print("TIMEOUT Sensor");}
        case 2:
            _dist2 = sensor2.readRangeContinuousMillimeters();
            if (sensor2.timeoutOccurred()) {Serial.print("TIMEOUT Sensor");}
        case 3:
            _dist3 = sensor3.readRangeContinuousMillimeters();
            if (sensor3.timeoutOccurred()) {Serial.print("TIMEOUT Sensor");}
        case 4:
            _dist4 = sensor4.readRangeContinuousMillimeters();
            if (sensor4.timeoutOccurred()) {Serial.print("TIMEOUT Sensor");}
    }
}
