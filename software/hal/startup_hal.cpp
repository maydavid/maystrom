#include "startup_hal.h"
#include "notification_hal.h"



int startup_board(struct board_handle **bh) {
    
    
    struct board_handle *b = (struct board_handle*) calloc(1,sizeof(struct board_handle));
    if (!b) {
        return 1;
        }
        
    #if HAS_NOTIFICATION_LED
    b->notification_led = new DigitalOut(NOTIFICATION_LED_PIN);
    b->notification_led->write(0);
    #endif
    
    #if HAS_ERROR_LED
    b->error_led = new DigitalOut(ERROR_LED_PIN);
    b->error_led->write(1);
    #endif
        
    #if HAS_SERIAL
    b->pc = new Serial(SERIAL_TX_PIN, SERIAL_RX_PIN);
    #endif
    
    #if HAS_SLCD
    b->slcd = new SLCD;
    b->slcd->printf("boot");
    #endif
    
    
    #if HAS_GLCD 
    // startup graphical display
    #if (GLCD_TYPE == ILI9341)
    b->tft = new PARALLEL_TFT_ILI9341(TFT_LCD_CS_PIN,TFT_LCD_RESET_PIN,TFT_LCD_DC_PIN,TFT_LCD_WR_PIN,TFT_LCD_RD_PIN,TFT_LCD_IM0_PIN,PortE,PortC,2,3,6,16,17,18,19,31,0,4,6,7,10,11,13,16,"TFT");
    b->tft->set_orientation(1);
    b->tft->background(Black);    // set background to black
    b->tft->foreground(Black);    // set chars to white
    b->tft->cls();                // clear the screen
    b->tft->set_font((unsigned char*) Arial28x28);
    int i;
    for (i=0; i<256; i+=10) {
        b->tft->locate(50,100);
        b->tft->foreground(RGB(i,i,i));
        b->tft->printf("maystrom 2014\n");
    }
    #endif
    #endif
    
    #if HAS_TLCD
    // startup text display
    #endif
    
    #if HAS_BLE
    b->ble = new Serial(PTE22, PTE23); 
    b->ble->baud(57600);
    #endif
        
    
    *bh = b;
    
    notify(*bh,"startup done\n");
    return 0;
    }