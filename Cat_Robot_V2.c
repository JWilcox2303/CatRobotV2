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

// PWM used for driving the DC motors
#include "hardware/pwm.h"

// DMA used for generating cat meow sounds
#include "hardware/dma.h"

// IRQ used for detecting optical signals
#include "hardware/irq.h"

/* May need ADC to convert optical signals from analog to digital,
but should not be necessary based on IR receiver schematic */
#include "hardware/adc.h"

// Include Custom Libraries, protothreads
#include "pt_cornell_rp2040_v1_3.h"

/* VARIABLES */

// Sine Table for Sound
#define sine_table_size 256
int raw_sin[sine_table_size];
unsigned short DAC_data[sine_table_size];

// A-channel, 1x, active
#define DAC_config_chan_A 0b0011000000000000

// DMA Variables
int data_chan;
int ctrl_chan;


/* FUNCTIONS */

/* INTERRUPTS*/

/* PROTOTHREADS */

static PT_THREAD(pt_blink(struct pt *pt)){
    PT_BEGIN(pt);
    while(1){
        printf("Hello, world!\n");
        gpio_put(25, true);
        sleep_ms(1000);
        gpio_put(25, false);
        sleep_ms(1000);
        PT_YIELD(pt);
    }
    PT_END(pt);
}

int main()
{
    stdio_init_all();
    gpio_init(25);
    gpio_set_dir(25, true);

    // This code is for meowing/audio which may not be included in the final implementation
    //
    // // Build sine table and DAC data table
    // int i;
    // for (i = 0; i < (sine_table_size); i++)
    // {
    //     raw_sin[i] = (int)(2047 * sin((float)i*6.283/(float)sine_table_size) + 2047); //12 bit
    //     DAC_data[i] = DAC_config_chan_A | (raw_sin[i] & 0x0fff);
    // }

    // // Select DMA channels
    // data_chan = dma_claim_unused_channel(true);
    
    // ctrl_chan = dma_claim_unused_channel(true);
    

    // // Setup the control channel
    // dma_channel_config c = dma_channel_get_default_config(ctrl_chan); // default configs
    // channel_config_set_transfer_data_size(&c, DMA_SIZE_32);           // 32-bit txfers
    // channel_config_set_read_increment(&c, false);                     // no read incrementing
    // channel_config_set_write_increment(&c, false);                    // no write incrementing
    // channel_config_set_chain_to(&c, data_chan);                       // chain to data channel

    // dma_channel_configure(
    //     ctrl_chan,                        // Channel to be configured
    //     &c,                               // The configuration we just created
    //     &dma_hw->ch[data_chan].read_addr, // Write address (data channel read address)
    //     &silly_address_pointer,           // Read address (POINTER TO AN ADDRESS)
    //     1,                                // Number of transfers
    //     false                             // Don't start immediately
    // );

    // // Setup the data channel
    // dma_channel_config c2 = dma_channel_get_default_config(data_chan); // Default configs
    // channel_config_set_transfer_data_size(&c2, DMA_SIZE_16);           // 16-bit txfers
    // channel_config_set_read_increment(&c2, true);                      // yes read incrementing
    // channel_config_set_write_increment(&c2, false);                    // no write incrementing
    // // (X/Y)*sys_clk, where X is the first 16 bytes and Y is the second
    // // sys_clk is 125 MHz unless changed in code. Configured to ~44 kHz
    // dma_timer_set_fraction(0, 0x0017, 0xffff);
    // // 0x3b means timer0 (see SDK manual)
    // channel_config_set_dreq(&c2, 0x3b); // DREQ paced by timer 0

    // dma_channel_configure(
    //     data_chan,                 // Channel to be configured
    //     &c2,                       // The configuration we just created
    //     &spi_get_hw(SPI_PORT)->dr, // write address (SPI data register)
    //     DAC_data,                  // The initial read address
    //     sine_table_size,           // Number of transfers
    //     false                      // Don't start immediately.
    // );

    pt_add_thread(pt_blink);
    pt_schedule_start;
}