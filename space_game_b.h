#ifndef SPACE_GAME_B
#define SPACE_GAME_B

#include "splashkit.h"
#include "player.h"
#include "powerup_b.h"
#include "score_b.h"
#include <vector>

using std::vector;

const int MIN_b = -1500;
const int MAX_b = 1500;

/**
 * @struct game_data
 * Represents the game data containing player, powerup, enemy, and score data.
 */
struct game_data_b
{
player_data player; // Player data
vector<powerup_data_b> powerups; // Vector to store powerup data
score_data_b score_b; // Score data
};

/**
 * Loads the game resources such as images, sounds, and fonts.
 */
void load_resources_b();

/**
 * Draws the heads-up display (HUD) of the game, including the score and player health.
 * @param game_b The game_data object containing the game information
 */
void draw_hud_b(game_data_b &game_b);

/**
 * Adds a new powerup to the game at a random position.
 * @param game_b The game_data object to add the powerup to
 */
void add_powerup_b(game_data_b &game_b);

/**
 * Removes a powerup from the game at the specified index.
 * @param game_b The game_data object to remove the powerup from
 * @param index The index of the powerup to remove
 */
void remove_powerup_b(game_data_b &game_b, int index);

/**
 * Applies the effects of a powerup to the player.
 * @param game_b The game_data object to apply the powerup to
 * @param i The index of the powerup to apply
 */
void apply_powerup_b(game_data_b &game_b, int i);

/**
 * Checks for collisions between the player and powerups or enemies in the game.
 * @param game_b The game_data object to check collisions for
 */
void check_collisions_b(game_data_b &game_b);

/**
 * Creates a new game instance by initializing the game_data object with default values.
 * @returns The newly created game_data object representing a new game instance
 */
game_data_b new_game_b();

/**
 * Draws the game on the screen, including the player, powerups, enemies, and HUD.
 * @param game_b The game_data object containing the game information
 */
void draw_game_b(game_data_b &game_b);

/**
 * Updates the game state, including the player, powerups, enemies, and score.
 * @param game_b The game_data object to update the state for
 */
void update_game_b(game_data_b &game_b);

/**
 * Determin_bes if the game should end based on certain conditions, such as player health reaching zero.
 * @param game_b The game_data object to check for end conditions
 * @returns True if the game should end, false otherwise
 */
bool should_end_game_b(const game_data_b &game_b);

/**
 * Calculates the mini map coordinates for a powerup.
 * @param powerup The powerup_data object for which to calculate the coordinates
 * @return The calculated mini map coordinates as a point_2d object
 */
point_2d mini_map_coordinate_powerup_b(const powerup_data_b &powerup);

/**
 * Draws the Mini Map of all powerups and enemies inside the Heads Up Display.
 * @param powerups The vector of powerup_data objects representing the powerups to be displayed on the mini map
 */
void draw_minimap_b(const vector<powerup_data_b> &powerups);


/**
 * Draws the player on the mini map.
 * @param player The player_data object representing the player to be displayed on the mini map
 */
void draw_player_in_map_b(const player_data &player);

#endif