#include "states.h"

void switch_to_help (int button_press, state *curr_state, state *prev_state) {
  if (button_press == LONG) {
    I2C_init_display();
    *prev_state = *curr_state;
    *curr_state = HELP;
  }
}

void instructions_sub_state_machine(int button_press, int selector) {
  I2C_init_display();
  I2C_instruction_selection_0(selector);
 // I2C_instruction_screen_1();
  switch (selector) {
    case NEXT_INSTR:
      break;
    case BACK_INSTR:
      break;
    case EXIT_INSTR:
      break;
    
  }
}
