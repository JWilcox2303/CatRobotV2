/**
 * Cat Robot Software Version 2
 * 
 * Charlie Wright (caw352@cornell.edu)
 * Jeff Wilcox (jtw88@cornell.edu)
 * Lauren Lee (lsl88@cornell.edu)
 * 
 * This project uses IR receivers, DC motors, and servo motors to detect the direction of optical signals from targets and
 * move towards them. An LCD screen will be used to emulate the face of a cat and a DAC will be used to generate meowing
 * sounds.
 * 
 * HARDWARE CONNECTIONS
 *  - GPIO XX ---> What does this connect to?
 */

/* LIBRARY IMPORTS */

// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// PICO Libraries
#include "pico/stdlib.h"
#include "pico/multicore.h"

// PWM used for driving the DC and servo motors
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "servo.h"
// #include "servoObject.h"

// IRQ used for detecting optical signals
#include "hardware/irq.h"

//PIO for LCD SPI interface
#include "hardware/pio.h"

/* May need ADC to convert optical signals from analog to digital,
but should not be necessary based on IR receiver schematic */
#include "hardware/adc.h"

// Include Custom Libraries, protothreads
#include "pt_cornell_rp2040_v1_3.h"


/* VARIABLES */

// IR Detector Variables


// DC Motor Variables
/**
 * RELEVANT HARDWARE CONNECTIONS
 *  Motor Controller for Side
 *  - GPIO 18 () ---> AIN1
 *  - GPIO 19 () ---> AIN2
 *  - GPIO 20 () ---> BIN1
 *  - GPIO 21 () ---> BIN2
 *  - MCU GND (Pin 18) ---> GND
 *  - GPIO 17 () ---> SLP
 */

// Servo Motor Variables
#define servoPin 16
int currentMillis = 2400;
bool direction = true;

// LCD Screen Variables
/**
 * We should use landscape mode with the VGA which requires setting rotation mode to 1
 * 
 */


/* FUNCTIONS */
void servoTest(){
    currentMillis += (direction)?200:-200;
    if (currentMillis >= 2400){
        direction = false;
        currentMillis = 2400;
    }
    if (currentMillis <= 400){
        direction = true;
        currentMillis = 400;
    }
    setMillis(servoPin, currentMillis);
}


/* INTERRUPTS*/

/* PROTOTHREADS */

static PT_THREAD(pt_blink_servo(struct pt *pt)){
    PT_BEGIN(pt);
    setServo(servoPin, currentMillis);
    while(1){
        // printf("Hello, world!\n");
        gpio_put(25, true);
        sleep_ms(15);
        gpio_put(25, false);
        sleep_ms(15);

        servoTest();
        printf("%d", currentMillis);

        PT_YIELD(pt);
    }
    PT_END(pt);
}

// static PT_THREAD(pt_servo(struct pt *pt)){
//     PT_BEGIN(pt);
//     while(1){

//         sleep_ms(10);

//         PT_YIELD(pt);
//     }
//     PT_END(pt);
// }

int main()
{
    stdio_init_all();
    gpio_init(servoPin);
    gpio_set_dir(servoPin, true);
    gpio_init(25);
    gpio_set_dir(25, true);

    pt_add_thread(pt_blink_servo);
    pt_schedule_start;

    //Servo initializing
}