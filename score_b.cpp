#include "score_b.h"
#include "splashkit.h"

// Function to convert a double value to a string with a specified precision
string to_string_with_precision_b(const double value, const int precision)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}

// Function to read a string from the user with a given prompt
string read_string_b(const string& prompt)
{
    write(prompt);           // Display the prompt to the user
    return read_line();      // Read a string from the user
}

// Function to create a new score data with initial values
score_data_b new_score_data_b()
{
    score_data_b score_b;

    score_b.cash_score_b = 0;     // Initialize cash score to 0
    score_b.diamond_score_b = 0;  // Initialize diamond score to 0
    score_b.battery_score_b = 0;  // Initialize battery score to 0
    score_b.elapsed_time_b = 0;   // Initialize elapsed time to 0

    return score_b;
}

// Procedure to update the elapsed time in the score data
void update_elapsed_time_b(score_data_b& score_b)
{
    static double start_time = -1;   // Starting time, initially set to -1

    if (start_time == -1)
    {
        start_time = current_ticks();   // Set the starting time when the function is first called
    }

    double current_time = current_ticks();   // Get the current time
    double elapsed_time_b = (current_time - start_time) / 1000;   // Calculate elapsed time in seconds

    score_b.elapsed_time_b = elapsed_time_b;   // Update the elapsed time in the score data
}

// Procedure to save the score data to a file
void save_score_b(const score_data_b& score_b)
{
    std::ofstream file("scores_b.txt", std::ios::app);   // Open the scores_b.txt file in append mode
    if (file)
    {
        file << score_b.cash_score_b << "," << score_b.diamond_score_b << ","
             << score_b.battery_score_b << "," << score_b.elapsed_time_b << "\n";
        file.close();
    }
    else
    {
        write_line("Error: Failed to open scores.txt for writing!");   // Display an error message if the file cannot be opened
    }
}

// Function to load the high score from a file
score_data_b load_high_score_b()
{
    score_data_b high_score_b;

    high_score_b.cash_score_b = INT_MIN;        // Initialize cash_score_b with minimum value
    high_score_b.diamond_score_b = INT_MIN;     // Initialize diamond_score_b with minimum value
    high_score_b.battery_score_b = INT_MIN;     // Initialize battery_score_b with minimum value
    high_score_b.elapsed_time_b = __DBL_MIN__;     // Initialize elapsed_time_b with minimum value

    std::ifstream file("scores_b.txt");   // Open the scores_b.txt file for reading
    if (file)
    {
        string line;
        while (getline(file, line))   // Read each line from the file
        {
            stringstream ss(line);

            int cash_score_b;
            int diamond_score_b;
            int battery_score_b;
            double elapsed_time_b;

            ss >> cash_score_b;    // Read cash_score_b
            ss.ignore();         // Ignore the comma separator
            ss >> diamond_score_b; // Read diamond_score_b
            ss.ignore();         // Ignore the comma separator
            ss >> battery_score_b; // Read battery_score_b
            ss.ignore();         // Ignore the comma separator
            ss >> elapsed_time_b;  // Read elapsed_time_b

            // Update high score if the current score is greater
            if (cash_score_b > high_score_b.cash_score_b)
            {
                high_score_b.cash_score_b = cash_score_b;
            }
            if (diamond_score_b > high_score_b.diamond_score_b)
            {
                high_score_b.diamond_score_b = diamond_score_b;
            }
            if (battery_score_b > high_score_b.battery_score_b)
            {
                high_score_b.battery_score_b = battery_score_b;
            }
            if (elapsed_time_b > high_score_b.elapsed_time_b)
            {
                high_score_b.elapsed_time_b = elapsed_time_b;
            }
        }
        file.close();
    }
    else
    {
        write_line("Error: Failed to open scores.txt for reading!");   // Display an error message if the file cannot be opened
    }

    return high_score_b;
}

// Procedure to restart the program
void restart_program_b()
{
    close_current_window();          // Close the current window
    system("./spacegame");           // Execute the spacegame executable
    exit(0);                         // Exit the current program
}

