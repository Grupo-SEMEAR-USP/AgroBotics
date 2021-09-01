#include <Arduino.h>

#include "utils.h"
#include "now.h" 

#define TIME 5000

/* Definição dos pinos */

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

/* Definição dos pinos da comunicação, endereços de Slaves e ID */

#define SHUT_1 5
#define SHUT_2 6
#define SHUT_3 7
#define SHUT_4 8

//Passagem dos pinos a serem lidos e enviados e endereço das esps slaves

uint8_t gpios[] = {23, 2};
uint8_t macSlaves[][6] = {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
const int id = 2;

/* Criando objetos */

Utils robot (
    motorRightTop, motorRightBottom, motorLeftTop, motorLeftBottom,
    pwm0, pwm1,
    sensor1, sensor2, sensor3, sensor4, sensor5);
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
    
};

void loop() {

    //Inicia o robô (Trocar 1 pelo microstart)
    while (1) {

        float myTime = millis();
        float time = 0;
        int moveType, speed = 255;
        
        comunication.Init(); 
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