#include <xc.h>
#include <libpic30.h>
#include <stdio.h>

void debug_enable()
{
    __C30_UART=1;
}