// Procedure to display the bonus game start screen
void display_start_screen_b(const score_data_b& score_b)
{
    play_sound_effect("bonus_game_music");  // Play the bonus game music    

    // Load the high score
    score_data_b high_score_b = load_high_score_b();
    
    while (!quit_requested())  // Continue until a quit event is requested
    {
        process_events();  // Process any pending events

        clear_screen(COLOR_BLACK);

        draw_bitmap("spacemoney", -1000, -505, option_scale_bmp(0.45, 0.45, option_to_screen()));  // Draw the start screen background image

        // Display start screen title text
        fill_rectangle(COLOR_GOLDENROD, 55, 30, 690, 180, option_to_screen());  // Draw a rectangle title frame
        fill_rectangle(COLOR_BLACK, 60, 35, 680, 170, option_to_screen());  // Draw a rectangle title frame
        draw_text("LOOT RUN", COLOR_GOLD, "PressStart2P", 45, screen_width() / 2 - 183, screen_height() / 2 - 340, option_to_screen());
        draw_text("Grab as much loot as you can in the 45 second time limit!", COLOR_GOLDENROD, "PressStart2P", 10, screen_width() / 2 - 292, screen_height() / 2 - 260, option_to_screen());
        draw_text("No enemies, no bombs, no damage and no fuel! Beat the high scores!", COLOR_GOLDENROD, "PressStart2P", 10, screen_width() / 2 - 330, screen_height() / 2 - 230, option_to_screen());

        // Display the high scores
        fill_rectangle(COLOR_GOLDENROD, 236, 265, 320, 320, option_to_screen());  // Draw a rectangle for high scores section
        fill_rectangle(COLOR_BLACK, 241, 270, 310, 310, option_to_screen());  // Draw a rectangle for high scores section
        draw_text("HIGH SCORES TO BEAT", COLOR_LIGHT_PINK, "PressStart2P", 15, screen_width() / 2 - 147, screen_height() / 2 - 110, option_to_screen());
        draw_text("Highest Cash Score: " + to_string(high_score_b.cash_score_b), COLOR_LIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 - 111, screen_height() / 2 - 30, option_to_screen());
        draw_text("Highest Diamond Score: " + to_string(high_score_b.diamond_score_b), COLOR_LIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 - 116, screen_height() / 2 + 50, option_to_screen());
        draw_text("Highest Battery Score: " + to_string(high_score_b.battery_score_b), COLOR_LIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 - 116, screen_height() / 2 + 130, option_to_screen());

        // Display press space to start message
        draw_text("Press 'SPACE' to Start", COLOR_WHITE, "PressStart2P", 12, screen_width() / 2 - 130, screen_height() / 2 + 310, option_to_screen());

        refresh_screen();  // Refresh the screen

        if (key_typed(SPACE_KEY))  // If SPACE key is typed
            {
                play_sound_effect("end_start_screen_sound");  // Play the end start screen sound effect
                break;  // Exit the loop and start the game
            }
    }
}

// Display the end screen
void display_end_screen_b(score_data_b& score_b)
{
    clear_screen(COLOR_BLACK);

    save_score_b(score_b);  // Save the player's score

    stop_sound_effect("bonus_game_music");  // Stop the game music
    play_sound_effect("gameover_sound");  // Play the gameover sound effect

    // Load the high score
    score_data_b high_score_b = load_high_score_b();

    while (!quit_requested())  // Continue until a quit event is requested
    {
        process_events();  // Process any pending events

        clear_screen(COLOR_BLACK);

        draw_bitmap("spacemoney", -1000, -505, option_scale_bmp(0.45, 0.45, option_to_screen()));  // Draw the end screen background image

        // Display end screen Title
        draw_text("TIME UP!!", COLOR_WHITE_SMOKE, "PressStart2P", 40, screen_width() / 2 - 177, screen_height() / 2 - 300, option_to_screen());

        // Display the player's scores
        fill_rectangle(COLOR_HOT_PINK, 65, 245, 285, 320, option_to_screen());  // Draw a rectangle for player's scores section
        fill_rectangle(COLOR_BLACK, 70, 250, 275, 310, option_to_screen());  // Draw a rectangle for player's scores section
        draw_text("YOUR SCORES", COLOR_LIGHT_PINK, "PressStart2P", 15, screen_width() / 2 - 275, screen_height() / 2 - 130, option_to_screen());
        draw_text("Cash Score: " + to_string(score_b.cash_score_b), COLOR_LIGHT_YELLOW, "PressStart2P", 9, screen_width() / 2 - 265, screen_height() / 2 - 50, option_to_screen());
        draw_text("Diamond Score: " + to_string(score_b.diamond_score_b), COLOR_LIGHT_YELLOW, "PressStart2P", 9, screen_width() / 2 - 270, screen_height() / 2 + 30, option_to_screen());
        draw_text("Battery Score: " + to_string(score_b.battery_score_b), COLOR_LIGHT_YELLOW, "PressStart2P", 9, screen_width() / 2 - 270, screen_height() / 2 + 110, option_to_screen());

        // Display the high scores
        fill_rectangle(COLOR_HOT_PINK, 420, 245, 320, 320, option_to_screen());  // Draw a rectangle for high scores section
        fill_rectangle(COLOR_BLACK, 425, 250, 310, 310, option_to_screen());  // Draw a rectangle for high scores section
        draw_text("HIGH SCORES", COLOR_LIGHT_PINK, "PressStart2P", 15, screen_width() / 2 + 97, screen_height() / 2 - 130, option_to_screen());
        draw_text("Highest Cash Score: " + to_string(high_score_b.cash_score_b), COLOR_LIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 + 73, screen_height() / 2 - 50, option_to_screen());
        draw_text("Highest Diamond Score: " + to_string(high_score_b.diamond_score_b), COLOR_LIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 + 68, screen_height() / 2 + 30, option_to_screen());
        draw_text("Highest Battery Score: " + to_string(high_score_b.battery_score_b), COLOR_LIGHT_GREEN, "PressStart2P", 9, screen_width() / 2 + 68, screen_height() / 2 + 110, option_to_screen());

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