#include "state_machine.h"

/**
 * @brief Helper function to state_switch() that resets the members of state_machine_t s,
 * except for s->states->curr_state, which is reset by the caller.
 * Function called upon reset from the HELP screen.
 * 
 * @param s pointer to a state machine 's'
 */
void reset_state_machine (state_machine_t *s);

/**
 * @brief Helper function to state_switch() that switches the current state to HELP if
 * a long button press is detected. Saves the pre-help current and previous
 * states to allow for the HELP state to act as an interrupt to the state
 * machine.
 * 
 * @param s pointer to state machine 's'
 */
void state_switch_to_help (state_machine_t *s);

/**
 * @brief Helper function to state_switch() that aids in the process of switching states
 * from the HELP screen. If the user selects 'Reset,' reset_state_machine() is called. If
 * the user selects 'Back,' the state machine switches to the pre-help current screen and
 * sets the state machine's previous screen as the pre-help prev_screen. If the user selects
 * any other option, it turns on the state machine struct's flag 'curr_state_accessed_from_help'
 * 
 * @param s pointer to state machine 's'
 */
void state_switch_from_help (state_machine_t *s);

/**
 * @brief Helper function that initializes the buttons for a specific screen. "Buttons" are
 * simulated virtual buttons on the screen controlled by the rotary encoder and its physical
 * button. Examples include forward and backwards arrows, EXIT buttons, START buttons, and
 * anything dynamic on the screens. Sets the number of buttons on the screen as well as the
 * length and height of the white rectangle that simulates a button hover.
 * 
 * @param s pointer to state machine 's'
 * @param next_state the next state from the state_switch() function's parameter. The next
 * state the state machine will switch to.
 */
void init_buttons (state_machine_t *s, state next_state);

state_machine_t *create_state_machine () {
  // Malloc space for state machine struct
  state_machine_t *s = (state_machine_t *) malloc(sizeof(state_machine_t));
  // Check if malloc was successful (returns NULL if unsuccessful)
  if (s == NULL) {
    return NULL;
  }

  // Malloc space for the state machine sub-struct 'states'
  s->states = (state_t *) malloc(sizeof(state_t));
  // Check if successful
  if (s->states == NULL) {
    return NULL;
  }
  // Set the current state to the welcome screen
  s->states->curr_state = WELCOME;
  s->states->prev_state = NULL;
  s->states->curr_state_accessed_from_help = false;
  s->states->pre_help_curr_state = NULL;
  s->states->pre_help_prev_state = NULL;
  
  // Malloc space for the state machine sub-struct 'pages'
  s->pages = (page_t *) malloc(sizeof(page_t));
  // Check if successful
  if (s->pages == NULL) {
    return NULL;
  }
  s->pages->curr_page = 0;
  s->pages->last_page = 0;

  // Malloc space for the state machine sub-struct 'buttons'
  s->buttons = (button_t *) malloc(sizeof(button_t));
  // Check if successful
  if (s->buttons == NULL) {
    return NULL;
  }
  // Set the buttons struct to the welcome screen's specifications
  s->buttons->curr_button = 0;
  s->buttons->num_buttons = 2; /* About and right arrow buttons on the welcome screen */
  s->buttons->button_press = NONE;
  s->buttons->hover_length = 30; /* Hover length covers the word 'About' */
  s->buttons->hover_height = 10; /* Hover height covers the smallest text size, 9 */

  // Malloc space for the state machine sub-struct 'tasks'
  s->tasks = (task_t *) malloc(sizeof(task_t));
  // Check if successful
  if (s->tasks == NULL) {
    return NULL;
  }
  // Set to free mode to start
  s->tasks->difficulty_mode = FREE;
  s->tasks->task_status = NOT_STARTED;
  s->tasks->time_remaining = 0.0;
  
  // Return the state machine 's'
  return s;
}

void reset_state_machine (state_machine_t *s) {
  // States
  s->states->prev_state = WELCOME;
  s->states->curr_state_accessed_from_help = false;
  s->states->pre_help_curr_state = NULL;
  s->states->pre_help_prev_state = NULL;
  // Pages
  s->pages->curr_page = 0;
  s->pages->last_page = 0;
  // Buttons
  s->buttons->curr_button = 0;
  s->buttons->num_buttons = 2;
  s->buttons->button_press = NONE;
  s->buttons->hover_length = 30;
  s->buttons->hover_height = 10;
  // Tasks
  s->tasks->task_status = NOT_STARTED;
  s->tasks->time_remaining = 0.0;

  // Timer
  timer_set_seconds(s);
}

