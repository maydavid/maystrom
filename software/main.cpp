/** 
maystrom 2014 
david.may.muc@gmail.com 
*/
#include "maystrom.h"

#include "hal/startup_hal.h"
#include "hal/notification_hal.h"
#include "hal/lcdmenu_hal.h"


    

struct board_handle * bh;

void sendStatus() {
        uint8_t type=0;
        bh->ble->putc(type);
        bh->ble->putc(rand());
    }

int main(void)
{
    int r;
    Ticker statusTicker;
    
    /* startup */ 
    r = startup_board(&bh);
    if (r>0) error(bh,"%s ERRNO: %i\n",__FUNCTION__,r);
    
    
    

    statusTicker.attach(&sendStatus,1.0);
    
    while (1) {}
/*
    while (1) {
        if(ble->readable()) {
            pc.putc(ble->getc());
        }
    }
    
*/


}