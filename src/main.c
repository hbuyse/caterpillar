/**
 * @file main.c
 * @author hbuyse
 * @date 26/12/2015
 */

#include <functions.h>  // turn_on_off
#include <wiringPi.h>   // wiringPiSetupGpio, pinMode
#include <stdio.h>  // printf
#include <signal.h>  //signal
#include <stdlib.h> //exit


#define WHITE 17
#define BLUE 18
#define YELLOW 27
#define RED 22
#define GREEN 23

#define DELAY 1000

static unsigned char tab_pins[] = {WHITE, BLUE, YELLOW, RED, GREEN};


static void sigint_handler(int signal __attribute__((unused))) {
    unsigned int i = 0;

    // Turn off all LEDS
    for (i = 0; i < (sizeof(tab_pins) / sizeof(unsigned char)); ++i)
    {
        #ifdef __DEBUG__
        printf("[%s] digitalWrite(%d, LOW)\n", __FUNCTION__, tab_pins[i]);
        #endif

        digitalWrite(tab_pins[i], LOW);
    }

    exit(0);
}


int main(void)
{
    signal(SIGINT, sigint_handler);
    unsigned int i = 0;

    /* SETUP FUNCTIONS
     *
     * There are three ways to initialise wiringPi.
     *
     *  * int wiringPiSetup (void) ;
     *  * int wiringPiSetupGpio (void) ;
     *  * int wiringPiSetupSys (void) ;
     *
     * One of the setup functions must be called at the start of your program. If it returns -1 then the initialisation
     * of the GPIO has failed, and you should consult the global errno to see why.
     *
     * The differences between the setup functions are as follows:
     *  * wiringPiSetup(void) ;
     *    This initialises the wiringPi system and assumes that the calling program is going to be using the wiringPi
     *    pin numbering scheme. This is a simplified numbering scheme which provides a mapping from virtual pin numbers
     *    0 through 16 to the real underlying Broadcom GPIO pin numbers. See the pins page for a table which maps the
     *    wiringPi pin number to the Broadcom GPIO pin number to the physical location on the edge connector.
     *
     *    This function needs to be called with root privileges.
     *
     *  * wiringPiSetupGpio(void) ;
     *    This is identical to above, however it allows the calling programs to use the Broadcom GPIO pin numbers
     *    directly with no re-mapping.
     *
     *    As above, this function need to be called with root priveledges
     *
     *  * wiringPiSetupSys(void)
     *    This initialises the wiringPi system but uses the /sys/class/gpio interface rather than accessing the hardware
     *    directly. This can be called as a non-root user provided the GPIO pins have been exported before-hand using
     *    the gpio program. Pin number in this mode is the native Broadcom GPIO numbers.
     *
     *    Note: In this mode you can only use the pins which have been exported via the /sys/class/gpio interface. You
     *    must export these pins before you call your program. You can do this in a separate shell-script, or by using
     *    the system() function from inside your program.
     *
     *    Also note that some functions (noted below) have no effect when using this mode as they’re not currently
     *    possible to action unless called with root privileges.
     */
    wiringPiSetupGpio();


    /* void pinMode (int pin, int mode) ;
     * This sets the mode of a pin to either INPUT, OUTPUT, or PWM_OUTPUT. Note that only wiringPi pin 1 (BCM_GPIO 18)
     * supports PWM output. The pin number is the number obtained from the pins table.
     *
     * This function has no effect when in Sys mode.
     */
    for (i = 0; i < (sizeof(tab_pins) / sizeof(unsigned char)); ++i)
    {
        #ifdef __DEBUG__
        printf("[%s] pinMode(%d, OUTPUT)\n", __FUNCTION__, tab_pins[i]);
        #endif

        pinMode(tab_pins[i], OUTPUT);
    }


    for (i = 0; i < (sizeof(tab_pins) / sizeof(unsigned char)); ++i)
    {
        #ifdef __DEBUG__
        printf("[%s] digitalWrite(%d, LOW)\n", __FUNCTION__, tab_pins[i]);
        #endif

        digitalWrite(tab_pins[i], LOW);
    }

    /*
     * void digitalWrite (int pin, int value) ;
     * Writes the value HIGH or LOW (1 or 0) to the given pin which must have been previously set as an output.
     */
    for ( ; ; )
    {
        for (i = 0; i < (sizeof(tab_pins) / sizeof(unsigned char)); ++i)
        {
            turn_on_off(tab_pins[i], DELAY);
        }
    }

    return (0);
}
