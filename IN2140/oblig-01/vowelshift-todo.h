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
#ifndef VOWELSHIFT_TODO_H
#define VOWELSHIFT_TODO_H

/*
 * This line is a declaration for a function called vowelshift.
 * The definition (a C word for implementation. Is not here.
 * It doesn't really matter where it is, it's just a promise that it exists
 * and that it can be linked (made available) to the final program.
 */
void vowelshift( char* buffer, char repl );

#endif

