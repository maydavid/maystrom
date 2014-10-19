#include "communication_hal.h"


void pcSerialRx(void) {
    
    
    }

void bleSerialRx(void) {
    
    
    
    }

int initCommunication(board_handle *bh) {
    
    // attach interrupts
    bh->pc->attach(&pcSerialRx);
    bh->ble->attach(&bleSerialRx); 
    return 0;
    }