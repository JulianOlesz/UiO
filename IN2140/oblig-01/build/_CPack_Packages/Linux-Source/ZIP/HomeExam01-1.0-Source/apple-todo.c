#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apple-todo.h"

int locateworm( char* apple)
{
    for (int i = 0; apple[i] != '\0'; i++) {
        if (apple[i] == 'w') return i;
    }
    return -1;
}

int removeworm( char* apple )
{
    int worm_length = 0;
    for (int i = 0; apple[i] != '\0'; i++) {
        switch (apple[i]) {
            case 'w': 
            case 'o':
            case 'r':
            case 'm':
                apple[i] = ' ';
                worm_length++;
        }
    }
    return worm_length;
}