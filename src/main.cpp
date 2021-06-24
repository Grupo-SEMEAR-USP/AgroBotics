#include <Arduino.h>

#include "utils.h"
#include "now.h" 
//TESTE DA BIBLIOTECA UTILS

//TESTE DA BIBLIOTECA NOW

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
const int id = 2;

//Setup dos pinos
Utils robot (
    motorRightTop, motorRightBottom, motorLeftTop, motorLeftBottom,
    pwm0, pwm1,
    sensor1, sensor2, sensor3, sensor4, sensor5);
Now comunication (
    gpios, macSlaves, id);

int status = 0;

void setup() {
    robot.followLine(0);
    
    //Declarando estados inciais do trator
    if (id == 2){
        status = 1;
    }
    else if (id == 3){
        status = -1;
    }
    
};

void loop() {
    
    //Inicia o robo
    //Trocar 1 pelo microstart
    while (1) {

        float myTime = millis();
        float time = 0;
        
        comunication.Slave();
        comunication.Master();

        if (comunication.myData.status == status && comunication.otherData.status == 1){
            
            if (comunication.myData.position == false) {
                //Chegar a colheitadeira
                robot.followLine (200);
                delay(comunication.myData.time);

                //Posicionar o trator

                comunication.myData.ready = true;
                //Mudar o estado do robo
                comunication.myData.position = true;
            }

            else {

                //O While tem q ser substituido por um if Colocamos seja utilizado
                //o modelo de passagem de dados do que esta sendo feito pela colheitadeira
                
                while (time <= 500){
                    //robot.followRobot()
                    time = millis() - myTime;
                }
                //robot.returnBase();
                comunication.myData.status = (-1)*comunication.myData.status;
                comunication.myData.position = false;
            }
        }
    }
};