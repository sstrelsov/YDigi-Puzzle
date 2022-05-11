#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__
#include "stdint.h"
#include "stdbool.h"
#include <Arduino.h>


typedef struct _state_machine_t state_machine_t;
typedef struct _state_t state_t;
typedef struct _page_t page_t;
typedef struct _button_t button_t;
extern state_machine_t *state_machine;

// Enumeration of all the different states
enum _state {
  WELCOME,
  ABOUT,
  DIFFICULTY_MODE,
  INSTRUCTIONS,
  HELP,
  RGB_PUZZLE,
  PHOTOCELL_PUZZLE,
  COMBO_LOCK_PUZZLE
};

typedef enum _state state;

struct _state_machine_t {
  state_t *states; /* Pointer to a struct that contains meta-data about the current and previous states */
  page_t *pages; /* Pointer to a struct that contains meta-data about the page information of the current state */
  button_t *buttons; /*Pointer to a struct that contains meta-data about the buttons being hovered over and pressed */
};

struct _state_t {
  state curr_state; /* The current state of the state machine */
  state prev_state; /* The previous state of the state machine */
  state pre_help_curr_state;
  state pre_help_prev_state;
};

struct _page_t {
  int curr_page; /* The page number of the current screen, if the state has multiple pages */
  int last_page; /* The page number of the last page within a certain state.*/
};

struct _button_t {
  int curr_button; /* Indicates which button is currently being hovered over */
  int num_buttons; /* The total number of buttons on a given screen */
  int button_press; /* Indicates whether a button is pressed, along with what type of press (SINGLE or LONG) */
  uint16_t hover_length; 
  uint16_t hover_height;
};

#include "I2C.h"
#include "button.h"
#include "encoder_ISR.h"

/**
 * @brief Switches the current state to HELP if a LONG button press is detected. 
 * Saves the previous state, clears the display for the help screen to load in.
 * @param screen struct pointer.
 */
void state_switch_to_help (state_machine_t *s);

/**
 * @brief Create a pointer to a screen_t struct, initializing each member
 * to the values of the WELCOME state – the first state in the program.
 * Sets the current and previous states to WELCOME, the page to PAGE_ZERO,
 * selector to 0, selector range to 2 (2 options on the WELCOME screen),
 * and the button press to NONE.
 * 
 * @return a pointer to a screen_t struct, NULL if allocation unsuccesful
 */
state_machine_t *create_state_machine ();

/**
 * @brief Switches the state from the current state to the next 
 * state, updating the screen_t struct s' curr_state and prev_state.
 * 
 * @param s, pointer to screen_t struct s
 * @param next_state, the next state to switch to
 */
void state_switch (state_machine_t *s, state next_state);

/**
 * @brief Switches the page from the current page to the next,
 * useful for states that include multiple pages. Pages are 
 * 0-indexed. For example, the ABOUT state's screen includes 3
 * different screens (pages) that the user can pan through, the
 * initial page being page 0.This function does not modify the
 * state_machine state, and the function that calls page_switch()
 * assigns s with the number of the last page.
 * 
 * @param s, pointer to screen_t struct s
 */
void page_switch (state_machine_t *s);

#endif
