#include <Arduino.h>
#include <Servo.h>

#define POT_PIN A0
#define SERVO_PIN 3
#define SINUS_KROK 0.01

Servo servo;

double uhel = 0;

void setup() {
    Serial.begin(115200);
    servo.attach(SERVO_PIN);
}

void loop() {
    //servo.write(analogRead(POT_PIN) * 180.f / 1023.f);

    //Uhel v rozsahu <-1, 1>
    double sinUhel = sin(uhel);
    uhel += SINUS_KROK;
    //Prevod uhlu z <-1,1> do <0,2>
    sinUhel += 1.f;
    //Prevod uhlu z <0,2> do <0,1>
    sinUhel /= 2.f;
    Serial.println(sinUhel);
    servo.write(sinUhel * 180.f);
}