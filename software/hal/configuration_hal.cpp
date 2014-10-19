#include "configuration_hal.h"

int initConfiguration(board_handle *bh) {
    
    bh->config = (struct config_handle*) calloc(1,sizeof(struct config_handle));
    
    bh->config->aquisitionInterval = 1.0f;
    bh->config->promotionInterval = 1.0f;
    return 0;
    }