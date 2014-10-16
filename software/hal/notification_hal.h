#include "maystrom.h"
#include <cstdarg>

int notify(board_handle *bh,const char* format, ...);
int debug(board_handle *bh,const char* format, ...);
int error(board_handle *bh,const char* format, ...);