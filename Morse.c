#include "Morse.h"
#include <Math.h>
#include <xc.h>
#include "Buttons.h"
#include "BinaryTree.h"
#include "Oled.h"
#include "OledDriver.h"




//Module level variables
static uint8_t counter = 0; //counter for BTN press event
static uint8_t level = 6; //level of binary Morse Tree
static uint8_t bEvent = BUTTON_EVENT_NONE;
static Node* Morsetree; //pointer to the Morse Tree
static Node* decoded; // pointer to the decoded char


//MorseDecoder machine states
 enum {
    WAITING, DOT, DASH, INTER_LETTER
} mstate;



/**
 *  If the morse tree is successfully generated, SUCCESS is returned, otherwise
 *  STANDARD_ERROR is returned. This function
 * also initializes the Buttons library so that MorseCheckEvents() can work properly.
 * @return Either SUCCESS if the decoding tree was successfully created or STANDARD_ERROR if not.
 */
int MorseInit(void){
    ButtonsInit(); //initialize Buttons library
    OledInit(); //initialize OLED 
    const char MorseTreedata[]="#EISH54V#3UF####2ARL#####WP##J#1TNDB6#X##KC##Y##MGZ7#Q##O#8##90";
    Morsetree = TreeCreate(level, MorseTreedata); 
    
    
    //if tree was not created
    if(Morsetree == NULL){
        return STANDARD_ERROR;
    }
    decoded = Morsetree;
    return SUCCESS;
    
}



/*
 * MorseDecode()
 * Decodes the input DOTS or DASHES by the user into a character from the Morse
 * Tree
 * 
 */
char MorseDecode(MorseChar in){
    //if its a DOT EVENT
    if(in == MORSE_CHAR_DOT){
        if(decoded->leftChild == NULL){
            return STANDARD_ERROR;
        }
        decoded = decoded->leftChild;
        return SUCCESS;
    }
    //if its a DASH EVENT
    else if(in == MORSE_CHAR_DASH){
        if(decoded->rightChild == NULL){
            return STANDARD_ERROR;
        }
        decoded = decoded->rightChild;
        return SUCCESS;
    }
    //if end of char event 
    else if(in == MORSE_CHAR_END_OF_CHAR){
        if(decoded->data == NULL){
            return STANDARD_ERROR;
        }
        return decoded->data;
    }
    //if decode reset event occurred
    else if(in == MORSE_CHAR_DECODE_RESET){
        decoded = Morsetree;
        return SUCCESS;   
    }
    else{
       //if none of the input events happen
        return STANDARD_ERROR; 
    }
    
}

/*
 * calls ButtonCheckEvents() and using timer interrupt, this function determines
 * which Morse events occurred and make the necessary transitions 
 * 
 */
MorseEvent MorseCheckEvents(void){
    
    bEvent = ButtonsCheckEvents(); 
    counter++;
    switch(mstate){
        case WAITING:
            //check for BTN4 event
            if(bEvent & BUTTON_EVENT_4DOWN){
                counter = 0;
                mstate = DOT;
            }
            break;
            
            
        case DOT:
            //check for BTN4 UP event
            if(bEvent & BUTTON_EVENT_4UP){
                counter = 0;
                mstate = INTER_LETTER;
                return MORSE_EVENT_DOT; //dot event occurred
            }
              //if counter>= DOT TIMEOUT
              //if BTN4 held longer than 0.5s
            else if(counter >= MORSE_EVENT_LENGTH_DOWN_DOT){
                mstate = DASH;
            }
            break;
            
        case DASH:
            if(bEvent & BUTTON_EVENT_4UP){
                counter = 0;
                mstate = INTER_LETTER;
                return MORSE_EVENT_DASH; //DASH event occurred
            }
            break;
             
        case INTER_LETTER:
            if(bEvent & BUTTON_EVENT_4DOWN){
                if(counter >= MORSE_EVENT_LENGTH_UP_INTER_LETTER){
                    counter = 0;
                    mstate = DOT;
                    return MORSE_EVENT_INTER_LETTER; 
                }
                else{
                    counter = 0;
                    mstate = DOT;
                    return MORSE_EVENT_NONE;
                }
            }
            //if counter>= inter letter timeout
            if(counter>= MORSE_EVENT_LENGTH_UP_INTER_LETTER_TIMEOUT){
                mstate = WAITING;
                return MORSE_EVENT_INTER_WORD;
            }
            break;
        
    }
    //reset button 
    //return Morse none event if none of the other cases work
    bEvent = BUTTON_EVENT_NONE;
    return MORSE_EVENT_NONE;
    
}


