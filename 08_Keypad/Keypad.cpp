#include <Arduino.h>
#include <WString.h>

#define R1 2
#define R2 3
#define R3 4
#define R4 5

#define C1 6
#define C2 7
#define C3 8
#define C4 9

/**
 * @brief Piny jednotlivych radku
 */
byte rowPins[4] = {R1, R2, R3, R4};

/**
 * @brief Piny jednotlivych sloupcu
 */
byte colPins[4] = {C1, C2, C3, C4};

/**
 * @brief Znaky pro klavesnici
 */
char znaky[4][4] = {{'1', '2', '3', 'A'},
                    {'4', '5', '6', 'B'},
                    {'7', '8', '9', 'C'},
                    {'*', '0', '#', 'D'}};

bool prevStates[4][4] = {{true, true, true, true},
                         {true, true, true, true},
                         {true, true, true, true},
                         {true, true, true, true}};

void setup() {
    Serial.begin(115200);
    for (int i = 0; i < 4; i++) {
        pinMode(rowPins[i], INPUT);
        pinMode(colPins[i], INPUT_PULLUP);
    }
}

void loop() {
    for (int i = 0; i < 4; i++) {
        pinMode(rowPins[i], OUTPUT);
        digitalWrite(rowPins[i], LOW);
        for (int k = 0; k < 4; k++) {
            bool state = digitalRead(colPins[k]);
            if (state != prevStates[i][k]) {
                if (state == LOW) {
                    /*Mame zmacknute tlacitko*/
//                    Serial.print("Zmacknute tlacitko");
//                    Serial.print(" Sloupec: ");
//                    Serial.print(k);
//                    Serial.print(" Radek: ");
//                    Serial.println(i);
                    Serial.print("Tlacitko: ");
                    Serial.println(znaky[i][k]);
                    char curChar = znaky[i][k];
                }
            }
            prevStates[i][k] = state;
        }
        pinMode(rowPins[i], INPUT);
    }
}