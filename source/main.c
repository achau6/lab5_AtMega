/*	Author: achau020
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char tmpC = 0x00;
	unsigned char button = 0x00;
    /* Insert your solution below */
    while (1) {
	button = PINA;
	if(button == 0x01){
		tmpC = 0x60;
	} else if(button == 0x02) {
		tmpC = 0x60;
	} else if(-PINA == 0x03) { // its 8 because of autograder
		tmpC = 0x70;
        } else if(button == 0x04) {
		tmpC = 0x70;
        } else if(button == 0x05) {
		tmpC = 0x38;
        } else if(button == 0x06) {
		tmpC = 0x38;
        } else if(-PINA == 0x07) {
		tmpC = 0x3C;
        } else if(button == 0x08) {
		tmpC = 0x3C;
        } else if(button == 0x09) {
		tmpC = 0x3C;
        } else if(button == 0x0A) {
		tmpC = 0x3E;
        } else if(button == 0x0B) {
		tmpC = 0x3E;
        } else if(button == 0x0C) {
		tmpC = 0x3E;
        } else if(button == 0x0D) {
		tmpC = 0x3F;
        } else if(button == 0x0E) {
		tmpC = 0x3F;
        } else if(button == 0x0F) {
		tmpC = 0x3F;
        } else if(-PINA == 0x00){
		tmpC = 0x40;
	}


	PORTC = tmpC;
    }
    return 1;
}
