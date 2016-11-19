/**
 * @file functions.h
 * @author hbuyse
 * @date 26/12/2015
 */

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__


/**
 * @brief Turn a pin on during a certain delay, then turn the same pin off
 *
 * @param _pin The pin to ocontrol
 * @param _delay The delay to wait
 */
void turn_on_off(unsigned char _pin, unsigned long int _delay);
#endif          // __FUNCTIONS_H__