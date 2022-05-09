#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include <Arduino.h>

#include "pins_setup.h"

#define DIG_ON LOW
#define DIG_OFF HIGH
#define DIG_BRIGHTNESS 5000
/* 7-Segment Display Setup
             A 
            ---
         F |   | B  
            ---  G 
         E |   | C 
            ---  
             D
*/

void light_up ();
void light_array_test ();

void set_easy_time ();

void set_med_time ();

void set_hard_time ();

#endif