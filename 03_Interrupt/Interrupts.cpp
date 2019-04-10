#include <Arduino.h>


#define BTN_1 2
#define BTN_2 3

#define LED_1 5
#define LED_2 6
#define LED_3 9
#define LED_4 10

#define DEBOUNCE_TIME 2

enum Stavy {
    BLIKANI_POMALU,
    BLIKANI_RYCHLE,
    POSTUPNE_ZLEVA,
    POSTUPNE_ZPRAVA,
    POCET_STAVU
};

byte aktualniStav = Stavy::POSTUPNE_ZLEVA;

unsigned long prevSlowBlinkTime = millis();
unsigned long prevFastBlinkTime = millis();

byte slowDelay = 1000;
byte fastDelay = 500;

byte ledArray[4] = {LED_1, LED_2, LED_3, LED_4};

volatile int pocetPreruseni = 0;

volatile unsigned long lastInterruptTime1 = 0;
volatile unsigned long lastInterruptTime2 = 0;

void ISR_btn1() {
    unsigned long currentMillis = millis();
    if (currentMillis - lastInterruptTime1 < DEBOUNCE_TIME)
        return;

    aktualniStav++;
    aktualniStav %= Stavy::POCET_STAVU;


    Serial.println("Preruseni 1");
    lastInterruptTime1 = currentMillis;
}

void ISR_btn2() {
    unsigned long currentMillis = millis();
    if (currentMillis - lastInterruptTime2 < DEBOUNCE_TIME)
        return;

    aktualniStav--;
    aktualniStav %= Stavy::POCET_STAVU;


    Serial.println("Preruseni 2");
    lastInterruptTime2 = currentMillis;
}

void setup() {
    Serial.begin(115200);
    pinMode(BTN_1, INPUT_PULLUP);
    pinMode(BTN_2, INPUT_PULLUP);
    attachInterrupt(
            digitalPinToInterrupt(BTN_1),
            ISR_btn1,
            CHANGE);
    attachInterrupt(
            digitalPinToInterrupt(BTN_2),
            ISR_btn2,
            RISING);

    for (int i = 0; i < 4; i++) {
        pinMode(ledArray[i], OUTPUT);
        digitalWrite(ledArray[i], HIGH);
    }
}

void loop() {
    unsigned long currentTime = millis();
    switch (aktualniStav) {
        case Stavy::BLIKANI_POMALU: {
            if (currentTime >= prevSlowBlinkTime + slowDelay) {
                prevSlowBlinkTime = currentTime;
                for (int i = 0; i < 4; i++) {
                    digitalWrite(ledArray[i], !digitalRead(ledArray[i]));
                }
            }
            break;
        }
        case Stavy::BLIKANI_RYCHLE: {
            if (currentTime >= prevFastBlinkTime + fastDelay) {
                prevFastBlinkTime = currentTime;
                for (int i = 0; i < 4; i++) {
                    digitalWrite(ledArray[i], !digitalRead(ledArray[i]));
                }
            }
            break;
        }
        case Stavy::POSTUPNE_ZLEVA: {
            //TODO
            break;
        }
        case Stavy::POSTUPNE_ZPRAVA: {
            //TODO
            break;
        }
    }

}