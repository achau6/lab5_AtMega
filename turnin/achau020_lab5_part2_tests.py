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
#include <stdbool.h>
#endif

enum SM_STATE { Start, Init, Inc, Dec, Reset } state;
int count = 7;
bool press1 = false;
bool press2 = false;

void Tick() {
	unsigned char button = PINA & 0x03;
	switch(state) {
		case Start:
			state = Init;
		break;

		case Init:
			if(button == 0x01){
					state = Inc;
			} else if(button == 0x02){
					state = Dec;
			} else if(button == 0x03){
				state = Reset;
			} else {
				press1 = false;
				press2 = false;
				state = Init;
			}	
		break;

		case Inc:	
			if(count < 10 && press1 == false){
				state = Inc;
			} else if(press1 == true && press2 == true){
				state = Reset;
			} else {
				state = Init;
			}
		break;
	
		case Dec:
			if(count != 0 && press2 == false){
                                state = Dec;
                        } else if(press1 == true && press2 == true){
                                state = Reset;
                        } else {
				state = Init;
                        }
		break;

		case Reset:
			if((button == 0x03) || (press1 == true && press2 == true)){
				state = Reset;
			} else {
				state = Init;	
			}
		break;
		
		default:
		break;
	}

	switch(state) {
		case Inc:
			if((button == 0x01) && (count < 10) && (press1 == false)){
				count ++;
				press1 = true;
			} 
			if(press1 == true && press2 == true){
				count = 0; 
			}
			//state = Init;
		break;
	
		case Dec:
			if((button == 0x02) && (count != 0) && (press2 == false)){
                                count --;
                                press2 = true;
                        }
			if(press1 == true && press2 == true){
                                count = 0;
                        }
			//state = Init;
		break;

		case Reset:
			count = 0;
			press1 = false;
			press2 = false;
			state = Init;
		break;

	}

	PORTC = count;
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char tmpC = 0x00;
	unsigned char button = 0x00;
    /* Insert your solution below */
    state = Init;
    while (1) {

	Tick();
    }
    return 1;
}
