#include "space_game.h"
#include "splashkit.h"

/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

float HPBAR = 0.142858;

// Calculate the coordinates for a powerup on the minimap
point_2d mini_map_coordinate_powerup(const powerup_data &powerup)
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

// Calculate the coordinates for an enemy on the minimap
point_2d mini_map_coordinate_enemy(const enemy_data &enemy)
{
    point_2d temp;
    float x = sprite_x(enemy.enemy_sprite);
    float y = sprite_y(enemy.enemy_sprite);
    
    // Map the x-coordinate to the range 650 to 800
    double mini_map_x = (x + 1500) / 3000.0 * 150 + 650;
    
    // Map the y-coordinate to the range 650 to 800
    double mini_map_y = (y + 1500) / 3000.0 * 150 + 650;
    
    // Create a point at the calculated coordinates
    temp = point_at(mini_map_x, mini_map_y);
    return temp;
}

// Draw the minimap with powerups and enemies
void draw_minimap(const vector<powerup_data> &powerups, const vector<enemy_data> &enemies)
{
    // Draw powerups on the minimap
    for (int i = powerups.size() - 1; i >= 0; i--)
    {
        point_2d temp;
        temp = mini_map_coordinate_powerup(powerups[i]);
        
        // Draw a small rectangle representing the powerup
        fill_rectangle(COLOR_GREEN, temp.x, temp.y, 5, 5, option_to_screen());
    }

    // Draw enemies on the minimap
    for (int i = enemies.size() - 1; i >= 0; i--)
    {
        point_2d temp;
        temp = mini_map_coordinate_enemy(enemies[i]);
        
        // Draw a small rectangle representing the enemy
        fill_rectangle(COLOR_RED, temp.x, temp.y, 5, 5, option_to_screen());
    }
}

void draw_player_in_map(const player_data &player)
{
    point_2d player_coordinate;
    color for_player;
    for_player = COLOR_BLUE;
    player_coordinate = point_at(((sprite_x(player.player_sprite) + 1500) / 3000 * 150 + 650), ((sprite_y(player.player_sprite) + 1500) / 3000 * 150 + 650));
    if (sprite_x(player.player_sprite) < MAX && sprite_x(player.player_sprite) > MIN && sprite_y(player.player_sprite) < 1500 && sprite_y(player.player_sprite) > -1500)
    {
        // Increase the size of the rectangle
        fill_rectangle(for_player, player_coordinate.x, player_coordinate.y, 8, 8, option_to_screen());
    }
}

