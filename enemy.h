#ifndef SPACE_GAME_ENEMY
#define SPACE_GAME_ENEMY

#include "splashkit.h"
#include "player.h"
#include <chrono>

using namespace std;

// Enumeration for different kinds of enemies
enum enemy_kind
{
    MARS,     
    JUPITER,  
    MERCURY   
};

// Struct to hold the enemy data
struct enemy_data
{
    enemy_kind kind;       // The kind of the enemy
    sprite enemy_sprite;   // The sprite representing the enemy
    double lifetime;       // Added field to track the lifetime of the enemy
};

/**
 * Creates a new enemy with a random kind at the specified position.
 * 
 * @param enemies   The vector of enemy data to add the new enemy to
 * @param x         The x coordinate for the new enemy
 * @param y         The y coordinate for the new enemy
 */
void new_enemy(vector<enemy_data> &enemies, double x, double y);

/**
 * Draws all enemy sprites in the enemies vector.
 * 
 * @param enemies   The vector of enemy data to draw
 */
void draw_enemies(vector<enemy_data> &enemies);

/**
 * Updates enemy positions and handles deletion.
 * 
 * @param enemies   The vector of enemy data to update
 * @param player    The player data used for enemy tracking
 */
void update_enemy(vector<enemy_data> &enemies, const player_data &player);

/**
 * Returns the time elapsed since the previous frame in seconds.
 */
double get_frame_time();

#endif