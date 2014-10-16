#include "notification_hal.h"


int notify(board_handle *bh,const char* format, ...)
{   
    char buffer[200]= {0};
    va_list argp;
    va_start(argp, format);
    vsnprintf(buffer,200,format, argp);
    int r;
    #if HAS_SERIAL
    r = bh->pc->printf("@N: %s",buffer);
    #endif
    #if HAS_GLCD
    
    #endif
    return r;

}

int debug(board_handle *bh,const char* format, ...)
{   
    char buffer[200]= {0};
    va_list argp;
    va_start(argp, format);
    vsnprintf(buffer,200,format, argp);
    int r;
    #if HAS_SERIAL
    r = bh->pc->printf("@D: %s",buffer);
    #endif
    return r;
}


int error(board_handle *bh,const char* format, ...)
{   
    char buffer[200]= {0};
    va_list argp;
    va_start(argp, format);
    vsnprintf(buffer,200,format, argp);
    int r;
    #if HAS_SERIAL
    r = bh->pc->printf("@E: %s",buffer);
    #endif
    #if HAS_ERROR_LED
    bh->error_led->write(0);
    #endif
    return r;
}