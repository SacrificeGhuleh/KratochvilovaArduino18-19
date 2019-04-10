#include <Arduino.h>

#define LED_CERVENA 3
#define PIN_POT A0

unsigned long minDelay = 200;
unsigned long maxDelay = 3000;

unsigned long redPrevTime = millis();
unsigned long redDelay = 200;

float mapFloat(float value, float inMin, float inMax, float outMin, float outMax) {
    return
            (value - inMin) *
            (outMax - outMin) /
            (inMax - inMin) +
            outMin;
}

void invert(byte pin) {
    digitalWrite(pin, !digitalRead(pin));
}

void setup() {
    pinMode(LED_CERVENA, OUTPUT);
    pinMode(PIN_POT, INPUT);

    digitalWrite(LED_CERVENA, HIGH);

    Serial.begin(115200);
}

void loop() {

    /*V intervalu <minDelay,maxDelay>*/
    redDelay = mapFloat(analogRead(PIN_POT),
                        0.f,
                        1024.f,
                        minDelay,
                        maxDelay);

    unsigned long currentTime = millis();
    if (currentTime >= (redPrevTime + redDelay)) {
        invert(LED_CERVENA);
        redPrevTime = currentTime;
    }

//analogWrite(LED_CERVENA, analogRead(PIN_POT)/4);

//    float voltage = ((float)analogRead(PIN_POT) * 5.f) / 1024.f;
//
//    int potValue = analogRead(PIN_POT);
//    Serial.print(0);
//    Serial.print(" ");
//    Serial.print(5);
//    Serial.print(" ");
//    Serial.println(voltage);

//    for(int i = 0; i < 256; i++){
//        analogWrite(LED_CERVENA, i);
//        delay(50);
//    }
//    for(int i = 255; i >= 0; i--){
//        analogWrite(LED_CERVENA, i);
//        delay(50);
//    }
}