#include "enemy.h"
#include "splashkit.h"


// Returns a bitmap for a given enemy kind
bitmap enemy_bitmap(enemy_kind kind)
{
    // Select the bitmap based on the enemy kind
    switch (kind)
    {
        case MARS:
            return bitmap_named("mars");
        case JUPITER:
            return bitmap_named("jupiter");
        case MERCURY:
            return bitmap_named("mercury");
        default:
            return bitmap_named("mars"); // Default to mars if the kind is invalid
    }
}

// Creates a new enemy with a random kind at the specified position
void new_enemy(vector<enemy_data> &enemies, double x, double y)
{
    enemy_data new_enemy_data;

    // Generate a random enemy kind
    new_enemy_data.kind = static_cast<enemy_kind>(rnd(3));

    // Create a sprite with the corresponding bitmap for the selected kind
    new_enemy_data.enemy_sprite = create_sprite(enemy_bitmap(new_enemy_data.kind));

    // Set the sprite's position
    sprite_set_x(new_enemy_data.enemy_sprite, x);
    sprite_set_y(new_enemy_data.enemy_sprite, y);

    // Set the sprite's x and y velocity to a random value between -2 and 2
    sprite_set_dx(new_enemy_data.enemy_sprite, 0);
    sprite_set_dy(new_enemy_data.enemy_sprite, 0);

    // Initialize the lifetime of the enemy to 0
    new_enemy_data.lifetime = 0.0;

    // Add the new enemy data to the vector
    enemies.push_back(new_enemy_data);
}



// Draws all enemy sprites in the enemies vector
void draw_enemies(vector<enemy_data> &enemies)
{
    for (const auto &enemy : enemies) 
    {
        sprite_set_scale(enemy.enemy_sprite, 0.5); // Set the scale factor here
        draw_sprite(enemy.enemy_sprite);
    }
}

// Constant to define the lifetime threshold for enemy deletion
const double enemy_LIFETIME = 10.0;
const double enemy_SPEED = 3.0;

// Function to update enemy positions and handle deletion
void update_enemy(vector<enemy_data>& enemies, const player_data& player)
{
    double frame_time = get_frame_time(); // Get the frame time

    vector<int> indices_to_remove; // Vector to store indices of enemies to remove

    for (int i = 0; i < enemies.size(); i++)
    {
        auto& enemy = enemies[i]; // Reference to the current enemy

        update_sprite(enemy.enemy_sprite); // Update the enemy sprite

        point_2d enemy_pos = sprite_position(enemy.enemy_sprite); // Get enemy position
        point_2d player_pos = sprite_position(player.player_sprite); // Get player position

        double dx = player_pos.x - enemy_pos.x - 50; // Calculate the x distance to player (-50 so that planet jupiter makes contact more consistently)
        double dy = player_pos.y - enemy_pos.y - 30; // Calculate the y distance to player (-30 so that planet jupiter makes contact more consistently)

        double speed = enemy_SPEED; // Speed at which the enemy chases the player

        double magnitude = sqrt(dx * dx + dy * dy); // Calculate the magnitude of the movement vector
        dx /= magnitude; // Normalize the x component of the movement vector
        dy /= magnitude; // Normalize the y component of the movement vector

        sprite_set_x(enemy.enemy_sprite, enemy_pos.x + dx * speed); // Update enemy x position
        sprite_set_y(enemy.enemy_sprite, enemy_pos.y + dy * speed); // Update enemy y position

        enemy.lifetime += frame_time; // Increment the enemy's lifetime

        if (enemy.lifetime >= enemy_LIFETIME)
        {
            indices_to_remove.push_back(i); // Add the enemy index to the removal list
        }
    }

    // Remove enemies after iterating through all of them
    for (int i = indices_to_remove.size() - 1; i >= 0; i--)
    {
        int index = indices_to_remove[i];
        free_sprite(enemies[index].enemy_sprite); // Free the enemy sprite
        enemies.erase(enemies.begin() + index); // Remove the enemy from the vector
    }
}

// Get the time elapsed since the previous frame in seconds
double get_frame_time()
{
    static double previous_frame_time = current_ticks() / 1000.0; // Convert ticks to seconds
    double current_frame_time = current_ticks() / 1000.0; // Convert ticks to seconds
    double frame_time = current_frame_time - previous_frame_time;
    previous_frame_time = current_frame_time;
    return frame_time;
}
