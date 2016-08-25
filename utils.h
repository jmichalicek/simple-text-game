/*utility functions for various stuff
 * such as linked list manipulation to return a link to a specific room or whatnot
 */

#ifndef JUSTIN_TEXT_ENGINE_UTILS_LIB
#define JUSTIN_TEXT_ENGINE_UTILS_LIB

/* structure which holds the room info */
struct room_data {
    
/* Pointers to the rooms each room connects to from a player perspective*/
    struct room_data *northRoom;
    struct room_data *southRoom;
    struct room_data *eastRoom;
    struct room_data *westRoom;
    
    /*Current room's number*/
    int room_number;
    
    /*room description*/
    char room_desc[255];
    
    /*pointer to make linked list*/
    struct room_data *next_room;
};

typedef struct room_data room;
/*typedef room *roomPtr; */

room * get_room(room **firstNode, int roomNum);

#endif
