/** 
maystrom 2014 
david.may.muc@gmail.com 
*/

#include "mbed.h"
#include "platform.h"

#include "hal/startup_hal.h"

#include "maystrom.h"


    

/*
void sendStatus() {
        ble->putc(0x00);
        ble->putc(0x11);
        ble->putc(rand());
    }
*/
int main(void)
{
    int r;
    //Ticker statusTicker;
    
    /* startup */
    struct board_handle * bh;

    
    r = startup_board(&bh);
    if (r>0) error("error at system startup. ERRNO: %i\n",r);
    
    
    
/*
    statusTicker.attach(&sendStatus,1.0);

    while (1) {
        if(ble->readable()) {
            pc.putc(ble->getc());
        }
    }
    
*/


}