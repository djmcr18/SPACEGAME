#include "score.h"
#include "splashkit.h"

// Function to convert a double value to a string with a specified precision
string to_string_with_precision(const double value, const int precision)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}

// Function to read a string from the user with a given prompt
string read_string(const string& prompt)
{
    write(prompt);           // Display the prompt to the user
    return read_line();      // Read a string from the user
}

// Function to create a new score data with initial values
score_data new_score_data()
{
    score_data score;

    score.cash_score = 0;     // Initialize cash score to 0
    score.diamond_score = 0;  // Initialize diamond score to 0
    score.battery_score = 0;  // Initialize battery score to 0
    score.elapsed_time = 0;   // Initialize elapsed time to 0

    return score;
}

// Procedure to update the elapsed time in the score data
void update_elapsed_time(score_data& score)
{
    static double start_time = -1;   // Starting time, initially set to -1

    if (start_time == -1)
    {
        start_time = current_ticks();   // Set the starting time when the function is first called
    }

    double current_time = current_ticks();   // Get the current time
    double elapsed_time = (current_time - start_time) / 1000;   // Calculate elapsed time in seconds

    score.elapsed_time = elapsed_time;   // Update the elapsed time in the score data
}

// Procedure to save the score data to a file
void save_score(const score_data& score)
{
    std::ofstream file("scores.txt", std::ios::app);   // Open the scores.txt file in append mode
    if (file)
    {
        file << score.cash_score << "," << score.diamond_score << ","
             << score.battery_score << "," << score.elapsed_time << "\n";
        file.close();
    }
    else
    {
        write_line("Error: Failed to open scores.txt for writing!");   // Display an error message if the file cannot be opened
    }
}

// Function to load the high score from a file
score_data load_high_score()
{
    score_data high_score;
    high_score.cash_score = INT_MIN;        // Initialize cash_score with minimum value
    high_score.diamond_score = INT_MIN;     // Initialize diamond_score with minimum value
    high_score.battery_score = INT_MIN;     // Initialize battery_score with minimum value
    high_score.elapsed_time = __DBL_MIN__;     // Initialize elapsed_time with minimum value

    std::ifstream file("scores.txt");   // Open the scores.txt file for reading
    if (file)
    {
        string line;
        while (getline(file, line))   // Read each line from the file
        {
            stringstream ss(line);

            int cash_score;
            int diamond_score;
            int battery_score;
            double elapsed_time;

            ss >> cash_score;    // Read cash_score
            ss.ignore();         // Ignore the comma separator
            ss >> diamond_score; // Read diamond_score
            ss.ignore();         // Ignore the comma separator
            ss >> battery_score; // Read battery_score
            ss.ignore();         // Ignore the comma separator
            ss >> elapsed_time;  // Read elapsed_time

            // Update high score if the current score is greater
            if (cash_score > high_score.cash_score)
            {
                high_score.cash_score = cash_score;
            }
            if (diamond_score > high_score.diamond_score)
            {
                high_score.diamond_score = diamond_score;
            }
            if (battery_score > high_score.battery_score)
            {
                high_score.battery_score = battery_score;
            }
            if (elapsed_time > high_score.elapsed_time)
            {
                high_score.elapsed_time = elapsed_time;
            }
        }
        file.close();
    }
    else
    {
        write_line("Error: Failed to open scores.txt for reading!");   // Display an error message if the file cannot be opened
    }

    return high_score;
}

// Procedure to restart the program
void restart_program()
{
    close_current_window();          // Close the current window
    system("./spacegame");           // Execute the spacegame executable
    exit(0);                         // Exit the current program
}

