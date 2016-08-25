/* Functions to define commands that players might use, such as look, go, take, etc.*/

#ifndef JUSTIN_TEXT_ENGINE_PLAYER_COMMANDS_LIB
#define JUSTIN_TEXT_ENGINE_PLAYER_COMMANDS_LIB

/* Functions the player might enter */

/* go in a direction.  Direction is enumerated to an int.
 * Check if there is a room in that direction and change the player's
 * current room pointer to that room.  Update room info of previous room and current room,
 * which should probably be new functions in perhaps utils.h/.c
 */
void go(player * player, int direction);

/* look at a specific object.  Will need some sort of
 * pointer to the object, I guess.
 */
void look();

#endif
