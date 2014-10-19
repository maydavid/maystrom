/**
maystrom 2014
david.may.muc@gmail.com
*/
#include "maystrom.h"

#include "hal/startup_hal.h"
#include "hal/notification_hal.h"
#include "hal/aquisition_hal.h"
#include "hal/promotion_hal.h"
#include "hal/communication_hal.h"
#include "hal/configuration_hal.h"



struct board_handle * bh;

volatile uint8_t do_aquisition;
volatile uint8_t do_promotion;

int main(void)
{
    int r;

    /* startup */
    r = startup_board(&bh);
    if (r>0) error(bh,"%s ERRNO: %i\n",__FUNCTION__,r);

    /* load configuration
    // SD-Card
    */
    initConfiguration(bh);
    debug(bh,"configuration init done\n");

    /* init local lcd menu
    // push button and timer interrupt
    */

    /* ctrl communication
    // interrupt based
    */
    initCommunication(bh);
    debug(bh,"communication init done\n");


    /* aquire data
    // timer based interupt
    */
    initAquisition(bh);
    debug(bh,"aquisition init done\n");


    /* promote data
    // timer based interrupt
    */
    initPromotion(bh);
    debug(bh,"promotion init done\n");


    while(1) {

        if (do_aquisition==1) {
            do_aquisition = 0;
            aquireData(bh);
        }

        if (do_promotion==1) {
            do_promotion=0;
            promoteData(bh);
        }

    }





}