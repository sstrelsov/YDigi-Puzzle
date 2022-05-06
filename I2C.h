#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <stdbool.h>

#include "states.h"

extern page page_no;

#define LEFT_INDENT 0
#define TOP 0
#define SMALL_TXT 1
#define MED_TXT 2

// Arrow Directions
#define LEFT 0
#define RIGHT 1

// WELCOME screen buttons (2 buttons)
#define NEXT_ARROW 1
#define ABOUT_BTN 0
#define ABOUT_CURSOR 55
#define ABOUT_HOVER_LENGTH 30
#define ABOUT_HOVER_HEIGHT 10

// ABOUT screen buttons (3 buttons)
#define LEFT_ARROW 0
#define EXIT_BTN 1
#define RIGHT_ARROW 2

// DIFFICULTY MODE screen buttons (4 buttons)
#define EASY_BTN 0
#define MED_BTN  1
#define HARD_BTN 2
#define FREE_MODE_BTN 3
#define EASY_CURSOR 20
#define MED_CURSOR 29
#define HARD_CURSOR 37
#define FREE_MODE_CURSOR 45
#define DIFFICULTY_MODE_HOVER_LENGTH 80
#define DIFFICULTY_MODE_HOVER_HEIGHT 9

// HELP screen buttons (3 buttons)
#define INSTR_BTN 1
#define RESET_BTN 2
#define BACK_BTN  3
#define ABOUT_HELP_CURSOR 20
#define INSTR_CURSOR 29
#define RESET_CURSOR 37
#define BACK_CURSOR 45
#define HELP_HOVER_LENGTH 80
#define HELP_HOVER_HEIGHT 9

// INSTRUCTIONS screen buttons (3 buttons)
#define BACK_INSTR 0
#define NEXT_INSTR 1
#define EXIT_INSTR 2

/* Initialize the display to get it ready to
 * show text. Begin the display, clear it, and
 * display a blank screen.
 */
void   I2C_init_display ();

/* Displays "Welcome" and allows the user to
 * proceed by clicking the right arrow or reading 
 * the about page. This screen corresponds to the
 * WELCOME state.
 */
void I2C_welcome_screen (int selector, int button_press, state *curr_state, state *prev_state);

/* Allows the user to read about the creation of the project:
 * who its creators are, where it got its name, and how to access 
 * the help screen for instructions and troubleshooting. Corresponds
 * to the ABOUT state.
 */
void I2C_about_screen (int selector, int button_press, state *curr_state, state *prev_state, page *page_no);

/* Displays the screen that allows the user to set
 * the puzzle box's difficulty using the rotary
 * encoder. Corresponds to the DIFFICULTY_MODE state.
 */
void I2C_difficulty_mode_screen (int selector, int button_press, state *curr_state, state *prev_state);

/* The "Help" screen is accessible at any time
 * during the program with a long press of the
 * rotary encoder button. It includes 4 options:
 * "Restart," which restarts the program from the
 * beginning, "Instructions," which includes
 * instructions about how to interact with the puzzle
 * box, and "Back," which returns the user back to the
 * screen that was live before they accessed "Help."
 */
void I2C_help_screen (int *selector, int button_press, state *curr_state, state *prev_state, page *page_no);

void I2C_instruction_selection_0 (int selector);
