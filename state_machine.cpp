#include "state_machine.h"

/**
 * @brief Resets the members of the screen_t
 * struct s, except for s->states->curr_state,
 * which is reset by the caller.
 * 
 * @param s, pointer to a screen_ struct
 */
void reset_state_machine (state_machine_t *s);

/**
 * @brief Switches the current state to HELP if a LONG button press is detected. 
 * Saves the previous state, clears the display for the help screen to load in.
 * @param screen struct pointer.
 */
void state_switch_to_help (state_machine_t *s);

/**
 * @brief 
 * 
 * @param s 
 */
void state_switch_from_help (state_machine_t *s);

/**
 * @brief 
 * 
 * @param s 
 * @param next_state 
 */
void init_buttons (state_machine_t *s, state next_state);

state_machine_t *create_state_machine () {
  state_machine_t *s = (state_machine_t *) malloc(sizeof(state_machine_t));
  if (s == NULL) {
    return NULL;
  }

  s->states = (state_t *) malloc(sizeof(state_t));
  if (s->states == NULL) {
    return NULL;
  }
  s->states->curr_state = WELCOME;
  s->states->prev_state = NULL;
  s->states->curr_state_accessed_from_help = false;
  s->states->pre_help_curr_state = NULL;
  s->states->pre_help_prev_state = NULL;
    
  s->pages = (page_t *) malloc(sizeof(page_t));
  if (s->pages == NULL) {
    return NULL;
  }
  s->pages->curr_page = 0;
  s->pages->last_page = 0;
    
  s->buttons = (button_t *) malloc(sizeof(button_t));
  if (s->buttons == NULL) {
    return NULL;
  }
  s->buttons->curr_button = 0;
  s->buttons->num_buttons = 2;
  s->buttons->button_press = NONE;
  s->buttons->hover_length = 30;
  s->buttons->hover_height = 10;

  s->tasks = (task_t *) malloc(sizeof(task_t));
  if (s->tasks == NULL) {
    return NULL;
  }
  s->tasks->difficulty_mode = FREE;
  s->tasks->task_status = NOT_STARTED;
  s->tasks->time_remaining = 0.0;

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
          if (s->states->curr_state_accessed_from_help == true) {
            s->states->curr_state_accessed_from_help = false;
          }
          break;
        case INSTRUCTIONS:
            s->states->curr_state_accessed_from_help = false;
          break;
        default:
          s->states->prev_state = s->states->curr_state;
          break;
      }
      s->states->curr_state = next_state;
      init_buttons(s,next_state);
      break;
    case LONG:
      state_switch_to_help(s);
      break;
  }
}

void state_switch_from_help (state_machine_t * s) {
  switch (s->buttons->curr_button) {
    case BACK_BTN:
      s->states->prev_state = s->states->pre_help_prev_state;
      break;
    case RESET_BTN:
      reset_state_machine(s); 
      break;
    default:
      s->states->curr_state_accessed_from_help = true;
      break;
  }
}

void state_switch_to_help (state_machine_t *s) {
  init_buttons(s,HELP);
  s->states->pre_help_prev_state = s->states->prev_state;
  s->states->pre_help_curr_state = s->states->curr_state;
  s->states->curr_state = HELP;
}

void init_buttons(state_machine_t *s, state next_state) {
  s->buttons->curr_button = 0;
  // Set number of buttons and height and width of hover on screen, resets task status to hide buttons while tasks in progress
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
      if (s->buttons->button_press == SINGLE) {
        if (s->pages->curr_page == 0) {
          s->pages->curr_page = s->pages->last_page;
        } else {
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
        if (s->pages->curr_page == s->pages->last_page) {
          s->pages->curr_page = 0;
        } else {
          s->pages->curr_page++;            
        }
      }
      break;
  }
}