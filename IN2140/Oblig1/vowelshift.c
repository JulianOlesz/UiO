#include <stdio.h>

int vowelshift(char string_in[], char symbol);

//int main(char string[], char symbol) {
int main(int argc, char** argv) {
    vowelshift(argv[1], argv[2][0]);
    return 0;
}

int vowelshift(char string_in[], char symbol) {
    for (int i = 0; string_in[i] != '\0'; i++) {
        // if (string_in[i] == 'a' || string_in[i] == 'e' || string_in[i] == 'i' || string_in[i] == 'o' || string_in[i] == 'u')
        switch (string_in[i]) {
            case 'a': case 'e': case 'i': case 'o': case 'u':
                string_in[i] = symbol;
        }
    }

    printf("%s\n", string_in);

    return 0;
};