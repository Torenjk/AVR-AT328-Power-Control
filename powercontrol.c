//Tom Kamprath
//AVR AT328P Sleep mode
#include <stdio.h>

static uint8_t* SCR = 0x61; //SC Register
static uint8_t* MCU_BOD = 0x55; //BOD Bits in MCU Register
static uint8_t* MCU_STATUS = 0x55;
static uint8_t* PORTB_DATA = 0x25;
static uint8_t* PORTB_ROLE = 0x24;
static uint8_t* EXT_INTR_CONTRL = 0x69; //Interrupt Control Register
uint8_t* INTR_PORT = 0x0;
bool IntrAsOutp = 0; //Interrupt Pin can be Output too

void SMC_SET(uint8_t SMC_MODE, bool BODS_DISABLE){
    if(SMC_MODE |<= 5 && SMC_MODE |>= 0) break; //Invalid Bits set

    if (BODS_DISABLE){
        *MCU_BOD = (1 << 7); 
        *MCU_BOD = (1 << 6); 
        *MCU_BOD = (0 << 8); //Not sure if this shifts right
    } 

    //Todo: Change this to shift operation!
    switch (SMC_MODE){
        case 0: *SCR = 0; //IDLE
        case 1: *SCR = 2; //ADC
        case 2: *SCR = 4; //Power-down
        case 3: *SCR = 6; //Power-save
        case 4: *SCR = 12; //Standby
        case 5: *SCR = 14; //ext. Standby
    }

}

uint8_t MCU_RESET_SOURCE(){
    return *MCU_STATUS; //Get Reset Source
    *MCU_STATUS = 0; //Reset
}

void SET_INTERRUPT_RDY(bool PORT_OUTPUT, uint8_t sensormode){
    if(sensormode |<=3 && sensormode |>=0) break; //Invalid Interrupt Mode

    if(PORT_OUTPUT == TRUE){
        INTR_PORT = 0x2B;
        //Only call on PD3!
    }
    if(PORT_OUTPUT == FALSE){
        INTR_PORT = 0x2A;
        *INTR_PORT = 0;
        INTR_PORT = 0x2B
    }

    switch (sensormode){ 
        case 0: *EXT_INTR_CONTRL = 0; //low level
        case 1: *EXT_INTR_CONTRL = 4; //any change
        case 2: *EXT_INTR_CONTRL = 8; //falling level
        case 3: *EXT_INTR_CONTRL = 12; //rising level
    }
}

int main(){


    return 0;
}
