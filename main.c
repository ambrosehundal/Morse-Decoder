// **** Include libraries here ****
// Standard C libraries


//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
#include "Ascii.h"
#include "BinaryTree.h"
#include "Buttons.h"
#include "Morse.h"
#include "Oled.h"
#include "OledDriver.h"
#include "Morse.h"


// **** Set any macros or preprocessor directives here ****
// Specify a bit mask for setting/clearing the pin corresponding to BTN4. Should only be used when
// unit testing the Morse event checker.
#define BUTTON4_STATE_FLAG (1 << 7)

// **** Declare any data types here ****

// **** Define any module-level, global, or external variables here ****
static uint8_t mEvent = MORSE_EVENT_NONE; //initialize morse event checker to none
static uint8_t Morse;
static char decodedChar;

//DASH AND DOT event results
static uint8_t dotTest = 1;
static uint8_t dashTest = 1;

//Oled display
static char display[100] = "";
static char top[20] = "";
static char down[80] = "";

// **** Declare any function prototypes here ****
//OLED functions

void ClearInput(void) {
    
    //CLEAR OLED INPUT-COMBO SCREEN
    int j;
    for (j = 0; j < 20; j++) {
        top[j] = '\0';
    }
    OledClear(OLED_COLOR_BLACK);
    sprintf(display, "\n%s", down);
    OledDrawString(display);
    OledUpdate();
}


//append a char to the top

void AppendCharTop(char* c) {
    strcat(top, c);
    sprintf(display, "%s\n%s", top, down);
    OledDrawString(display);
    OledUpdate();
}


//append a char to the bottom

void AppendCharDown(char* d) {
    strcat(down, d);
    sprintf(display, "%s\n%s", top, down);
    OledDrawString(display);
    OledUpdate();
}

int main() {
    BOARD_Init();


    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_16, BOARD_GetPBClock() / 16 / 100);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T2);
    INTSetVectorPriority(INT_TIMER_2_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_2_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T2, INT_ENABLED);

    /******************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     *****************************************************************************/


    Morse = MorseInit();


    //check if morse is initialized
    if (Morse == 0) {
        printf("Initialization error");
        FATAL_ERROR();
    } else {
        while (1) {
            //check if an event happened
            if (mEvent != MORSE_EVENT_NONE) {

                //check for DOT event
                if (mEvent == MORSE_EVENT_DOT) {
                    dotTest = MorseDecode(MORSE_CHAR_DOT);

                    //check if valid left child was accessed
                    if (dotTest == 0) {
                        ClearInput();
                        AppendCharDown("#");
                        MorseDecode(MORSE_CHAR_DECODE_RESET);
                    } else {
                        AppendCharTop(".");
                    }
                } else if (mEvent == MORSE_EVENT_DASH) {
                    dashTest = MorseDecode(MORSE_CHAR_DASH);

                    //check if valid right child was accessed
                    if (dashTest == 0) {
                        ClearInput();
                        AppendCharDown("#"); //invalid char
                        MorseDecode(MORSE_CHAR_DECODE_RESET);
                    } else {
                        AppendCharTop("-");
                    }

                } else if (mEvent == MORSE_EVENT_INTER_LETTER) {
                    decodedChar = MorseDecode(MORSE_CHAR_END_OF_CHAR);

                    //if current node has no DATA holding
                    if (decodedChar == NULL) {
                        decodedChar = '#';
                    }
                    ClearInput();
                    AppendCharDown(&decodedChar); //append decoded char
                    MorseDecode(MORSE_CHAR_DECODE_RESET);

                } else if (mEvent == MORSE_EVENT_INTER_WORD) {
                    MorseDecode(MORSE_CHAR_DECODE_RESET);
                    ClearInput();
                    AppendCharDown(" ");

                }
                mEvent = MORSE_EVENT_NONE;
            }




        }





    }





    /******************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks.
     *****************************************************************************/

    while (1);
}

void __ISR(_TIMER_2_VECTOR, IPL4AUTO) TimerInterrupt100Hz(void) {
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    //******** Put your code here *************//
    mEvent = MorseCheckEvents();

}
