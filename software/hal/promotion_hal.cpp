#include "promotion_hal.h"

extern volatile uint8_t do_promotion;


int initPromotion(board_handle *bh)
{


    bh->promotionTicker = new Ticker();
    bh->promotionTicker->attach(&promoteDataISR,1.0);

    return 1;
}


void promoteDataISR(void)
{
    do_promotion = 1;

}


int promoteData(board_handle *bh)
{
    notify(bh,"promotion: %f\n",bh->data->temp);
    return 1;

}