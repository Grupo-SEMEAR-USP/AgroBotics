#include <Arduino.h>

#include "utils.h"
//#include "now.h"
#include <Wire.h>
#define TIME 5000

/* Definição dos pinos */

#define MotorRightTopPin1 2
#define MotorRightTopPin2 4
#define MotorRightBottomPin1 26
#define MotorRightBottomPin2 25
#define MotorLeftTopPin1 18
#define MotorLeftTopPin2 19
#define MotorLeftBottomPin1 12
#define MotorLeftBottomPin2 14


#define SENSOR1 33
#define SENSOR2 32
#define SENSOR3 35
#define SENSOR4 34
#define SENSOR5 23

#define SHUT_1 
#define SHUT_2
#define SHUT_3 
#define SHUT_4 

#define PWM0 15
#define PWM1 27
#define PWM2 5
#define PWM3 13

//Passagem dos pinos a serem lidos e enviados e endereço das esps slaves

uint8_t gpios[] = {23, 2};
uint8_t macSlave[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
const int id = 1; //ID da colheitadeira

/* Criando objetos */

Utils robot (
    MotorRightTopPin1, MotorRightTopPin2, MotorRightBottomPin1, MotorRightBottomPin2, MotorLeftTopPin1, MotorLeftTopPin2, MotorLeftBottomPin1, MotorLeftBottomPin2,
    PWM0, PWM1, PWM2, PWM3,
    SENSOR1, SENSOR2, SENSOR3, SENSOR4, SENSOR5);
/*
Now comunication (
    gpios, macSlave, id);
*/
/* Variáveis default */

int status = 0;

void setup() {
    //Desligar os motores do robô
    
    robot.moveRobot(0, 0);

    //Declarando estados inciais do trator
    status = 1;
    //comunication.Init();
    
};

void loop() {


    //Inicia o robô (Trocar 1 pelo microstart)
    
    while (1) {

        float initialTime = 0;
        int moveType, speed = 225;
        moveType = robot.followLine();
        robot.moveRobot(moveType, speed);
        /*
        comunication.Slave();
        comunication.Master();

        Verifica se trator está posicionado
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
        */
    }
};