#include <Arduino.h>

#define LED_BLUE    2
#define LED_RED     3
#define BTN_PIN     4

unsigned long bluePrevTime = millis();
unsigned long redPrevTime = millis();

unsigned int blueDelay = 500;
unsigned int redDelay = 600;

bool btnPrevState;
bool blueBlink = true;

void invert(int pin) {
    digitalWrite(pin, !digitalRead(pin));
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_BLUE, OUTPUT); //modra LED
    pinMode(LED_RED, OUTPUT); //cervena LED
    pinMode(BTN_PIN, INPUT_PULLUP); // Tlacitko

    btnPrevState = digitalRead(BTN_PIN);
}

void loop() {
    bool btnCurrentState = digitalRead(BTN_PIN);

    if (btnCurrentState != btnPrevState) {
        if (!btnCurrentState) {
            Serial.println("Invertuj");
            digitalWrite(LED_RED, LOW);
            digitalWrite(LED_BLUE, LOW);
            blueBlink = !blueBlink;
        }
    }
    btnPrevState = btnCurrentState;

    if (blueBlink) { //blikej s modrou
        if (bluePrevTime + blueDelay <= millis()) {
            invert(LED_BLUE);
            bluePrevTime = millis();
        }
    } else { //blikej s cervenou
        if (redPrevTime + redDelay <= millis()) {
            invert(LED_RED);
            redPrevTime = millis();
        }
    }
}