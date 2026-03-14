#include <stdio.h>

#include "vowelshift-todo.h"

void vowelshift(char* buffer, char repl) {
    for (int i = 0; buffer[i] != '\0'; i++) {
        // if (buffer[i] == 'a' || buffer[i] == 'e' || buffer[i] == 'i' || buffer[i] == 'o' || buffer[i] == 'u')
        switch (buffer[i]) {
            case 'a': case 'e': case 'i': case 'o': case 'u':
                buffer[i] = repl;
        }
    }

    printf("%s\n", buffer);
};