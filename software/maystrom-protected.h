
#include "mbed.h"
#include "SLCD.h"
#include "PARALLEL_TFT_ILI9341.h"
#include "fonts/SourceCodePro31.h"
#include "fonts/Arial28x28.h"
#include "fonts/Arial12x12.h"

struct board_handle {
    
    SLCD *slcd;
    Serial *ble;
    Serial *pc;
    PARALLEL_TFT_ILI9341 *tft;
    };