#include <Arduino.h>

#define MOTOR_A     8
#define MOTOR_B     9
#define MOTOR_C     10
#define MOTOR_D     11

#define BTN_RIGHT   2
#define BTN_LEFT    3

byte bit = 0;

byte motorDelay = 2;

unsigned long prevMillis = 0;

void step(byte val) {
    digitalWrite(MOTOR_A, val & 0b0001);
    digitalWrite(MOTOR_B, val & 0b0010);
    digitalWrite(MOTOR_C, val & 0b0100);
    digitalWrite(MOTOR_D, val & 0b1000);
}

void setup() {
    Serial.begin(115200);
    pinMode(MOTOR_A, OUTPUT);
    pinMode(MOTOR_B, OUTPUT);
    pinMode(MOTOR_C, OUTPUT);
    pinMode(MOTOR_D, OUTPUT);

    pinMode(BTN_LEFT, INPUT_PULLUP);
    pinMode(BTN_RIGHT, INPUT_PULLUP);
}

void loop() {
    unsigned long curMillis = millis();
    if(curMillis - prevMillis >= motorDelay){
        prevMillis = curMillis;

        if (digitalRead(BTN_LEFT)) {
            bit--;
        }
        if (digitalRead(BTN_RIGHT)) {
            bit++;
        }
        bit %= 4;
    }
    step(0b1 << bit);
}