// Procedure to display the start screen
void display_start_screen(const score_data& score)
{
    // Load the high score
    score_data high_score = load_high_score();

    process_events();  // Process any pending events

    clear_screen(COLOR_BLACK);

    draw_bitmap("start_screen", 0, 0, option_scale_bmp(1, 1, option_to_screen()));  // Draw the start screen background image

    // Display start screen title text
    draw_text("SPACE GAME", COLOR_PURPLE, "PressStart2P", 45, screen_width() / 2 - 220, screen_height() / 2 - 340, option_to_screen());
    draw_text("Somehow the planets are chasing you and want you dead", COLOR_MEDIUM_PURPLE, "PressStart2P", 8, screen_width() / 2 - 210, screen_height() / 2 - 275, option_to_screen());
    draw_text("Like just grab some loot and run away bro seriously.", COLOR_MEDIUM_PURPLE, "PressStart2P", 8, screen_width() / 2 - 203, screen_height() / 2 - 252, option_to_screen());

    // Display rules
    draw_text("RULES", COLOR_LIGHT_PINK, "PressStart2P", 15, screen_width() / 2 - 250, screen_height() / 2 - 160, option_to_screen());
    draw_text(":  + 25% FUEL", COLOR_BRIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 - 250, screen_height() / 2 - 90, option_to_screen());
    draw_text(":  + 1 HEALTH", COLOR_BRIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 - 250, screen_height() / 2 - 40, option_to_screen());
    draw_text(":  + SCORE", COLOR_BRIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 - 250, screen_height() / 2 + 10, option_to_screen());
    draw_text(":  - 1 HEALTH", COLOR_RED, "PressStart2P", 9, screen_width() / 2 - 250, screen_height() / 2 + 60, option_to_screen());
    draw_text(":  - 2 HEALTH", COLOR_RED, "PressStart2P", 9, screen_width() / 2 - 250, screen_height() / 2 + 110, option_to_screen());
    draw_text(":  FREEZES ROCKET SHIP", COLOR_RED, "PressStart2P", 9, screen_width() / 2 - 250, screen_height() / 2 + 160, option_to_screen());

    // Draw icons
    draw_bitmap("fuel", screen_width() / 2 - 355, screen_height() / 2 - 140, option_scale_bmp(0.45, 0.45, option_to_screen()));
    draw_bitmap("heart", screen_width() / 2 - 357, screen_height() / 2 - 88, option_scale_bmp(0.45, 0.45, option_to_screen()));
    draw_bitmap("cash", screen_width() / 2 - 415, screen_height() / 2 - 35, option_scale_bmp(0.45, 0.45, option_to_screen()));
    draw_bitmap("diamond", screen_width() / 2 - 370, screen_height() / 2 - 35, option_scale_bmp(0.45, 0.45, option_to_screen()));
    draw_bitmap("battery", screen_width() / 2 - 325, screen_height() / 2 - 35, option_scale_bmp(0.45, 0.45, option_to_screen()));
    draw_bitmap("mars", screen_width() / 2 - 425, screen_height() / 2 - 17, option_scale_bmp(0.2, 0.2, option_to_screen()));
    draw_bitmap("jupiter", screen_width() / 2 - 418, screen_height() / 2 - 50, option_scale_bmp(0.15, 0.15, option_to_screen()));
    draw_bitmap("mercury", screen_width() / 2 - 368, screen_height() / 2 + 110, option_scale_bmp(0.2, 0.2, option_to_screen()));
    draw_bitmap("nos", screen_width() / 2 - 360, screen_height() / 2 + 63, option_scale_bmp(0.5, 0.5, option_to_screen()));

    draw_rectangle(COLOR_HOT_PINK, 401, 215, 360, 390);  // Draw a rectangle for high scores section

    // Display High Scores
    draw_text("HIGH SCORES TO BEAT", COLOR_LIGHT_PINK, "PressStart2P", 15, screen_width() / 2 + 37, screen_height() / 2 - 160, option_to_screen());
    draw_text("Highest Cash Score: " + to_string(high_score.cash_score), COLOR_LIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 + 73, screen_height() / 2 - 80, option_to_screen());
    draw_text("Highest Diamond Score: " + to_string(high_score.diamond_score), COLOR_LIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 + 68, screen_height() / 2, option_to_screen());
    draw_text("Highest Battery Score: " + to_string(high_score.battery_score), COLOR_LIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 + 68, screen_height() / 2 + 80, option_to_screen());
    draw_text("Longest Time Survived: " + to_string_with_precision(high_score.elapsed_time, 0) + " seconds", COLOR_LIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 + 28, screen_height() / 2 + 160, option_to_screen());

    // Display game selection options
    draw_text("Press 'SPACE' to Start Main Survival Game", COLOR_WHITE, "PressStart2P", 12, screen_width() / 2 - 253, screen_height() / 2 + 300, option_to_screen());
    draw_text("Press 'B' to Start Bonus Loot Run Mode", COLOR_WHITE, "PressStart2P", 12, screen_width() / 2 - 238, screen_height() / 2 + 350, option_to_screen());

    refresh_screen();  // Refresh the screen
}



