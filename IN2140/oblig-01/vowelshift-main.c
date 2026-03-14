#include <stdio.h>   /* search for system header file: use <> */
#include <stdlib.h>
#include <string.h>

#include "vowelshift-todo.h" /* search locally: use "" */

/*
 * This is a forward declaration of the function usage().
 * usage() is the traditional name of a function that prints how the program
 * should be used, and terminates the program after that.
 *
 * This means that it's implemented in the same source file, but probably
 * further below. If you don't do this and call the function earlier in the
 * file than you define it, the compiler will complain.
 */
static void usage( const char* name );

/*
 * This program can take arguments from the command line.
 * The first parameter is the number of arguments, including the program's own name, which
 * is stored in argv[0].
 * The second parameter is an array of C strings (pointers to char), where each command
 * line argument is one entry of the array.
 * You can choose the names of the arguments. It is tradition to call them argc and argv.
 */
int main( int argc, char* argv[] )
{
    /*
     * Some quick checks at the start:
     * Is the number of parameters including the program name 3?
     * Is the first argument not empty?
     * Is the second argument not empty?
     * If any of the checks fails, print the usage (see below) and
     * quit.
     */
    if( argc != 3 )              usage( argv[0] );
    if( strlen( argv[1] ) == 0 ) usage( argv[0] );
    if( strlen( argv[2])  == 0 ) usage( argv[0] );

    /*
     * Print the inputs - make sure they are as expected.
     */
    printf( "Input string:    %s\n", argv[1] );
    printf( "Input character: %c\n", argv[2][0] );

    /*
     * Make a copy of the long input string. The reason is that the strings in
     * the argv array are protected in modern C, attempting to change them leads
     * to a crash.
     */
    char* copy = strdup( argv[1] );

    /*
     * Make a copy of the replacement character. Just for readbility.
     * But it shows how you pick a character out of a C string that is itself in an
     * array of C strings.
     */
    char  repl = argv[2][0];

    /*
     * Call the function vowelshift.
     * The functions changes the copy of the input C string.
     */
    vowelshift( copy, repl );

    /*
     * Print the modified C string.
     */
    printf( "Ouput string:    %s\n", copy );

    /*
     * copy is a copy of argv[1] that was made with the strcpy() function.
     * strcpy() calls malloc() behind the scenes. Such memory should always
     * be released.
     * If you don't train yourself to do this, you will forget it in larger
     * projects and create terrible memory leaks.
     */
    free( copy );

    return 0;
}

static void usage( const char* name )
{
    /*
     * This explains how the command should be called.
     * Arguments in less than and greater than signs are mandatory.
     * If an argument is optional, you's put it between corner brackets [ and ].
     * This is inspired by the syntax of regular expressions in Unix shells.
     */
    printf("Usage: %s <string> <character>\n"
           "          replaces each of the 5 English vowels (a,e,i,o,u) in <string> with\n"
           "          with the character <character>\n"
           "          <string>: a series of characters in double quotation marks, probably a sentence\n"
           "          <character>: a single character\n", name );
    exit( -1 );
}