// Draw the HUD
void draw_hud(game_data &game)
{
    // Draw the purple ellipse background for the top left section of the HUD
    fill_ellipse(COLOR_WHITE, 22, 22, 356, 106, option_to_screen());
    fill_ellipse(COLOR_MEDIUM_PURPLE, 25, 25, 350, 100, option_to_screen());

    // Determine the color for the SPEED text based on ship speed
    color speed_color = COLOR_WHITE;
    if (sprite_dx(game.player.player_sprite) == 0 && sprite_dy(game.player.player_sprite) == 0)
    {
        speed_color = COLOR_RED;
    }
    // Draw the labels/text in the HUD

    draw_text("LOCATION: " + point_to_string(center_point(game.player.player_sprite)), COLOR_WHITE, "PessStart2P", 9, 50, 70, option_to_screen());
    draw_text("SPEED: " + to_string_with_precision(sprite_speed(game.player.player_sprite), 1) + "km/s", speed_color, "PressStart2P", 9, 135, 95, option_to_screen());
    draw_text("TIME: " + to_string_with_precision(game.score.elapsed_time, 0) + "s", COLOR_WHITE, "PessStart2P", 10, 160, 45, option_to_screen());
    draw_text(to_string(game.score.battery_score), COLOR_GREEN, "PressStart2P", 30, 540, 740, option_to_screen());
    draw_text(to_string(game.score.diamond_score), COLOR_STEEL_BLUE, "PressStart2P", 30, 95, 740, option_to_screen());
    draw_text(to_string(game.score.cash_score), COLOR_GOLD, "PressStart2P", 30, 290, 740, option_to_screen());

    // Draw the icons in the HUD
    draw_bitmap("battery", 445, 702, option_scale_bmp(0.7, 0.7, option_to_screen()));
    draw_bitmap("diamond", -5, 700, option_scale_bmp(0.7, 0.7, option_to_screen()));
    draw_bitmap("cash", 195, 705, option_scale_bmp(0.7, 0.7, option_to_screen()));
    draw_bitmap("fuel", 425, -9, option_scale_bmp(0.4, 0.4, option_to_screen()));
    draw_bitmap("heart", 425, 43, option_scale_bmp(0.4, 0.4, option_to_screen()));
    draw_bitmap("bar_grey_fill", 500, 20, option_to_screen());
    float orange_bar_width = bitmap_width("orange_bar") * game.player.fuel_pct;
    draw_bitmap("orange_bar", 500, 20, option_part_bmp(0, 0, orange_bar_width, bitmap_height("orange_bar"), option_to_screen()));
    draw_bitmap("bar_grey_fill", 500, 70, option_to_screen());
    float green_bar_lines_width = bitmap_width("green_bar_lines") * game.player.health_pct;
    draw_bitmap("green_bar_lines", 500, 70, option_part_bmp(0, 0, green_bar_lines_width, bitmap_height("green_bar_lines"), option_to_screen()));

    //background for the minimap bar
    fill_rectangle(COLOR_MEDIUM_PURPLE, 642, 642, 160, 160, option_to_screen());
    fill_rectangle(COLOR_GRAY, 650, 650, 150, 150, option_to_screen());
    //displaying  for the minimap
    draw_minimap(game.powerups, game.enemies);
    draw_player_in_map(game.player);
};

// Create a new game instance
game_data new_game()
{
    game_data game;
    game.player = new_player(); // Initialize the player
    game.score = new_score_data(); //Initialize score
    return game;
}

// Add a powerup to the game
void add_powerup(game_data &game)
{
    if (rnd() < 0.05) // Random chance of 5% to add a powerup
    {
        new_powerup(game.powerups, rnd(-1500, 1500), rnd(-1500, 1500)); // Create a new powerup at a random position
    }
}

// Add a enemy to the game
void add_enemy(game_data &game)
{
    if (rnd() < 0.025) // Random chance of 2.5% to add an enemy
    {
        new_enemy(game.enemies, rnd(-1500, 1500), rnd(-1500, 1500)); // Create a new enemy at a random position
    }
}

// Remove a powerup from the game
void remove_powerup(game_data &game, int index)
{
    game.powerups.erase(game.powerups.begin() + index); // Remove the powerup at the specified index from the vector
}

// Remove a powerup from the game
void remove_enemy(game_data &game, int index)
{
    game.enemies.erase(game.enemies.begin() + index); // Remove the powerup at the specified index from the vector
}

void apply_powerup(game_data &game, int i)
{
    // Perform appropriate action based on powerup type
    switch (game.powerups[i].kind)
    {
        case FUEL:
            play_sound_effect("fuel_sound"); // Play the powerup sound
            // Add 25% fuel to the player and removes the fuel powerup
            game.player.fuel_pct += 0.25;
            if (game.player.fuel_pct > 1.0)
            {
                game.player.fuel_pct = 1.0;
            }
            remove_powerup(game, i);
            break;
        case HEART:
            play_sound_effect("heart_sound"); // Play the powerup sound
            // Add 1/7 to health_pct and remove the powerup
            game.player.health_pct += HPBAR;
            if (game.player.health_pct > 1.0)
            {
                game.player.health_pct = 1.0;
            }
            remove_powerup(game, i);
            break;
        case CASH:
            play_sound_effect("cash_sound"); // Play the powerup sound
            // Add 100 to cash score and remove the powerup
            game.score.cash_score += 100;                    
            remove_powerup(game, i); 
            break;
        case BATTERY:
            play_sound_effect("battery_sound"); // Play the powerup sound
            // Add 1 to battery score and remove battery powerup
            game.score.battery_score += 1;
            remove_powerup(game, i);                    
            break;
        case DIAMOND:
            play_sound_effect("diamond_sound"); // Play the powerup sound
            // Add 1 to diamond score and removes the powerup
            game.score.diamond_score += 1;
            remove_powerup(game, i);                    
            break;
        case NOS:
            play_sound_effect("nos_sound"); // Play the nos explosion sound
            // Remove 2/7 from health_pct and remove the powerup
            game.player.health_pct -= HPBAR * 2;
            if (game.player.health_pct < 0.0)
            {
                game.player.health_pct = 0.0;
            }
            remove_powerup(game, i);
            break;
    }
}