// Display the end screen for a specific duration and then close the program
void display_end_screen(score_data& score)
{
    clear_screen(COLOR_BLACK);

    save_score(score);  // Save the player's score

    stop_sound_effect("game_music");  // Stop the game music
    play_sound_effect("gameover_sound");  // Play the gameover sound effect

    // Load the high score
    score_data high_score = load_high_score();

    while (!quit_requested())  // Continue until a quit event is requested
    {
        process_events();  // Process any pending events

        clear_screen(COLOR_BLACK);

        draw_bitmap("end_screen", -150, 0, option_scale_bmp(0.85, 0.85, option_to_screen()));  // Draw the end screen background image

        // Display end screen Title
        draw_text("GAME OVER", COLOR_RED, "PressStart2P", 40, screen_width() / 2 - 177, screen_height() / 2 - 320, option_to_screen());

        // Display the player's scores
        fill_rectangle(COLOR_RED, 54, 195, 305, 390, option_to_screen());  // Draw a rectangle for player's scores section
        fill_rectangle(COLOR_BLACK, 59, 200, 295, 380, option_to_screen());  // Draw a rectangle for player's scores section
        draw_text("YOUR SCORES", COLOR_LIGHT_PINK, "PressStart2P", 15, screen_width() / 2 - 275, screen_height() / 2 - 180, option_to_screen());
        draw_text("Cash Score: " + to_string(score.cash_score), COLOR_LIGHT_YELLOW, "PressStart2P", 9, screen_width() / 2 - 255, screen_height() / 2 - 100, option_to_screen());
        draw_text("Diamond Score: " + to_string(score.diamond_score), COLOR_LIGHT_YELLOW, "PressStart2P", 9, screen_width() / 2 - 260, screen_height() / 2 - 20, option_to_screen());
        draw_text("Battery Score: " + to_string(score.battery_score), COLOR_LIGHT_YELLOW, "PressStart2P", 9, screen_width() / 2 - 260, screen_height() / 2 + 60, option_to_screen());
        draw_text("Time Survived: " + to_string_with_precision(score.elapsed_time, 0) + " seconds", COLOR_LIGHT_YELLOW, "PressStart2P", 9, screen_width() / 2 - 310, screen_height() / 2 + 140, option_to_screen());

        // Display the high scores
        fill_rectangle(COLOR_RED, 407, 195, 340, 390, option_to_screen());  // Draw a rectangle for high scores section
        fill_rectangle(COLOR_BLACK, 412, 200, 330, 380, option_to_screen());  // Draw a rectangle for player's scores section
        draw_text("HIGH SCORES", COLOR_LIGHT_PINK, "PressStart2P", 15, screen_width() / 2 + 97, screen_height() / 2 - 180, option_to_screen());
        draw_text("Highest Cash Score: " + to_string(high_score.cash_score), COLOR_LIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 + 73, screen_height() / 2 - 100, option_to_screen());
        draw_text("Highest Diamond Score: " + to_string(high_score.diamond_score), COLOR_LIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 + 68, screen_height() / 2 - 20, option_to_screen());
        draw_text("Highest Battery Score: " + to_string(high_score.battery_score), COLOR_LIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 + 68, screen_height() / 2 + 60, option_to_screen());
        draw_text("Longest Time Survived: " + to_string_with_precision(high_score.elapsed_time, 0) + " seconds", COLOR_LIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 + 28, screen_height() / 2 + 140, option_to_screen());

        // Display text for quit and restart options
        draw_text("Press 'esc' to Exit", COLOR_WHITE, "PressStart2P", 11, screen_width() / 2 - 112, screen_height() / 2 + 340, option_to_screen());
        draw_text("Press 'R' to Restart", COLOR_WHITE, "PressStart2P", 11, screen_width() / 2 - 115, screen_height() / 2 + 300, option_to_screen());

        refresh_screen();

        while (true)  // Continue processing events until an action is taken
        {
            if (key_typed(R_KEY))  // If 'r' key is typed
            {
                restart_program();  // Restart the program
                return;
            }
            else if (key_typed(ESCAPE_KEY))  // If 'esc' key is typed
            {
                close_current_window();  // Close the current window
                exit(0);  // Exit the program
            }
            else if (quit_requested())  // If a quit event is requested
            {
                close_current_window();  // Close the current window
                exit(0);  // Exit the program
            }

            process_events();  // Process any pending events
        }
    }
}