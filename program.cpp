// COMPILE AND RUN THE GAME AS "spacegame" (without the ""):
// skm g++ *.cpp -o spacegame

#include "splashkit.h"
#include "space_game.h"
#include "space_game_b.h"

game_data   game;
game_data_b game_b;

/**
 * The main function of the space game.
 */
int main()
{
    // Open the window and load the game resources
    open_window("Space Game", 800, 800);
    load_resources();

    clear_screen(COLOR_BLACK);

    play_sound_effect("start_screen_sound");  // Play the start screen sound effect

    // Display the start screen

    while (!quit_requested())  // Continue until a quit event is requested
    {
        display_start_screen(game.score);

        if (key_typed(SPACE_KEY))  // If SPACE key is typed
            {
                play_sound_effect("end_start_screen_sound");  // Play the end start screen sound effect
                play_sound_effect("game_music");  // Play the game music
                // Create the player and powerup objects
                game = new_game();

                // Game loop
                while (!should_end_game(game))
                {
                    process_events();
                    
                    // Handle player input
                    handle_input(game.player);

                    // Perform movement, update the camera and update the game state
                    update_game(game);

                    // Clear the screen
                    clear_screen(COLOR_BLACK);

                    // Draw the game
                    draw_game(game);
                }

                // Display the end screen
                display_end_screen(game.score);
            }
        else if (key_typed(B_KEY))
            {
                display_start_screen_b(game_b.score_b);

                play_sound_effect("end_start_screen_sound");  // Play the end start screen sound effect
                // Create the player and powerup objects
                game_b = new_game_b();

                // Game loop
                while (!should_end_game_b(game_b))
                {
                    process_events();
                    
                    // Handle player input
                    handle_input(game_b.player);

                    // Perform movement, update the camera and update the game state
                    update_game_b(game_b);

                    // Clear the screen
                    clear_screen(COLOR_BLACK);

                    // Draw the game
                    draw_game_b(game_b);
                }

                // Display the end screen
                display_end_screen_b(game_b.score_b);

            }
    }

    return 0;
}
