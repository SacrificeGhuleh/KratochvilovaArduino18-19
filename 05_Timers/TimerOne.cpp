#include <Arduino.h>
#include <TimerOne.h>
#include <Servo.h>

void invert(byte pin){
    digitalWrite(pin, !digitalRead(pin));
}

void ISR_timer(){
    invert(LED_BUILTIN);

    Serial.println("Preruseni");
}

void setup() {
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    Timer1.initialize(1000000);

    Timer1.attachInterrupt(ISR_timer);
    Timer1.start();
}

void loop() {
    Serial.println("loop");
    delay(111);
}