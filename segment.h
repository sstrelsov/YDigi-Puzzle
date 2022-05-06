#include "pins.h"
#include <arduino.h>

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


void segment_display_init ();
void light_up ();
void light_array_test ();

void set_easy_time ();

void set_med_time ();

void set_hard_time ();
