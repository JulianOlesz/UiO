/*
 * This is the header file for your own code.
 * It contains only declarations, but no C code.
 * The header must be included into all code files that use something
 * that is declared here.
 */

/*
 * This ifndef-define-endif sequence protects your compiler from include
 * loops. When a compiler reads this file for the first time, it remembers
 * everything between ifndef and the matching endif. When it reads this file
 * a second time (due to some bug), it jumps straight to the end.
 * Every header file must have a unique protection string.
 */
#ifndef APPLE_TODO_H
#define APPLE_TODO_H

/*
 * Note that I use the word "buffer" for the parameter of the function
 * localworm. In the file apple-todo.c, I use the word "apple".
 *
 * I can do this because the name of the parameter in the definition here
 * has not meaning. I can even remove the parameter name in this header
 * file, it exists only for readability.
 */

/*
 * Return the index from the array start of the first character for the
 * worm.
 */
int locateworm( char* buffer );

/*
 * Delete the worm from the apple, replacing it with empty space.
 */
int removeworm( char* buffer );

#endif
