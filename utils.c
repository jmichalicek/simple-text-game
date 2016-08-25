/* this library provides utility functions such as for finding a specific room in the world linked list */

#include <stdlib.h>
#include <stdio.h>

/* functions local to this library */
#include "utils.h"

#define DEBUG

room * get_room(room **firstNode, int roomNum)
{
    
    room *current = *firstNode;
    while (current != NULL)
    {
#ifdef DEBUG
        printf("found room: %d and am looking for room: %d\n",current->room_number, roomNum);
#endif
        if (current->room_number == roomNum)
        {
#ifdef DEBUG
            printf("Found room\n");
#endif
            return(current);
        }
        current = current->next_room;
    } /*end while*/
    
    return NULL;        
}
