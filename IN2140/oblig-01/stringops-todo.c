#include <stdio.h>
#include <ctype.h>

#include "stringops-todo.h"

int stringsum(char* s);
int distance_between(char *s, char c);
char* string_between(char *s, char c);
int stringsum2(char *s, int *res);

struct Section {
    int first;
    int last;
};

struct Section find_section(char* s, char c) {
    int first = 0;
    int last = 0;

    for (int i = 1; s[0] != '\0'; s++, i++){
        if (s[0] == c) {
            if (first == 0) {
                first = i;
            } else {
                last = i;
            }
        }
    }
    struct Section sec;
    sec.first = first;
    sec.last = last; 
    return (sec);
}

int stringsum(char *s) {
    int stringsum = 0; 
    
    while (s[0] != '\0'){
        int char_value = (int)(tolower(s[0]));
      
        if (char_value >= 97 && char_value <= 122 || char_value == 32) {
            if (char_value != 32) {
               stringsum += (char_value - 96); 
            }
        } else {
            return -1;
        }

        s++;
    }

    return stringsum;
}

int distance_between(char *s, char c) {
    struct Section sec = find_section(s, c);

    if (sec.first != 0) {
        if (sec.last != 0) {
            return (sec.last - sec.first);
        } else {
            return 0;
        }
    } else {
        return -1;
    }
}

char* string_between(char *s, char c) {
    struct Section sec = find_section(s, c);

    if (sec.first != 0) {
        if (sec.last != 0) {
            int distance = (sec.last - sec.first - 1);
        
            char *start = s += sec.first; // lager en startpeker, den peker på første forekomst av symbolet
            char *end = start + distance; // en sluttpeker som er n plasser frem til siste forekomst 
            *end = '\0'; // setter symbolet som pekes på til null for å ende strengen

            return s; // s kan returneres nå som pekerene er overskrevet 
        } else {
            return "";
        }
    } else {
        return NULL;
    }
}

int stringsum2(char *s, int *res) {
    int sum = stringsum(s);

    *res = sum;

    if (sum > 0){
        return 0;
    } else {
        return -1;
    }
}