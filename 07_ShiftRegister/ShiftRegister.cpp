#include <Arduino.h>

#define REGISTR_DATA_PIN    2
#define REGISTR_LATCH_PIN   3
#define REGISTR_CLK_PIN     4

#define ENKODER_DT_PIN      5
#define ENKODER_CLK_PIN     6

byte ledky = 0;

int prevClk;

int polohaEnkoderu = 4;

void sendToRegister() {
    digitalWrite(REGISTR_LATCH_PIN, LOW);
    for (int b = 0; b < 8; b++) {
        digitalWrite(REGISTR_DATA_PIN, (ledky & (1 << b)));
        digitalWrite(REGISTR_CLK_PIN, HIGH);
        digitalWrite(REGISTR_CLK_PIN, LOW);
    }

    digitalWrite(REGISTR_LATCH_PIN, HIGH);
}

void setup() {
    Serial.begin(115200);
    pinMode(REGISTR_DATA_PIN, OUTPUT);
    pinMode(REGISTR_LATCH_PIN, OUTPUT);
    pinMode(REGISTR_CLK_PIN, OUTPUT);

    pinMode(ENKODER_CLK_PIN, INPUT);
    pinMode(ENKODER_DT_PIN, INPUT);

    prevClk = digitalRead(ENKODER_CLK_PIN);
}

void loop() {
    int curClk = digitalRead(ENKODER_CLK_PIN);

    if (curClk != prevClk && curClk == 1) {
        Serial.println("Pohyb enkoderu");
        if (digitalRead(ENKODER_DT_PIN) == curClk) {
            Serial.println("Pohyb vlevo");
            polohaEnkoderu--;
            polohaEnkoderu %= 9;
        } else {
            Serial.println("Pohyb vpravo");
            polohaEnkoderu++;
        }
    }
    if (polohaEnkoderu > 8) {
        polohaEnkoderu = 8;
    }

    if (polohaEnkoderu < 0) {
        polohaEnkoderu = 0;
    }
    prevClk = curClk;

    ledky = 0b11111111 >> polohaEnkoderu;
    sendToRegister();

//    ledky = 0;
//    sendToRegister();
//    delay(200);
//
//    ledky = 0b11111111;
//    sendToRegister();
//    delay(200);
//



//    for (int i = 0; i < 8; i++) {
//        ledky = 0b11111111 >> (8 - i);
//        sendToRegister();
//        delay(200);
//    }
//    for (int i = 0; i < 8; i++) {
//        ledky = 0b11111111 >> i;
//        sendToRegister();
//        delay(200);
//    }
//

}