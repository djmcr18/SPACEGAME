#include "space_game_b.h"
#include "splashkit.h"


// Load the game images, sounds, etc.
void load_resources_b()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

// Calculate the coordinates for a powerup on the minimap
point_2d mini_map_coordinate_powerup_b(const powerup_data_b &powerup)
{
    point_2d temp;
    float x = sprite_x(powerup.powerup_sprite);
    float y = sprite_y(powerup.powerup_sprite);
    
    // Map the x-coordinate to the range 650 to 800
    double mini_map_x = (x + 1500) / 3000.0 * 150 + 650;
    
    // Map the y-coordinate to the range 650 to 800
    double mini_map_y = (y + 1500) / 3000.0 * 150 + 650;
    
    // Create a point at the calculated coordinates
    temp = point_at(mini_map_x, mini_map_y);
    return temp;
}

// Draw the minimap with powerups and enemies
void draw_minimap_b(const vector<powerup_data_b> &powerups)
{
    // Draw powerups on the minimap
    for (int i = powerups.size() - 1; i >= 0; i--)
    {
        point_2d temp;
        temp = mini_map_coordinate_powerup_b(powerups[i]);
        
        // Draw a small rectangle representing the powerup
        fill_rectangle(COLOR_GREEN, temp.x, temp.y, 5, 5, option_to_screen());
    }
}

void draw_player_in_map_b(const player_data &player)
{
    // Declare a variable to store the player's coordinates on the minimap
    point_2d player_coordinate;

    // Declare a variable to store the color for the player's dot on the minimap
    color for_player;

    // Set the color for the player's dot to blue
    for_player = COLOR_BLUE;

    // Calculate the player's coordinates on the minimap based on their sprite position
    // Map the x-coordinate to the range 650 to 800
    // Map the y-coordinate to the range 650 to 800
    player_coordinate = point_at(((sprite_x(player.player_sprite) + 1500) / 3000 * 150 + 650), ((sprite_y(player.player_sprite) + 1500) / 3000 * 150 + 650));

    // Check if the player's sprite position is within the valid range on the minimap
    if (sprite_x(player.player_sprite) < MAX_b && sprite_x(player.player_sprite) > MIN_b && sprite_y(player.player_sprite) < 1500 && sprite_y(player.player_sprite) > -1500)
    {
        // Create a square for the player's dot on the minimap
        fill_rectangle(for_player, player_coordinate.x, player_coordinate.y, 8, 8, option_to_screen());
    }
}

// Draw the HUD
void draw_hud_b(game_data_b &game_b)
{
    // Draw the purple ellipse background for the top left section of the HUD
    fill_ellipse(COLOR_WHITE, 22, 22, 356, 106, option_to_screen());
    fill_ellipse(COLOR_MEDIUM_PURPLE, 25, 25, 350, 100, option_to_screen());

    // Determine the color for the SPEED text based on ship speed
    color speed_color = COLOR_WHITE;
    if (sprite_dx(game_b.player.player_sprite) == 0 && sprite_dy(game_b.player.player_sprite) == 0)
    {
        speed_color = COLOR_RED;
    }

    // Draw the labels/text in the HUD
    draw_text("LOCATION: " + point_to_string(center_point(game_b.player.player_sprite)), COLOR_WHITE, "PessStart2P", 9, 50, 70, option_to_screen());
    draw_text("SPEED: " + to_string_with_precision_b(sprite_speed(game_b.player.player_sprite), 1) + "km/s", speed_color, "PressStart2P", 9, 135, 95, option_to_screen());
    draw_text("TIME: " + to_string_with_precision_b(game_b.score_b.elapsed_time_b, 0) + "s", COLOR_WHITE, "PessStart2P", 10, 160, 45, option_to_screen());
    draw_text(to_string(game_b.score_b.battery_score_b), COLOR_GREEN, "PressStart2P", 30, 540, 740, option_to_screen());
    draw_text(to_string(game_b.score_b.diamond_score_b), COLOR_STEEL_BLUE, "PressStart2P", 30, 95, 740, option_to_screen());
    draw_text(to_string(game_b.score_b.cash_score_b), COLOR_GOLD, "PressStart2P", 30, 290, 740, option_to_screen());

    // Draw the icons in the HUD
    draw_bitmap("battery", 445, 702, option_scale_bmp(0.7, 0.7, option_to_screen()));
    draw_bitmap("diamond", -5, 700, option_scale_bmp(0.7, 0.7, option_to_screen()));
    draw_bitmap("cash", 195, 705, option_scale_bmp(0.7, 0.7, option_to_screen()));
    draw_bitmap("time", 425, -9, option_scale_bmp(0.4, 0.4, option_to_screen()));
    draw_bitmap("bar_grey_fill", 500, 20, option_to_screen());
    // Calculate the current width based on the elapsed time and depletion rate
    float orange_bar_width = bitmap_width("orange_bar") * (1.0 - (game_b.score_b.elapsed_time_b / 45));
    draw_bitmap("orange_bar", 500, 20, option_part_bmp(0, 0, orange_bar_width, bitmap_height("orange_bar"), option_to_screen()));

    // background for the minimap
    fill_rectangle(COLOR_MEDIUM_PURPLE, 642, 642, 160, 160, option_to_screen());
    fill_rectangle(COLOR_GRAY, 650, 650, 150, 150, option_to_screen());
    // display the minimap
    draw_minimap_b(game_b.powerups);
    draw_player_in_map_b(game_b.player);
};

