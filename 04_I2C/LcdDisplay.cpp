#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2);

#define JOY_X A0
#define JOY_Y A1

#define SENSITIVITY 50

unsigned int xPos = 0, yPos = 0;

enum class JoystickState {
    TOP,
    BOT,
    LEFT,
    RIGHT,
    MID
};

JoystickState prevState = JoystickState::MID;

bool activeBuffer = true;
char buf1[2][17] = {{0},
                    {0}};
char buf2[2][17] = {{0},
                    {0}};

void printAsciiTable();

bool inInterval(int val, int compare, int interval);

void printToBuffer(char buffer[2][17]);

void drawBufferToLcd(char buffer[2][17]);

JoystickState getJoystickState();

void setup() {
    Serial.begin(115200);
    lcd.init();

    pinMode(JOY_X, INPUT);
    pinMode(JOY_Y, INPUT);

    lcd.backlight();
    //lcd.noBacklight();

    lcd.print("Hello world!");
    lcd.setCursor(0, 1);
    lcd.print("Ahoj svete");

    char c = 'A';
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 16; j++) {
            buf1[i][j] = c++;
        }
    }


    lcd.setCursor(0, 0);
    lcd.print(buf1[0]);

    lcd.setCursor(0, 1);
    lcd.print(buf1[1]);

    delay(2000);
}

void loop() {
    activeBuffer = !activeBuffer;

    if (activeBuffer) {
        drawBufferToLcd(buf1);
        printToBuffer(buf1);
    } else {
        drawBufferToLcd(buf2);
        printToBuffer(buf2);
    }


    /*//printAsciiTable();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("x: ");
    lcd.print(analogRead(JOY_X));

    lcd.setCursor(0, 1);
    lcd.print("y: ");
    lcd.print(analogRead(JOY_Y));*/
}


void printAsciiTable() {
    for (int znak = '!'; znak < 128; znak++) {
        lcd.clear();
        lcd.setCursor(0, 0);

        lcd.print("ASCII num: ");
        lcd.print((int) znak);

        Serial.print("ASCII num: ");
        Serial.println((int) znak);

        lcd.setCursor(0, 1);

        lcd.print("char: ");
        lcd.print((char) znak);

        Serial.print("char: ");
        Serial.println((char) znak);

        delay(300);
    }
}


void drawBufferToLcd(char buffer[2][17]) {
    lcd.setCursor(0, 0);
    lcd.print(buffer[0]);

    lcd.setCursor(0, 1);
    lcd.print(buffer[1]);
}

void printToBuffer(char buffer[2][17]) {
    /*
     * vycisteni displaye
     * */
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 16; j++) {
            buffer[i][j] = ' ';
        }
    }
    char firstLine[17];
    char secondLine[17];
    int firstLineLen = 0, secondLineLen = 0;


    JoystickState curState = getJoystickState();

    if (prevState != curState)
        switch (curState) {
            case JoystickState::TOP: {
                --yPos;
                yPos %= 2;
                break;
            }
            case JoystickState::BOT: {
                ++yPos;
                yPos %= 2;
                break;
            }
            case JoystickState::LEFT: {
                --xPos;
                xPos %= 16;
                break;
            }
            case JoystickState::RIGHT: {
                ++xPos;
                xPos %= 16;
                break;
            }
            default: { break; }
        }
    prevState = curState;
    buffer[yPos][xPos] = '#';
    /*
     * Zapis do bufferu
     * */
//    firstLineLen = sprintf(firstLine, "x: %d", analogRead(JOY_X));
//    secondLineLen = sprintf(secondLine, "y: %d", analogRead(JOY_Y));
//
//    for (int j = 0; j < firstLineLen; j++) {
//        buffer[0][j] = firstLine[j];
//    }
//    for (int j = 0; j < secondLineLen; j++) {
//        buffer[1][j] = secondLine[j];
//    }

    buffer[0][16] = 0;
    buffer[1][16] = 0;
}


JoystickState getJoystickState() {
    int xJoyValue = analogRead(JOY_X);
    int yJoyValue = analogRead(JOY_Y);

    if (inInterval(xJoyValue, 512, SENSITIVITY) &&
        inInterval(yJoyValue, 512, SENSITIVITY)) {
        Serial.println("MID");
        return JoystickState::MID;
    }

    if (yJoyValue < 512 - SENSITIVITY) {
        Serial.println("TOP");
        return JoystickState::TOP;
    }
    if (yJoyValue > 512 + SENSITIVITY) {
        Serial.println("BOT");
        return JoystickState::BOT;
    }
    if (xJoyValue < 512 - SENSITIVITY) {
        Serial.println("RIGHT");
        return JoystickState::RIGHT;
    }
    if (xJoyValue > 512 + SENSITIVITY) {
        Serial.println("LEFT");
        return JoystickState::LEFT;
    }
}


bool inInterval(int val, int compare, int interval) {
    return
            val > (compare - interval) &&
            val < (compare + interval);
}