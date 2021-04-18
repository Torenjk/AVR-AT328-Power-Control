//Tom Kamprath
//AVR AT328P Sleep mode
#include <stdio.h>

static uint8_t* SCR = 0x61; //SC Register
static uint8_t* MCU_BOD = 0x55; //BOD Bits in MCU Register
static uint8_t* MCU_STATUS = 0x55;

void SMC_SET(uint8_t SMC_MODE, bool BODS_DISABLE){
    if(SMC_MODE |<= 5 && SMC_MODE |>= 0) break; //Invalid Bits set

    if (BODS_DISABLE){
        *MCU_BOD = (1 << 7); 
        *MCU_BOD = (1 << 6); 
        *MCU_BOD = (0 << 8); //Not sure if this shifts right
    } 

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

int main(){
    SMC_SET(1,0) //Call this...
    return 0;
}
