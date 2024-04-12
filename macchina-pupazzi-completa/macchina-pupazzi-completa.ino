#include <Stepper.h>

int pulsante = 2;
// variabili motore gancio
int enA = 3;
int in1 = 12;
int in2 = 13;
// variabili joystick
int pinX = A0;
int pinY = A1;
int xjoy, yjoy;
// 1 giro dello stepper = 2048 passi
const int passi = 25;
// per lo stepper 28BYJ-48 range 0~17 rpm
const int rpm = 15;

// inizializzo lo stepper con pin IN1, IN3, IN2, IN4
// Stepper1 sono in realtà 2 comandati simultaneamente
Stepper Stepper1(passi, 11, 9, 10, 8);
Stepper Stepper2(passi, 7, 5, 6, 4);

void setup() {
  pinMode(pulsante, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(A2, OUTPUT);
  // pin di prova per motore, togliere
  // pinMode(17, OUTPUT);
  // pinMode(18, OUTPUT);
  // fine
  // imposta la velocità degli stepper
  Stepper1.setSpeed(rpm);
  Stepper2.setSpeed(rpm);
  Serial.begin(9600);
}

void loop() {
  analogWrite(enA, 50);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  // se premo il pulsante il motore fa salire e scendere il gancio
  if(digitalRead(pulsante) == HIGH){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(A2, HIGH);
    delay(2000);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(2000);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(A2, LOW);
  }
  // leggo i valori del joystick
  xjoy = analogRead(pinX);
  yjoy = analogRead(pinY);
  Serial.print("X: ");
  Serial.print(xjoy);
  Serial.print(" Y: ");
  Serial.println(yjoy);
  // imposto un if per alimentare i motori solo se il joystick non e' fermo
  if((xjoy > 450 && xjoy < 550) && (yjoy > 450 && yjoy < 550)){
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    }
  else {
    if(xjoy > 1020){
      // muove motore 1 senso orario (1 giro = 2048 passi)
      Serial.println("X orario");
      Stepper1.step(passi);
      // digitalWrite(17, HIGH); // controllo
    }
    if(xjoy < 200){
      // muove motore 1 senso antiorario
      Serial.println("X antiorario");
      Stepper1.step(-passi);
      // digitalWrite(17, LOW); // controllo
    }
    if(yjoy > 1020){
      // muove motore 2 senso orario
      Serial.println("Y orario");
      Stepper2.step(passi);
      // digitalWrite(18, HIGH); // controllo
    }
    if(yjoy < 200){
      // muove motore 2 senso antiorario
      Serial.println("Y antiorario");
      Stepper2.step(-passi);
      // digitalWrite(18, LOW); // controllo
    }
  }
}