#include <stdbool.h>
#include <arduino.h>
#include "states.h"
#include "pins.h"

extern int selector;
extern bool option_selected;
extern bool settings_screen;
extern int button_pin_prev;

extern state current_state;

#define NONE   0
#define SINGLE 1
#define DUB    2
#define LONG   3

#define LONG_PRESS_TIME 400

void button_init ();
int read_button_press ();
bool any_kind (int button_press);
