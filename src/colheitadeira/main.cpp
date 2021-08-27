#include <Arduino.h>

#include "utils.h"
#include "now.h"
#include "dist_sensor.h"

#define TIME 5000

//Definição dos canais
const int motorRightTop = 1;
const int motorRightBottom = 2;
const int motorLeftTop = 3;
const int motorLeftBottom = 4;

const int sensor1 = 5;
const int sensor2 = 6;
const int sensor3 = 7;
const int sensor4 = 8;
const int sensor5 = 9;

const int pwm0 = 10;
const int pwm1 = 11;

//Passagem dos pinos a serem lidos e enviados e endereço das esps slaves
uint8_t gpios[] = {23, 2};
uint8_t macSlaves[][6] = {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
const int id = 1; //ID da colheitadeira

//Setup dos pinos
Utils robot (
    motorRightTop, motorRightBottom, motorLeftTop, motorLeftBottom,
    pwm0, pwm1,
    sensor1, sensor2, sensor3, sensor4, sensor5);
Now comunication (
    gpios, macSlaves, id);

int status = 1; //Configurando colheitadeira para percorrer

void setup() {
    robot.moveRobot(0, 0);


};

void loop() {

    //Inicia o robo
    //Trocar 1 pelo microstart
    while (1) {

        float myTime = millis();
        float time = 0;
        int moveType, speed = 255;

        comunication.Init();
        comunication.Slave();
        comunication.Master();

        //Verifica se trator está posicionado
        if (comunication.myData.status == 1 && comunication.otherData.ready == true) {
                //Trator posicionado
                    moveType = robot.followLine();
                    comunication.Master();
                    robot.moveRobot(moveType, speed);
                    //Registrar tempo?

            }
          else{
                    //Esperando o trator chegar
                    robot.moveRobot(0,0);
            }
          }
        };
