#ifndef SPACE_GAME_POWER_UP
#define SPACE_GAME_POWER_UP

#include "splashkit.h"
#include <vector>

using namespace std;

/**
 * Different types of powerups that can be collected by the player.
 */
enum powerup_kind
{
    FUEL,       
    HEART,      
    CASH,       
    BATTERY,    
    DIAMOND,    
    NOS         
};

/**
 * Struct containing the data for a powerup.
 * 
 * @field   kind            The type of powerup
 * @field   powerup_sprite  The powerup's sprite - used to track position and movement
 */
struct powerup_data
{
    powerup_kind   kind;
    sprite         powerup_sprite;
};

/**
 * Returns the bitmap associated with the given powerup type.
 * 
 * @param kind  The type of powerup to get the bitmap for
 * @returns     The bitmap associated with the given powerup type
 */
bitmap powerup_bitmap(powerup_kind kind);

/**
 * Creates a new powerup at the given position with a random type.
 * 
 * @param x     The x coordinate for the new powerup
 * @param y     The y coordinate for the new powerup
 * @returns     The new powerup data
 */
void new_powerup(vector<powerup_data> &powerups, double x, double y);

/**
 * Draws the given powerup to the screen.
 * 
 * @param powerups  The powerup to draw to the screen
 */
void draw_powerup(vector<powerup_data> &powerups);

/**
 * Actions a step update of the given powerup - moving it and checking for collision with the player.
 * 
 * @param powerups   The powerup being updated
 */
void update_powerup(vector<powerup_data> &powerups);

#endif