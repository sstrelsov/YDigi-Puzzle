#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <stdbool.h>
#include <Arduino.h>
#include "state_machine.h"
#include "pins_setup.h"

#define NONE   0
#define SINGLE 1
#define DUB    2
#define LONG   3

#define LONG_PRESS_TIME 400

int read_button_press ();
bool any_kind (int button_press);

#endif