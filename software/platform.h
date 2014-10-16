/** 
maystrom 2014
david.may.muc@gmail.com 
*/


#define HAS_ERROR_LED 1
#define ERROR_LED_PIN LED2

#define HAS_NOTIFICATION_LED 1
#define NOTIFICATION_LED_PIN LED1

#define HAS_SERIAL 1
#define SERIAL_TX_PIN USBTX
#define SERIAL_RX_PIN USBRX




#define HAS_SLCD 1
#define HAS_BLE 1

/* graphic lcd */
#define HAS_GLCD 1
/* glcd resolution */
#define GLCD_RESOLUTION "320X240"
/* glcd type */
#define GLCD_TYPE ILI9341

#define TFT_LCD_CS_PIN        PTB0
#define TFT_LCD_DC_PIN        PTB1
#define TFT_LCD_WR_PIN        PTB2
#define TFT_LCD_RD_PIN        PTB3
#define TFT_LCD_RESET_PIN     PTC2
#define TFT_LCD_IM0_PIN       PTC1

/* text lcd */
#define HAS_TLCD 0
/* tlcd resolution */
#define TLCD_RESOLUTION "2X16"
