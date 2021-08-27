#include <Wire.h>
#include <VL53L0X.h>

// Instancia dois sensores
VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;
VL53L0X sensor4;

#define SHUT_1 5
#define SHUT_2 6
#define SHUT_3 7
#define SHUT_4 8

// #define s1_NewAdress 41 - Não precisa colocar (padrão)
#define s2_NewAdress 42
#define s3_NewAdress 43
#define s4_NewAdress 44

void setup()
{
  // Define todos os Sensores como saída
  pinMode(SHUT_1, OUTPUT);
  pinMode(SHUT_2, OUTPUT);
  pinMode(SHUT_3, OUTPUT);
  pinMode(SHUT_4, OUTPUT);

  Serial.begin(9600);

  Wire.begin();

  // Desliga os sensores 1, 3 e 4
  digitalWrite(SHUT_1, LOW);
  delay(2);
  digitalWrite(SHUT_3, LOW);
  delay(2);
  digitalWrite(SHUT_4, LOW);
  delay(2);

  // Define o novo endereço de cada sensor
  // Define o sensor 2 como entrada para fazer o pino SHUT_2 ficar em nível alto
  pinMode(SHUT_2, INPUT);
  delay(10); //For power-up procedure t-boot max 1.2ms
  sensor2.setAddress(s2_NewAdress);

  pinMode(SHUT_3, INPUT);
  delay(10); //For power-up procedure t-boot max 1.2ms
  sensor3.setAddress(s3_NewAdress);

  pinMode(SHUT_4, INPUT);
  delay(10); //For power-up procedure t-boot max 1.2ms
  sensor4.setAddress(s4_NewAdress);

  // Para adicionar novos sensores
  //pinMode(SHUT_X, INPUT);
  //delay(10); //For power-up procedure t-boot max 1.2ms
  //SensorX.setAddress(sx_NewAdress);

  // Religa o sensor 1 definindo ele como entrada
  pinMode(SHUT_1, INPUT);
  delay(10); //For power-up procedure t-boot max 1.2ms
  //sensor1.setAddress(41);

  // Inicializa sensores
  sensor.init();
  sensor2.init();
  sensor3.init();
  sensor4.init();
  //sensorX.init();

  sensor.setTimeout(500);
  sensor2.setTimeout(500);
  sensor3.setTimeout(500);
  sensor4.setTimeout(500);
  //sensorX.setTimeout(500);

  // Inicializa modo contínuo
  // Para timed mode, colocar intervalo de medidas na entrada
  sensor.startContinuous();
  sensor2.startContinuous();
  sensor3.startContinuous();
  sensor4.startContinuous();
  //sensorX.startContinuous();

  delay(200);

  println("");
  println("Sensores ativados\n\n");
}

void loop()
{
  // Mede a distância sensores
  int dist1;
  int dist2;
  int dist3;
  int dist4;

  dist1 = sensor1.readRangeContinuousMillimeters();
  if (sensor1.timeoutOccurred()) {Serial.print("TIMEOUT Sensor 1"); }

  dist2 = sensor2.readRangeContinuousMillimeters();
  if (sensor2.timeoutOccurred()) {Serial.print("TIMEOUT Sensor 2"); }

  dist3 = sensor3.readRangeContinuousMillimeters();
  if (sensor3.timeoutOccurred()) {Serial.print("TIMEOUT Sensor 3"); }

  dist4 = sensor4.readRangeContinuousMillimeters();
  if (sensor4.timeoutOccurred()) {Serial.print("TIMEOUT Sensor 4"); }

  //distX = sensorX.readRangeContinuousMillimeters();
  //if (sensorX.timeoutOccurred()) {Serial.print("TIMEOUT Sensor X"); }

  Serial.print("Distância sensor 1: ")
  Serial.println(dist1);
  Serial.print("Distância sensor 2: ");
  Serial.println(dist2);
  Serial.print("Distância sensor 3: ")
  Serial.println(dist3);
  Serial.print("Distância sensor 4: ");
  Serial.println(dist4);

  //Parar sistema
  stop();
}

void get_dist()
{
  //Medição da Distância
  dist = sensor.readRangeContinuousMillimeters();
  if (sensor.timeoutOccurred()) {Serial.print("TIMEOUT Sensor";}

  Serial.print("Distância sensor: ")
  Serial.println(dist);
  return dist
}

void stop()
{
  // Para e desativa os sensores
  sensor1.stopContinuous();
  sensor2.stopContinuous();
  sensor3.stopContinuous();
  sensor4.stopContinuous();
  delay(200);

  Serial.println("Sensores desativados!");
}
