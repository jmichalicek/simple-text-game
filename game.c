/*This is the beginning of a small text adventure game engine*/
/*I started this project specifically to learn to create and use linked lists*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* My libs */
#include "utils.h"
#include "player.h"

#define DEBUG

#define START_ROOM 100

const char worldFile[] = "rooms";
const char titleFile[] = "title";

void title_screen(void);
room ** load_world(room **);
int init_player(ch *, room **);
void free_world(room **);

/*stuff that eventually may be moved into a different source file*/
void parse_input(char[]);

/*actual actions from commands*/
int move_player(char [], char []);

int main()
{
    /*
     * create null pointer for linked list for world
     * I'm still trying to understand this fully
     * but this is how it works
     */
    
    char command[] = "bobo rar";
    room *roomListPtr = NULL;
    ch player;
    /*  int start; */
    
    /*Load the world*/
    load_world(&roomListPtr);
    
    /*Display title screen*/
    title_screen();
    
    /*initialize the player*/
    if (init_player(&player, &roomListPtr) != 0)
    {
        printf("Could not load player\n");
        free_world(&roomListPtr);
        return(-1); 
    }
#ifdef DEBUG
    printf("Loaded player fully\n");
#endif
    printf("%s is in room %d: %s\n", player.name, player.current_room->room_number, player.current_room->room_desc);
    
    /* clean up by freeing up the linked list storing the world */
    free_world(&roomListPtr);
    parse_input(command);

    printf("Good bye!\n");
    return(0); 
} /*End Main()*/


/*The following function loads the world from
 *config file into memory as a linked list
 */
room ** load_world(room **firstNode)
{
    room *nextRoomPtr;
    FILE *rfPtr;
    char value[255];
    int north;
    int south;
    int east;
    int west;
    int current;
    /* file postition */
    fpos_t pos;
    room *currentRoomPtr;
    room *connectingRoomPtr;

    printf("Please wait while the world loads\n");
    if ((rfPtr = fopen(worldFile, "r")) == NULL)
    {
        printf("Could not open world file\r\n");
        exit;
    }/*end if fopen*/
    
    /* Allocate memory for a new room */
    nextRoomPtr = malloc(sizeof(room));

    /* get the file position for laster use with fsetpos*/
    fgetpos(rfPtr,&pos);
    /*leading read before while loop*/
    fscanf(rfPtr, "%d", &nextRoomPtr->room_number); 

    while (!feof(rfPtr))
    {
        /* Need to skip over this line and this is the best way I know how.  It will get
         * parsed later in a second interation over the config file.  Since this char[]
         * already exists just read into it and then it will get overwritten before it is
         * really needed anyway.  ugly. */
        fgets(value, 255, rfPtr);
        fgets(value, 255, rfPtr);

        while (strncmp(value, "ENDROOM", 7) != 0)
        {
            strcat(nextRoomPtr->room_desc, value);
            fgets(value, 255, rfPtr);
        } /*end while strcmp*/
     
        /* now link the room to the "current" room or the initial node
         * on our first loop through
         */
        nextRoomPtr->next_room = *firstNode;

        /* Now that the next room is linked to our current room's address
         * make the 'next' room our 'current' room so that it can be linked to at the end of the next loop
         */
        *firstNode = nextRoomPtr;
        nextRoomPtr = malloc(sizeof(room));
        fscanf(rfPtr, "%d", &nextRoomPtr->room_number);
    } /*end while !feof*/

    /* back to the beginning of the file */
    fsetpos(rfPtr,&pos);
 
    /*leading read before while loop*/
    fscanf(rfPtr, "%d", &current);
    while (!feof(rfPtr))
    {
        printf("%d\n",(*firstNode)->room_number);
        currentRoomPtr = get_room(firstNode, current);

        /* find the various connecting rooms and connect them */
        /* need to add some error checking here in case a room doesn't exist */
        fscanf(rfPtr, "%d%d%d%d", &north, &south, &east, &west);
        connectingRoomPtr = get_room(firstNode, north);
        currentRoomPtr->northRoom = connectingRoomPtr; 
        connectingRoomPtr = get_room(firstNode, south);
        currentRoomPtr->southRoom = connectingRoomPtr;
        connectingRoomPtr = get_room(firstNode, east);
        currentRoomPtr->eastRoom = connectingRoomPtr;
        connectingRoomPtr = get_room(firstNode, west);
        currentRoomPtr->westRoom = connectingRoomPtr;
        /* this seems a bit overly redundant.  Need to find a better way to skip this crap */
        fgets(value, 255, rfPtr);
        while (strncmp(value, "ENDROOM", 7) != 0)
        {
            fgets(value, 255, rfPtr);
        } /*end while strcmp*/

        /*leading read before while loop*/
        fscanf(rfPtr, "%d", &current);
    }
 
    fclose(rfPtr);
 
    /* This puts our pointer to the linked list of the world
     * at the end of the list.  We are actually returning a pointer to the last room
     * and each room has a pointer to the previous room number
     */
 
    /* Now we need to loop through out linked list and map the other rooms that each room connects to */

    return nextRoomPtr;

} /*end load_world()*/

