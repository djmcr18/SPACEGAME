#ifndef SPACE_GAME_POWER_UP_B
#define SPACE_GAME_POWER_UP_B

#include "splashkit.h"
#include <vector>

using namespace std;

/**
 * Different types of power-ups that can be collected by the player.
 */
enum powerup_kind_b
{    
    CASH_b,       
    BATTERY_b,    
    DIAMOND_b,      
};

/**
 * Struct containing the data for a power-up.
 * 
 * @field   kind            The type of power-up
 * @field   powerup_sprite  The power-up's sprite - used to track position and movement
 */
struct powerup_data_b
{
    powerup_kind_b   kind;
    sprite         powerup_sprite;
};

/**
 * Returns the bitmap associated with the given power-up type.
 * 
 * @param kind  The type of power-up to get the bitmap for
 * @returns     The bitmap associated with the given power-up type
 */
bitmap powerup_bitmap_b(powerup_kind_b kind);

/**
 * Creates a new power-up at the given position with a random type.
 * 
 * @param x     The x coordinate for the new power-up
 * @param y     The y coordinate for the new power-up
 * @returns     The new power-up data
 */
void new_powerup_b(vector<powerup_data_b> &powerups, double x, double y);

/**
 * Draws the given power-up to the screen.
 * 
 * @param powerups  The power-up to draw to the screen
 */
void draw_powerup_b(vector<powerup_data_b> &powerups);

/**
 * Actions a step update of the given power-up - moving it and checking for collision with the player.
 * 
 * @param powerups   The power-up being updated
 */
void update_powerup_b(vector<powerup_data_b> &powerups);

#endif