/* Functions to define commands that players might use, such as look, go, take, etc.*/

#ifndef JUSTIN_TEXT_ENGINE_PLAYER_LIB
#define JUSTIN_TEXT_ENGINE_PLAYER_LIB

struct character
{
    char name[25];
    struct room_data *current_room;
};

typedef struct character ch;


/* Functions which modify the player */
/* I don't have any yet, but I will.  Probably an add points, add health, take health,
 * update current room, etc
 */

#endif
