#include "powerup_b.h"
#include "splashkit.h"

const int MIN = -1500;
const int MAX = 1500;

// Returns a bitmap for a given powerup kind
bitmap powerup_bitmap_b(powerup_kind_b kind)
{
    // Select the bitmap based on the powerup kind
    switch (kind)
    {
        case CASH_b:
            return bitmap_named("cash");
        case BATTERY_b:
            return bitmap_named("battery");
        case DIAMOND_b:
            return bitmap_named("diamond");
        default:
            return bitmap_named("cash"); // Default to cash if the kind is invalid
    }
}

// Creates a new powerup with a random kind at the specified position
void new_powerup_b(vector<powerup_data_b> &powerups, double x, double y)
{
    powerup_data_b new_powerup_data_b;

    // Generate a random powerup kind
    new_powerup_data_b.kind = static_cast<powerup_kind_b>(rnd(3));

    // Create a sprite with the corresponding bitmap for the selected kind
    new_powerup_data_b.powerup_sprite = create_sprite(powerup_bitmap_b(new_powerup_data_b.kind));

    // Set the sprite's position
    sprite_set_x(new_powerup_data_b.powerup_sprite, x);
    sprite_set_y(new_powerup_data_b.powerup_sprite, y);

    // Set the sprite's x and y velocity to a random value between -3 and 3
    sprite_set_dx(new_powerup_data_b.powerup_sprite, rnd() * 6 - 3);
    sprite_set_dy(new_powerup_data_b.powerup_sprite, rnd() * 6 - 3);

    // Add the new powerup data to the vector
    powerups.push_back(new_powerup_data_b);
}

// Draws all powerup sprites in the powerups vector
void draw_powerup_b(vector<powerup_data_b> &powerups)
{
    for (const auto &powerup : powerups) 
    {
        draw_sprite(powerup.powerup_sprite);
    }
}

// Updates all powerup sprites in the powerups vector
void update_powerup_b(vector<powerup_data_b> &powerups)
{
    for (auto &powerup : powerups) 
    {
        update_sprite(powerup.powerup_sprite);
    }

    // Iterate over all the power-ups
    for (int i = 0; i < powerups.size(); i++)
    {
        // Get the current power-up sprite's position
        point_2d powerupPos = sprite_position(powerups[i].powerup_sprite);

        // Check if the power-up sprite is within the boundary
        if (powerupPos.x < MIN || powerupPos.x > MAX || powerupPos.y < MIN || powerupPos.y > MAX)
        {
            // Remove the powerup from the vector
            free_sprite(powerups[i].powerup_sprite);
            powerups.erase(powerups.begin() + i);
            i--; // Decrement the index as the powerup was removed
        }
    }
}

