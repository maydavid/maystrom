#include "aquisition_hal.h"

extern volatile uint8_t do_aquisition;

int initAquisition(board_handle *bh)
{

    bh->aquisitionTicker = new Ticker();
    bh->aquisitionTicker->attach(&aquireDataISR,bh->config->aquisitionInterval);

    bh->data = (struct data_handle*) calloc(1,sizeof(struct data_handle));

    return 1;
}

void aquireDataISR(void)
{
    do_aquisition = 1;
}

int aquireData(board_handle *bh)
{
    bh->data->temp = rand();
    return 1;
}