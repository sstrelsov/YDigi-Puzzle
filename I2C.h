#ifndef __I2C_H__
#define __I2C_H__

#include <stdbool.h>

#include "state_machine.h"
#include "encoder_ISR.h"
#include "timer.h"
#include "SevSeg.h"

#define LEFT_INDENT 0
#define TOP 0
#define SMALL_TXT 1
#define MED_TXT 2

// Arrow Directions
#define LEFT 0
#define RIGHT 1

// WELCOME screen buttons (2 buttons)
#define ABOUT_BTN 0

// Multi-Page screen buttons (3 buttons)
#define LEFT_ARROW 2
#define EXIT_BTN 0
#define RIGHT_ARROW 1

// DIFFICULTY MODE screen buttons (4 buttons)
#define EASY_BTN 0
#define MED_BTN  1
#define HARD_BTN 2
#define FREE_MODE_BTN 3

// CONFIRM_DIFFICULTY screen buttons (2 buttons)
#define BACK_ARROW 1
#define START 0

// HELP screen buttons (3 buttons)
#define INSTR_BTN 1
#define RESET_BTN 2
#define BACK_BTN  3

/**
 * @brief Displays the screen for the WELCOME state,
 * allowing the user to proceed by clicking the right
 * arrow or reading the about page.
 * 
 * @param s, pointer to a screen_t struct.
 */
void I2C_welcome_screen (state_machine_t *s);

/**
 * @brief Displays the ABOUT state's screen. Allows the user to read
 * about the creation of the project: who its creators are,
 * where it got its name, and how to access the help screen for
 * instructions and troubleshooting.
 * 
 * @param s, pointer to a screen_t struct
 */
void I2C_about_screen (state_machine_t *s);

/**
 * @brief Displays DIFFICULTY_MODE's state screen.
 * Allows the user to set the puzzle box's difficulty
 * (easy, medium, hard, free mode) using the rotary encoder.
 * 
 * @param s, pointer to a screen_t struct
 */
void I2C_difficulty_mode_screen (state_machine_t *s);

/**
 * @brief 
 * 
 * @param s 
 */
void I2C_confirmation_screen (state_machine_t *s);

/**
 * @brief 
 * 
 * @param s 
 */
void I2C_task_1_screen (state_machine_t *s);

/**
 * @brief 
 * 
 * @param s 
 */
void I2C_task_2_screen (state_machine_t *s);

/**
 * @brief 
 * 
 * @param s 
 */
void I2C_task_3_screen (state_machine_t *s);

/**
 * @brief Displays the HELP state's screen. The "Help" screen
 * is accessible at any time during the program with a long press of the
 * rotary encoder button. It includes 4 options: "About,' which tells
 * users about the creation of the progra, "Restart," which restarts
 * the program from the beginning, "Instructions," which includes
 * instructions about how to interact with the puzzle box, and "Back,"
 * which returns the user back to the screen that was live before they accessed "Help."
 * 
 * @param s, pointer to a screen_t struct
 */
void I2C_help_screen (state_machine_t *s);

/**
 * @brief Displays the INSTRUCTION state's screen. The instruction
 * screen is accessible from the HELP state's screen at any point
 * in the program. It explains what the YDigi Puzzle is, as well as
 * the goals of each of the three tasks.
 * 
 * @param s, pointer to a screen_t struct
 */
void I2C_instruction_screen (state_machine_t *s);
/**
 * @brief 
 * 
 * @param dir 
 */
void hover_arrow (int dir);

/**
 * @brief 
 * 
 */
void hover_exit ();

/**
 * @brief 
 * 
 */
void hover_start ();

#endif