void apply_enemy(game_data &game, int i)
{
    // Perform appropriate action based on powerup type
    switch (game.enemies[i].kind)
    {
        case MARS:
            play_sound_effect("planet_sound"); // Play the planet explosion sound
            // Remove 1/7 from health_pct and remove the enemy
            game.player.health_pct -= HPBAR;
            if (game.player.health_pct < 0.0)
            {
                game.player.health_pct = 0.0;
            }
            remove_enemy(game, i);
            break;
        case JUPITER:
            play_sound_effect("planet_sound"); // Play the planet explosion sound
            // Remove 1/7 from health_pct and remove the enemy
            game.player.health_pct -= HPBAR;
            if (game.player.health_pct < 0.0)
            {
                game.player.health_pct = 0.0;
            }
            remove_enemy(game, i);
            break;
        case MERCURY:
            play_sound_effect("mercury_sound"); // Play the slow down sound
            // Set the player's speed to 0
            sprite_set_dx(game.player.player_sprite, 0);
            sprite_set_dy(game.player.player_sprite, 0);
            remove_enemy(game, i);
            break;
    }
}

void check_collisions(game_data &game)
{
    // Loop backwards through all powerups in the game
    for (int i = game.powerups.size() - 1; i >= 0; i--)
    {
        // Check for collision with player sprite
        if (sprite_collision(game.player.player_sprite, game.powerups[i].powerup_sprite))
        {
            apply_powerup(game, i);
        }
    }
    // Loop backwards through all enemies in the game
    for (int i = game.enemies.size() - 1; i >= 0; i--)
    {   
        // Check for collision with player sprite
        if (sprite_collision(game.player.player_sprite, game.enemies[i].enemy_sprite))
        {
            apply_enemy(game, i);
        }
    }
}

// Function to check if the game should end
bool should_end_game(const game_data& game)
{
    // If the player's health is zero, the game should end
    if (game.player.health_pct <= 0.0)
    {
        return true;
    }

    // If the player's fuel is zero, the game should end
    if (game.player.fuel_pct <= 0.0)
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

// Function to draw the game on the screen
void draw_game(game_data &game)
{
    // Draw the background of the game
    draw_bitmap("space_background", 0, 0, option_scale_bmp(2.3, 2.3, option_to_screen())); 
    draw_bitmap("space_background", 0, 400, option_scale_bmp(2.3, 2.3, option_to_screen()));
    draw_powerup(game.powerups); // Draw the powerups
    draw_enemies(game.enemies); // Draw the enemies
    draw_hud(game);           // Draw the HUD (Heads-Up Display)
    draw_player(game.player); // Draw the player
    refresh_screen(60); // Refresh the screen at 60 frames per second
};

// Function to update the game state
void update_game(game_data &game)
{
    add_powerup(game);          // Add new powerups to the game
    add_enemy(game);            // Add new enemies to the game
    check_collisions(game);     // Check for collisions between player and powerups
    update_player(game.player); // Update the player's position
    update_powerup(game.powerups); // Update the powerups' positions
    update_enemy(game.enemies, game.player); // Update the enemies' positions
    update_elapsed_time(game.score); // Update the elapsed time of the game
};
