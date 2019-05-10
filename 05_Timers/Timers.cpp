#include <Arduino.h>

//timer interrupts
//by Amanda Ghassaei
//June 2012
//https://www.instructables.com/id/Arduino-Timer-Interrupts/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
*/

//timer setup for timer0, timer1, and timer2.
//For arduino uno or any board with ATMEL 328/168.. diecimila, duemilanove, lilypad, nano, mini...

//this code will enable all three arduino timer interrupts.
//timer0 will interrupt at 2kHz
//timer1 will interrupt at 1Hz
//timer2 will interrupt at 8kHz

#define TIMER0_OUT_PIN 8
#define TIMER1_OUT_PIN 9
#define TIMER2_OUT_PIN 13


void invert(const uint8_t &pin);

void setup() {
    //set pins as outputs
    pinMode(TIMER0_OUT_PIN, OUTPUT);
    pinMode(TIMER1_OUT_PIN, OUTPUT);
    pinMode(TIMER2_OUT_PIN, OUTPUT);

    noInterrupts();//stop interrupts

    //set timer0 interrupt at 2kHz
    TCCR0A = 0;// set entire TCCR2A register to 0
    TCCR0B = 0;// same for TCCR2B
    TCNT0 = 0;//initialize counter value to 0
    // set compare match register for 2khz increments
    OCR0A = (16 * 1000000) / (2000 * 64) - 1;// = (16*10^6) / (2000*64) - 1 (must be <256)
    // turn on CTC mode
    TCCR0A |= (1 << WGM01);
    // Set CS01 and CS00 bits for 64 prescaler
    TCCR0B |= (1 << CS01) | (1 << CS00);
    // enable timer compare interrupt
    TIMSK0 |= (1 << OCIE0A);

    //set timer1 interrupt at 1Hz
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1 = 0;//initialize counter value to 0
    // set compare match register for 1hz increments
    OCR1A = (16 * 1000000) / (1024 * 1) - 1;// = (16*10^6) / (1024*1) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS12 and CS10 bits for 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);

//set timer2 interrupt at 8kHz
    TCCR2A = 0;// set entire TCCR2A register to 0
    TCCR2B = 0;// same for TCCR2B
    TCNT2 = 0;//initialize counter value to 0
    // set compare match register for 8khz increments
    OCR2A = (16 * 1000000) / (8000 * 8) - 1;// = (16*10^6) / (8000*8) - 1 (must be <256)
    // turn on CTC mode
    TCCR2A |= (1 << WGM21);
    // Set CS21 bit for 8 prescaler
    TCCR2B |= (1 << CS21);
    // enable timer compare interrupt
    TIMSK2 |= (1 << OCIE2A);


    interrupts();//allow interrupts

}



void loop() {
    //do other things here
}

void invert(const uint8_t &pin) {
    digitalWrite(pin, !digitalRead(pin));
}

ISR(TIMER0_COMPA_vect) {//timer0 interrupt 2kHz toggles pin 8
//generates pulse wave of frequency 2kHz/2 = 1kHz (takes two cycles for full wave- toggle high then toggle low)
    invert(TIMER0_OUT_PIN);
}

ISR(TIMER1_COMPA_vect) {//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
    invert(TIMER1_OUT_PIN);
}

ISR(TIMER2_COMPA_vect) {//timer1 interrupt 8kHz toggles pin 9
//generates pulse wave of frequency 8kHz/2 = 4kHz (takes two cycles for full wave- toggle high then toggle low)
    invert(TIMER2_OUT_PIN);
}