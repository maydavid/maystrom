/** 
maystrom 2014
david.may.muc@gmail.com 
*/


#define TFT_LCD_CS_PIN        PTB0
#define TFT_LCD_DC_PIN        PTB1
#define TFT_LCD_WR_PIN        PTB2
#define TFT_LCD_RD_PIN        PTB3
#define TFT_LCD_RESET_PIN     PTC2
#define TFT_LCD_IM0_PIN       PTC1

#define HAS_SERIAL 1
#define HAS_SLCD 1
#define HAS_BLE 1

/* graphic lcd */
#define HAS_GLCD 1
/* glcd resolution */
#define GLCD_RESOLUTION "320X240"

/* text lcd */
#define HAS_TLCD 0
/* tlcd resolution */
#define TLCD_RESOLUTION "2X16"