// Create a new bonus game instance
game_data_b new_game_b()
{
    game_data_b game_b;
    game_b.player = new_player(); // Initialize the player
    game_b.score_b = new_score_data_b(); //Initialize score
    return game_b;
}

// Add a powerup to the game
void add_powerup_b(game_data_b &game_b)
{
    if (rnd() < 0.80) // Random chance of 80% to add a powerup
    {
        new_powerup_b(game_b.powerups, rnd(-1500, 1500), rnd(-1500, 1500)); // Create a new powerup at a random position
    }
}

// Remove a powerup from the game
void remove_powerup_b(game_data_b &game_b, int index)
{
    game_b.powerups.erase(game_b.powerups.begin() + index); // Remove the powerup at the specified index from the vector
}

void apply_powerup_b(game_data_b &game_b, int i)
{
    // Perform appropriate action based on powerup type
    switch (game_b.powerups[i].kind)
    {
        case CASH_b:
            play_sound_effect("cash_sound"); // Play the powerup sound
            // Add 100 to cash score and remove the powerup
            game_b.score_b.cash_score_b += 100;                    
            remove_powerup_b(game_b, i); 
            break;
        case BATTERY_b:
            play_sound_effect("battery_sound"); // Play the powerup sound
            // Add 1 to battery score and remove battery powerup
            game_b.score_b.battery_score_b += 1;
            remove_powerup_b(game_b, i);                    
            break;
        case DIAMOND_b:
            play_sound_effect("diamond_sound"); // Play the powerup sound
            // Add 1 to diamond score and removes the powerup
            game_b.score_b.diamond_score_b += 1;
            remove_powerup_b(game_b, i);                    
            break;
    }
}

void check_collisions_b(game_data_b &game_b)
{
    // Loop backwards through all score powerups in the game
    for (int i = game_b.powerups.size() - 1; i >= 0; i--)
    {
        // Check for collision with player sprite
        if (sprite_collision(game_b.player.player_sprite, game_b.powerups[i].powerup_sprite))
        {
            apply_powerup_b(game_b, i);
        }
    }
}

// Function to check if the bonus game should end
bool should_end_game_b(const game_data_b& game_b)
{
    // If the elapsed time is 45, the game should end
    if (game_b.score_b.elapsed_time_b >= 45.0)
    {
        return true;
    }

    // If the window close event has been triggered, the game should quit
    if (quit_requested())
    {
        return true;
    }

    return false;
}

// Function to draw the bonus game on the screen
void draw_game_b(game_data_b &game_b)
{
    // Draw the background of the game
    draw_bitmap("space_background", 0, 0, option_scale_bmp(2.3, 2.3, option_to_screen())); 
    draw_bitmap("space_background", 0, 400, option_scale_bmp(2.3, 2.3, option_to_screen()));
    draw_powerup_b(game_b.powerups); // Draw the powerups
    draw_hud_b(game_b);           // Draw the HUD (Heads-Up Display)
    draw_player(game_b.player); // Draw the player
    refresh_screen(60); // Refresh the screen at 60 frames per second
};

// Function to update the bonus game state
void update_game_b(game_data_b &game_b)
{
    add_powerup_b(game_b);          // Add new powerups to the game
    check_collisions_b(game_b);     // Check for collisions between player and powerups
    update_player(game_b.player); // Update the player's position
    update_powerup_b(game_b.powerups); // Update the powerups' positions
    update_elapsed_time_b(game_b.score_b); // Update the elapsed time of the game
};
