/*
 Author: Tom Kamprath
 Description: AVR AT328* Power & Sleep Mode Controller
 */

#include <stdio.h>

static uint8_t* SCR = 0x61; //SC Register
static uint8_t* MCU_BOD = 0x55; //BOD Bits in MCU Register
static uint8_t* MCU_STATUS = 0x55;
static uint8_t* PORTB_DATA = 0x25;
static uint8_t* PORTB_ROLE = 0x24;
static uint8_t* GLBL_INTR = 0x5F;
static uint8_t* EXT_INTR_CONTRL = 0x69; //Interrupt Control Register
uint8_t* INTR_PORT = 0x0;
bool IntrAsOutp = 0; //Interrupt Pin can be Output too

void SMC_SET(uint8_t SMC_MODE, bool BODS_DISABLE){
    if(SMC_MODE > 5) foo(); //Still need to implement error handling

    if (BODS_DISABLE){
        *MCU_BOD = (1 << 7); 
        *MCU_BOD = (1 << 6); 
        *MCU_BOD &= ~(1 << 8); //Shift zero
    } 

    //Todo: Change this to shift operation!
    switch (SMC_MODE){
        case 0: *SCR = 0; //IDLE
        case 1: *SCR = (1 << 1); //ADC
        case 2: *SCR = (1 << 2); //Power-down
        case 3: *SCR = (1 << 1); //*SCR = 6
                *SCR = (1 << 2); 
        case 4: *SCR = (1 << 2); //*SCR = 12
                *SCR = (1 << 3);
        case 5: *SCR = (1 << 1);
                *SCR = (1 << 2);
                *SCR = (1 << 3); //*SCR = 14 ext. Standby
    }

}

uint8_t MCU_RESET_SOURCE(){
    return *MCU_STATUS; //Get Reset Source
    *MCU_STATUS = 0; //Reset
}

void SET_INTERRUPT_RDY(bool PORT_OUTPUT, uint8_t sensormode, uint8_t INT_PIN){
    if(sensormode >3) break; //Invalid Interrupt Mode
    GLBL_INTR = (1 << 7); //Set Bit for Global Interrupts
    if(PORT_OUTPUT == TRUE){
        INTR_PORT = 0x2B;
        //INT1 Map
        if (INT_PIN == 1){
            switch (sensormode){ 
                case 0: *EXT_INTR_CONTRL = 0; //low level
                case 1: *EXT_INTR_CONTRL = 4; //any change
                case 2: *EXT_INTR_CONTRL = 8; //falling level
                case 3: *EXT_INTR_CONTRL = 12; //rising level
            }
        }

        if (INT_PIN == 0){
            switch (sensormode){
                case 0: *EXT_INTR_CONTRL = 0; //low level
                case 1: *EXT_INTR_CONTRL = 1; //any change
                case 2: *EXT_INTR_CONTRL = 2; //falling level
                case 3: *EXT_INTR_CONTRL = 3; //rising level
            }
        }
    }
    if(PORT_OUTPUT == FALSE){
        INTR_PORT = 0x2A;
        *INTR_PORT = 0;
        INTR_PORT = 0x2B
    }
}

void SET_CLOCK_SRC(){

}

int main(){


    return 0;
}
