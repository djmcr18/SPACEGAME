#ifndef SCORE_H
#define SCORE_H

#include <string>
#include "splashkit.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

/**
* @struct score_data
* Represents the score data containing cash score, diamond score, battery score,
* and elapsed time.
*/
struct score_data
{
    int cash_score; // Cash score
    int diamond_score; // Diamond score
    int battery_score; // Battery score
    double elapsed_time; // Elapsed time
};

/**
 * Converts a double value to a string with a specified precision.
 * @param value The double value to convert
 * @param precision The desired precision of the resulting string
 * @returns The converted string with the specified precision
 */
string to_string_with_precision(const double value, const int precision);

/**
 * Initializes the score module by creating a new score_data object.
 * @returns The newly initialized score_data object
 */
score_data new_score_data();

/**
 * Updates the elapsed time of the score_data object based on the delta time.
 * @param score The score_data object to update the elapsed time for
 */
void update_elapsed_time(score_data& score);

/**
 * Saves the score_data object to a file for future retrieval.
 * @param score The score_data object to save
 */
void save_score(const score_data& score);

/**
 * Loads the high score from a file and returns it as a score_data object.
 * @returns The score_data object representing the loaded high score
 */
score_data load_high_score();

/**
 * Displays the end screen with the player's score and elapsed time.
 * @param score The score_data object containing the player's score and elapsed time
 */
void display_end_screen(score_data& score);

/**
 * Displays the start screen with the provided score_data object.
 * @param score The score_data object to display on the start screen
 */
void display_start_screen(const score_data& score);

/**
 * Restarts the program by exiting the current window and starting a new instance.
 */
void restart_program();
#endif /* SCORE_H */






