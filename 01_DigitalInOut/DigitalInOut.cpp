#include <Arduino.h>

#define RED_LED     3
#define BLUE_LED    2
#define BTN_PIN     4


unsigned long redPrevTime = millis();
unsigned long redDelay = 200;

unsigned long bluePrevTime = millis();
unsigned long blueDelay = 199;

unsigned long blinkPrevTime = millis();
unsigned long blinkDelay = 200;

void invert(byte pin){
    digitalWrite(pin, !digitalRead(pin));
}

void setup() {
    Serial.begin(115200);
    pinMode(RED_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    pinMode(BTN_PIN, INPUT_PULLUP);

    digitalWrite(RED_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
}

void loop() {
    Serial.println(digitalRead(BTN_PIN));
    unsigned long currentTime = millis();
    if(digitalRead(BTN_PIN)){
        /*
         * Pokud NENI zmacknute
         * */
        if(currentTime >= (blinkPrevTime + blinkDelay)){
            digitalWrite(RED_LED, !digitalRead(RED_LED));
            digitalWrite(BLUE_LED, digitalRead(RED_LED));
            blinkPrevTime = currentTime;
        }
    }else{/*
     * Pokud JE zmacknute
     * */
        if(currentTime >= (blinkPrevTime + blinkDelay)){
            digitalWrite(RED_LED, !digitalRead(RED_LED));
            digitalWrite(BLUE_LED, !digitalRead(RED_LED));
            blinkPrevTime = currentTime;
        }
    }
///*
//     * Blikani cervenou LED
//     * */
//    if(currentTime >= (redPrevTime + redDelay)){
//        invert(RED_LED);
//        redPrevTime = currentTime;
//    }
//
//    /*
//     * Blikani modrou LED
//     * */
//    if(currentTime >= (bluePrevTime + blueDelay)){
//        invert(BLUE_LED);
//        bluePrevTime = currentTime;
//    }
}