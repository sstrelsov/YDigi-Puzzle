#include <SevSeg.h>

#include "init.h"
#include "state_machine.h"
#include "timer.h"

void setup() {
  init_timer_interrupt (); /* Initializes the registers to allow for TIMER_0 interrupt */
  init_I2C_display(); /* Initialize the I2C display, clearing screen and getting ready for content */
  init_rotary_encoder(); /* Set the a and b pins of encoder */
  init_encoder_button(); /* Set the button pin of the encoder to passive pullup */
  init_buzzer(); /* Initialize the buzzer to the proper pin */
  init_seven_segment(); /* TODO */
  
  // Help with interrupts from the Arduino tutorials: https://create.arduino.cc/projecthub/rafitc/interrupts-basics-f475d5
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), encoder_ISR, CHANGE); /* Attach an interrupt for a change in the encoderA pin, launching the encoder ISR */
}

// Create a state_machine struct to navigate the program
state_machine_t *state_machine = create_state_machine();

void loop() {
  // Poll the rotary encoder's button for either a single or a long press
  state_machine->buttons->button_press = read_button_press();
  // Switch the current state of the state machine based on user interactions
  switch (state_machine->states->curr_state) {
    case WELCOME:
      I2C_welcome_screen(state_machine);
      break;
    case ABOUT:
      I2C_about_screen(state_machine);
      break;
    case DIFFICULTY_MODE:
      I2C_difficulty_mode_screen(state_machine);
      break;
    case HELP:
      I2C_help_screen(state_machine);
      break;
    case INSTRUCTIONS:
     I2C_instruction_screen(state_machine);
     break;
    case CONFIRM_DIFFICULTY:
      I2C_confirmation_screen(state_machine);
      break;
    case TASK_1:
      I2C_task_1_screen(state_machine);
      break;
    case TASK_2:
      I2C_task_2_screen(state_machine);
      break;
    case TASK_3:
      // TODO: Change Task 3. Cannot enter numbers on 7-seg while it's counting down
      I2C_task_3_screen(state_machine);
      break;
    case GAME_LOST:
      I2C_game_lost_screen(state_machine);
      break;
    case GAME_WON:
      I2C_game_won_screen(state_machine);
      break;
    case END:
      I2C_end_screen(state_machine);
      break;
  }
}