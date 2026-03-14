#include <stdio.h>   /* search for system header file: use <> */
#include <stdlib.h>
#include <string.h>

#include "the_apple.h"
#include "apple-todo.h"

static void usage( const char* name );

/*
 * This program takes no arguments from the command line.
 *
 * It calls the two functions that you must write as part of the assignment,
 * locateworm and removeworm.
 * locateworm() does not change the apple, so it goes first.
 * removeworm() changes the apple.
 */
int main( )
{
    printf("The apple with the worm:\n"
           "%s\n", apple );

    int position;
    int length;

    position = locateworm( apple );

    printf("The worm starts at position %d of the apple\n", position);

    length = removeworm( apple );

    printf("The worm was %d characters long\n", length);

    printf("The apple without the worm:\n"
           "%s\n", apple );

    return 0;
}