/*initialize player*/
int init_player(ch *player, room **firstNode)
{
    FILE * rfPtr;
    char label[7];
    char name[25];

    int temp_room;

    scanf("%s", name);
    /*if new player*/
    if (strcmp(name,"new") == 0)
    {
        printf("Name your character: ");
        scanf("%s", player->name);
        /* add check if that name exists */
        player->current_room = get_room(firstNode, START_ROOM);

        return 0;

    } /*end if*/

    /*otherwise do this stuff*/
    if ((rfPtr = fopen(name, "r")) == NULL)
    {
        printf("Could not open player file\r\n");
        return 1;
    } /*end if fopen*/

    /*Add in login function and then call this function*/
    /*Then this will need to see if the player exists*/
    /*If player does, do the stuff that is below, if not*/
    /*then create new player with some defaults*/

    
    /*Load player info from their save file.*/
    /*If you're familiar with CircleMUD w/ ascii pfiles code*/
    /* then you should know how this works since I stole the idea */
    fgets(label, 7, rfPtr);

    while(!feof(rfPtr))
    {
        switch(*label)
        {
        case 'A': break;
        case 'B': break;
        case 'C': break;
        case 'D': break;
        case 'E': break;
        case 'F': break;
        case 'G': break;
        case 'H': break;
        case 'I': break;
        case 'J': break;
        case 'K': break;
        case 'L': break;
        case 'M': break;
        case 'N': 
            if(strcmp(label, "Name :") == 0) fscanf(rfPtr, "%s", player->name);
#ifdef DEBUG
            printf("Loaded player name: %s\n", player->name);
#endif
            break;
        case 'P': break;
        case 'Q': break;
        case 'R':
            if(strcmp(label, "Room :") == 0) {
                fscanf(rfPtr, "%d", &temp_room);
#ifdef DEBUG
                printf("putting player in room %d\n", temp_room);
#endif
                player->current_room = get_room(firstNode, temp_room);
#ifdef DEBUG
                printf("Successfully loaded to room\n");
#endif
            }
            break; 
        case 'S': break;
        case 'T': break;
        case 'U': break;
        case 'V': break;
        case 'W': break;
        case 'X': break;
        case 'Y': break;
        case 'Z': break;
        } /*end switch(label)*/

        fgets(label, 7, rfPtr);
      
        /*  fscanf(rfPtr, "%s", player->name);
	    fscanf(rfPtr, "%d", &player->current_room);
        */
    } /*end while !feof*/

    fclose(rfPtr);

    return 0;

} /*end init_player()*/

void free_world(room **firstNode)
{
    room *temp = *firstNode;
    room *current = *firstNode; 
    
    while (current != NULL)
    {
        temp = current->next_room;
#ifdef DEBUG
        printf("freeing: %d\n", current->room_number);
#endif
        free(current);
        current = temp;
    } /*end while*/
    
} /*end free_world*/

void title_screen()
{
    FILE *rfPtr;
    char temp[100];
    
    if ((rfPtr = fopen(titleFile, "r")) == NULL)
    {
        printf("Could not open file\r\n");
        exit;
    } /*end if fopen*/
    
    fgets(temp, 100, rfPtr);
    
    while (!feof(rfPtr))
    {
        printf("%s", temp);
        fgets(temp, 100, rfPtr);
    } /*end while !feof*/
    
    fclose(rfPtr);
    
    printf("Name of character to load (Type \"new\" for new character): ");
    
} /*end title_screen()*/


/*Beginnings of simple command parser*/
void parse_input(char command[255]) {
    char *parsed_command;
    char *command_arg;
    int i;
    
#ifdef DEBUG
    printf("about to parse command: %s\n", command);
#endif
    parsed_command = strtok(command, " ");
    command_arg = (command + (strlen(parsed_command) + 1));
    
#ifdef DEBUG 
    printf("command given was %s\n", parsed_command);
    printf("the rest of the command was: %s\n", command_arg);
#endif
    
    /*Going to want to convert to uppercase before doing this eventually as a player could type in upper or lower*/
    switch(*command){
    case 'A': break;
    case 'B': break;
    case 'C': break;
    case 'D': break;
    case 'E': break;
    case 'F': break;
    case 'G': 
        /*Need to write this function.  Need to write some actual command parsing to grab the command itself and its arguments*/
        if(strcmp(command, "GO") == 0) move_player(parsed_command, command_arg);
        break;
    case 'H': break;
    case 'I': break;
    case 'J': break;
    case 'K': break;
    case 'L': break;
    case 'M': break;
    case 'N': break;
    case 'P': break;
    case 'Q': break;
    case 'R': break;
    case 'S': break;
    case 'T': break;
    case 'U': break;
    case 'V': break;
    case 'W': break;
    case 'X': break;
    case 'Y': break;
    case 'Z': break;
    } /*end switch(*command)*/    
} /*end parse_input()*/

/*action commands*/
int move_player(char command[255], char command_arg[255])
{



}
