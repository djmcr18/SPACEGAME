#ifndef SCORE_H_B
#define SCORE_H_B

#include <string>
#include "splashkit.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

/**
* @struct score_data_b
* Represents the score data containing cash score, diamond score, battery score,
* and elapsed time.
*/
struct score_data_b
{
    int cash_score_b; // Cash score
    int diamond_score_b; // Diamond score
    int battery_score_b; // Battery score
    double elapsed_time_b; // Elapsed time
};

/**
 * Converts a double value to a string with a specified precision.
 * @param value The double value to convert
 * @param precision The desired precision of the resulting string
 * @returns The converted string with the specified precision
 */
string to_string_with_precision_b(const double value, const int precision);

string read_string_b(const string& prompt);

/**
 * Initializes the score module by creating a new score_data_b object.
 * @returns The newly initialized score_data_b object
 */
score_data_b new_score_data_b();

/**
 * Updates the elapsed time of the score_data_b object based on the delta time.
 * @param score_b The score_data_b object to update the elapsed time for
 */
void update_elapsed_time_b(score_data_b& score_b);

/**
 * Saves the score_data_b object to a file for future retrieval.
 * @param score_b The score_data_b object to save
 */
void save_score_b(const score_data_b& score_b);

/**
 * Loads the high score from a file and returns it as a score_data_b object.
 * @returns The score_data_b object representing the loaded high score
 */
score_data_b load_high_score_b();

void display_start_screen_b(const score_data_b& score_b);

/**
 * Displays the end screen with the player's score and elapsed time.
 * @param score_b The score_data_b object containing the player's score and elapsed time
 */
void display_end_screen_b(score_data_b& score_b);

/**
 * Restarts the program by exiting the current window and starting a new instance.
 */
void restart_program();

#endif