void state_switch (state_machine_t *s, state next_state) {
  switch (s->buttons->button_press) {
    // With a single button press, update current state
    case SINGLE:
      switch (s->states->curr_state) {
        case HELP:
          state_switch_from_help(s);
          break;
        case GAME_LOST:
          reset_state_machine(s);
          break;
        case GAME_WON:
          reset_state_machine(s);
          break;
        case ABOUT:
          // About can be accessed from both the welcome and help screens. Determine where it is accessed.
          if (s->states->curr_state_accessed_from_help == true) {
            s->states->curr_state_accessed_from_help = false;
          }
          break;
        case INSTRUCTIONS:
            // Instructions only accessible from the HELP screen, so a state switch from instructions means that the current state is now help.
            s->states->curr_state_accessed_from_help = false;
          break;
        default:
          // Update the previous state to the current state before update the curent state to the next_state
          s->states->prev_state = s->states->curr_state;
          break;
      }
      // Update current state to the next state and initialize the button count on the next state's screen
      s->states->curr_state = next_state;
      init_buttons(s,next_state);
      break;
    // Long presses always switch to the help screen
    case LONG:
      state_switch_to_help(s);
      break;
  }
}

void state_switch_from_help (state_machine_t * s) {
  switch (s->buttons->curr_button) {
    case BACK_BTN:
      // Restore the prev_state to that before the help state was activated
      s->states->prev_state = s->states->pre_help_prev_state;
      break;
    case RESET_BTN:
      reset_state_machine(s); 
      break;
    default:
      // If not going back to the main state machine and not reset, then 'instructions' or 'about' was selected.
      s->states->curr_state_accessed_from_help = true;
      break;
  }
}

void state_switch_to_help (state_machine_t *s) {
  // Initialize the buttons to the help screen
  init_buttons(s,HELP);
  // Save the previous and current states from before the help interrupt was enabled
  s->states->pre_help_prev_state = s->states->prev_state;
  s->states->pre_help_curr_state = s->states->curr_state;
  // Switch current state to help
  s->states->curr_state = HELP;
}

void init_buttons(state_machine_t *s, state next_state) {
  s->buttons->curr_button = 0;
  // Set number of buttons and height and width of hover on screen
  switch (next_state) {
    case HELP:
      s->buttons->num_buttons = 4;
      s->buttons->hover_length = 80;
      s->buttons->hover_height = 9;
      break;
    case WELCOME:
      s->buttons->num_buttons = 2;
      s->buttons->hover_length = 30;
      s->buttons->hover_height = 10;
      break;
    case ABOUT:
      s->buttons->num_buttons = 3;
      break;
    case DIFFICULTY_MODE:
      s->buttons->num_buttons = 4;
      s->buttons->hover_length = 80;
      s->buttons->hover_height = 9;
      break;
    case CONFIRM_DIFFICULTY:
      s->buttons->num_buttons = 2;
      break;
    case INSTRUCTIONS:
      s->buttons->num_buttons = 3;
      break;
    case TASK_1:
      // Resets task status to not started in order to hide buttons while tasks in progress
      s->tasks->task_status = NOT_STARTED;
      s->buttons->num_buttons = 1;
      break;
    case TASK_2:
      s->tasks->task_status = NOT_STARTED;
      s->buttons->num_buttons = 1;
      break;
    case TASK_3:
      s->tasks->task_status = NOT_STARTED;
      s->buttons->num_buttons = 1;
      break;
    case GAME_LOST:
      s->buttons->num_buttons = 1;
      s->buttons->hover_length = 55;
      s->buttons->hover_height = 9;
      break;
    case GAME_WON:
      s->buttons->num_buttons = 1;
      break;
  }
}

void page_switch (state_machine_t *s) {
  switch (s->buttons->curr_button) {
    case LEFT_ARROW:
      hover_arrow(LEFT);
      // Check if button press is single for cycling through pages (as opposed to long)
      if (s->buttons->button_press == SINGLE) {
        // If on first page and user tries to go back, loop to the last page
        if (s->pages->curr_page == 0) {
          s->pages->curr_page = s->pages->last_page;
        } else {
          // Decrease the page count if not on first page
          s->pages->curr_page--;
        }
          }
          break;
    case EXIT_BTN:
      hover_exit();
      // If the current state was accessed from the help state, switch back to the help state. Don't use switch_to_help since we want to preserve the pre-help data
      if (s->states->curr_state_accessed_from_help == true) {
        state_switch(s,HELP);
      } else {
      // Otherwise return to previous state.
      state_switch(s,s->states->prev_state);
      }
      break;
    case RIGHT_ARROW:
      hover_arrow(RIGHT);
      if (s->buttons->button_press == SINGLE) {
        // If on the last page and user tries to advance, cycle back to the first page
        if (s->pages->curr_page == s->pages->last_page) {
          s->pages->curr_page = 0;
        } else {
          // If not on last page, increment the current page
          s->pages->curr_page++;            
        }
      }
      break;
  }
}