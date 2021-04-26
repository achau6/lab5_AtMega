/*      Author: lab
 *  Partner(s) Name: 
 *      Lab Section:
 *      Assignment: Lab #  Exercise #
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include <stdbool.h>
#endif

int count = 0;

enum SM_STATE { Init, Inc, Dec, Wait1, Wait2, Wait3, Wait4, Reset } state;
void Tick(){
        unsigned char input = ~PINA & 0x01;
        switch(state) {
                case Init:
                        if(input){
                                //if(count == 63){
                                        //state = Dec;
                                //} else {
                                        state = Inc;
                                //}
                        } else {
                                state = Init;
                        }
                break;

                case Inc:
                        if(count < 0x3F){
                                if(!input){
                                        state = Wait1;
                                } else {
                                        state = Inc;
                                }
                        } /*else if(count >= 0x40){
                                if(!input){
                                        state = Wait3;
                                } else {
                                        state = Inc;
                                }
                        }*/
                break;
                case Wait1:
                        if(!input) {
                                state = Wait2;
                        } else {
                                state = Wait1;
                        }
                break;

                case Wait2:
                        if(input){
                                //state = Inc;
                                state = Wait2;
                        } else {
                                state = Wait1;
                        }
                break;

                case Dec:
                        if(count != 0x00){
                                if(!input){
                                        state = Wait3;
                                } else {
                                        state = Dec;
                                }
                        } else {
                                state = Init;
                        }
                break;
                case Wait3:
                        if(input) {
                                state = Wait4;
                        } else {
                                state = Wait3;
                        }
                break;

                case Wait4:
                        if(!input){
                                state = Dec;
                        } else {
                                state = Wait4;
                        }
                break;

                case Reset:
                        if(input){
                                state = Reset;
                        } else {
                                state = Init;
                        }

                break;

                default:
                        state = Init;
                break;

        }

        switch(state) {
                case Init:
                break;
                case Wait2:
                        //count = count << 1;
                        //count = count | 0x01;
                        count = (count * 2) + 1;
                break;
                case Dec:
                        //count = count >> 1;
                        count = (count - 1) / 2;
                break;
                case Reset:
                        PORTB = 0x00;
                        //state = Init;
                break;
                default:
                break;
        }

        switch(count) {
                case 0:
                        PORTB = 0x00;
                break;
                case 1:
                        PORTB = 0x01;
                break;
                case 3:
                        PORTB = 0x03;
                break;
                case 7:
                        PORTB = 0x07;
                break;
                case 15:
                        PORTB = 0x0F;
                break;
                case 31:
                        PORTB = 0x1F;
                break;
                case 63:
                        PORTB = 0x3F;
                break;
        }


        //PORTB = count;
}

int main(void) {
    /* Insert DDR and PORT initializations */
        DDRB = 0xFF; PORTB = 0x00;
        DDRA = 0x00; PORTA = 0xFF;
    /* Insert your solution below */

        count = 0;
    while (1) {
        Tick();

    }
    return 1;
}
