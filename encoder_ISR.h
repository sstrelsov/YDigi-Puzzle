#ifndef __ENCODER_ISR_H__
#define __ENCODER_ISR_H__

#include <stdbool.h>
#include <Arduino.h>

#include "state_machine.h"
#include "init.h"
// SEE IF WE CAN ADD A PARAMETER TO ENCODER_ISR

/**
 * @brief This function serves as an interrupt service handler for the rotary encoder. Its
 * body is run every 10 milliseconds (ENCODER_DEBOUNCE_TIME). If the state of the rotary
 * encoder changes, it updates the value of the state_machine's curr_button member, informing
 * other functions about which virtual button/option the user is currently hovering over on the
 * I2C display.
 * 
 */
void encoder_ISR ();

#endif