#include <Arduino.h>

#include "utils.h"
#include "now.h"

#define TIME 5000

/* Definição dos pinos */

#define MotorRightTop A0
#define MotorRightBottom A5
#define MotorLeftTop A7
#define MotorLeftBottom A3

#define SENSOR1 1
#define SENSOR2 2
#define SENSOR3 3
#define SENSOR4 4
#define SENSOR5 5

#define SHUT_1 6
#define SHUT_2 7
#define SHUT_3 8
#define SHUT_4 9

#define PWM0 10
#define PWM1 11

//Passagem dos pinos a serem lidos e enviados e endereço das esps slaves

uint8_t gpios[] = {23, 2};
uint8_t macSlave[6] = {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
const int id = 1; //ID da colheitadeira

/* Criando objetos */

Utils robot (
    MotorRightTop, MotorRightBottom, MotorLeftTop, MotorLeftBottom,
    PWM0, PWM1,
    SENSOR1, SENSOR2, SENSOR3, SENSOR4, SENSOR5,
    SHUT_1, SHUT_2, SHUT_3, SHUT_4);
Now comunication (
    gpios, macSlave, id);

/* Variáveis default */

int status = 0;

void setup() {
    //Desligar os motores do robô
    robot.moveRobot(0, 0);

    //Declarando estados inciais do trator
    status = 1;
    comunication.Init();
};

void loop() {

    //Inicia o robô (Trocar 1 pelo microstart)
    while (1) {

        float initialTime = 0;
        int moveType, speed = 255;
  
        comunication.Slave();
        comunication.Master();

        //Verifica se trator está posicionado
        if (comunication.myData.status == 1 && comunication.otherData.ready == true) {
            //Trator posicionado
            moveType = robot.followLine();
            robot.moveRobot(moveType, speed);

            comunication.myData.moveType = moveType;
            comunication.myData.time = millis() - initialTime;

        }

        else {
            //Esperando o trator chegar
            robot.moveRobot(0,0);
            initialTime = millis();
        }
    }
};