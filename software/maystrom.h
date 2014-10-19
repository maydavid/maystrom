#pragma once


#include "platform.h"
#include "mbed.h"
#include "SLCD.h"
#include "PARALLEL_TFT_ILI9341.h"
#include "fonts/SourceCodePro31.h"
#include "fonts/Arial28x28.h"
#include "fonts/Arial12x12.h"

struct config_handle {
    float aquisitionInterval;
    float promotionInterval;

};

struct data_handle {
    float temp;
};


struct board_handle {
    config_handle *config;
    data_handle *data;
    DigitalOut *notification_led;
    DigitalOut *error_led;
    SLCD *slcd;
    Serial *ble;
    Serial *pc;
    PARALLEL_TFT_ILI9341 *tft;
    Ticker * aquisitionTicker;
    Ticker * promotionTicker;
};




