#include <Arduino.h>

#include "utils.h"
#include "now.h" 

#define TIME 5000 //Tempo para revezamento

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
uint8_t macSlaves[][6] = {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
const int id = 2;

/* Criando objetos */

Utils robot (
    MotorRightTop, MotorRightBottom, MotorLeftTop, MotorLeftBottom,
    PWM0, PWM1,
    SENSOR1, SENSOR2, SENSOR3, SENSOR4, SENSOR5,
    SHUT_1, SHUT_2, SHUT_3, SHUT_4);
Now comunication (
    gpios, macSlaves, id);

/* Variáveis default */

int status = 0;

void setup() {
    //Desligar os motores do robô
    robot.moveRobot(0, 0);
    
    //Declarando estados inciais do trator
    if (id == 2){
        status = 1;
    }
    else if (id == 3){
        status = -1;
    }
    comunication.Init();
    
};

void loop() {

    //Inicia o robô (Trocar 1 pelo microstart)
    while (1) {

        float myTime = millis();
        float time = 0;
        int moveType, speed = 255;
    
        comunication.Slave();
        comunication.Master();
        
        if (comunication.myData.status == status && comunication.otherData.status == 1){
            
            if (comunication.myData.position == false) {
                //Chegar a colheitadeira
                while(time <= comunication.otherData.time){
                    moveType = robot.followLine();
                    robot.moveRobot(moveType, speed);

                    time = millis() - myTime;
                }

                //Posicionar o trator

                //Mudar o estado do robo
                comunication.myData.ready = true;
                comunication.myData.position = true;
            }

            else {
                while (time <= TIME){
                    //Recebendo o movimento que a colheitadeira está fazendo
                    comunication.Slave();
                    moveType = comunication.otherData.moveType;
                    robot.moveRobot(moveType, speed);
                    //Acrescentar forma de controlar a contagem de curvas
                    
                    time = millis() - myTime;
                }
                //robot.returnBase();
                comunication.myData.status = (-1)*comunication.myData.status;
                comunication.myData.position = false;
            }
        }
    }
};