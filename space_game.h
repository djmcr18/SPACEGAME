#ifndef SPACE_GAME
#define SPACE_GAME

#include "splashkit.h"
#include "player.h"
#include "powerup.h"
#include "enemy.h"
#include "score.h"
#include <vector>

using std::vector;

const int MIN = -1500;
const int MAX = 1500;

/**
 * @struct game_data
 * Represents the game data containing player, powerup, enemy, and score data.
 */
struct game_data
{
player_data player; // Player data
vector<powerup_data> powerups; // Vector to store powerup data
vector<enemy_data> enemies; // Vector to store enemy data
score_data score; // Score data
};

/**
 * Loads the game resources such as images, sounds, and fonts.
 */
void load_resources();

/**
 * Draws the heads-up display (HUD) of the game, including the score and player health.
 * @param game The game_data object containing the game information
 */
void draw_hud(game_data &game);

/**
 * Adds a new powerup to the game at a random position.
 * @param game The game_data object to add the powerup to
 */
void add_powerup(game_data &game);

/**
 * Removes a powerup from the game at the specified index.
 * @param game The game_data object to remove the powerup from
 * @param index The index of the powerup to remove
 */
void remove_powerup(game_data &game, int index);

/**
 * Adds a new enemy to the game at a random position.
 * @param game The game_data object to add the enemy to
 */
void add_enemy(game_data &game);

/**
 * Applies the effects of a powerup to the player.
 * @param game The game_data object to apply the powerup to
 * @param i The index of the powerup to apply
 */
void apply_powerup(game_data &game, int i);

/**
 * Checks for collisions between the player and powerups or enemies in the game.
 * @param game The game_data object to check collisions for
 */
void check_collisions(game_data &game);

/**
 * Creates a new game instance by initializing the game_data object with default values.
 * @returns The newly created game_data object representing a new game instance
 */
game_data new_game();

/**
 * Draws the game on the screen, including the player, powerups, enemies, and HUD.
 * @param game The game_data object containing the game information
 */
void draw_game(game_data &game);

/**
 * Updates the game state, including the player, powerups, enemies, and score.
 * @param game The game_data object to update the state for
 */
void update_game(game_data &game);

/**
 * Determines if the game should end based on certain conditions, such as player health reaching zero.
 * @param game The game_data object to check for end conditions
 * @returns True if the game should end, false otherwise
 */
bool should_end_game(const game_data &game);

/**
 * Calculates the mini map coordinates for a powerup.
 * @param powerup The powerup_data object for which to calculate the coordinates
 * @return The calculated mini map coordinates as a point_2d object
 */
point_2d mini_map_coordinate_powerup(const powerup_data &powerup);

/**
 * Calculates the mini map coordinates for an enemy.
 * @param enemy The enemy_data object for which to calculate the coordinates
 * @return The calculated mini map coordinates as a point_2d object
 */
point_2d mini_map_coordinate_enemy(const enemy_data &enemy);

/**
 * Draws the Mini Map of all powerups and enemies inside the Heads Up Display.
 * @param powerups The vector of powerup_data objects representing the powerups to be displayed on the mini map
 * @param enemies The vector of enemy_data objects representing the enemies to be displayed on the mini map
 */
void draw_minimap(const vector<powerup_data> &powerups, const vector<enemy_data> &enemies);


/**
 * Draws the player on the mini map.
 * @param player The player_data object representing the player to be displayed on the mini map
 */
void draw_player_in_map(const player_data &player);

#endif