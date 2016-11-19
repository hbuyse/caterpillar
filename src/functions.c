/**
 * @file functions.c
 * @author hbuyse
 * @date 26/12/2015
 */

#include <wiringPi.h>          // digitalWrite, delay
#include <stdio.h>      // printf

void turn_on_off(unsigned char _pin,
                 unsigned long int  _delay
                 )
{
    #ifdef __DEBUG__
    printf("[%s] turn_on_off(%u, %lu)\n", __FUNCTION__, _pin, _delay);
    #endif

    digitalWrite(_pin, HIGH);
    delay(_delay);
    digitalWrite(_pin, LOW);
}