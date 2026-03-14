#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  

char *stackExample() { 

    char streng[] = "Denne strengen blir lagt på stacken";
    printf("String: %s\n", streng);

    return streng;
}

char *heapExample() {
    char *streng = (char*)malloc(10 * sizeof(char)); 
    if (streng == NULL) {                             
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    strcpy(streng, "heap!");

    return streng;
}

void sizeExample() {
    int x = 10;
    long y = 10;
    char z = 'Y';
    char str[] = "Dette er en streng!";
    int numbers[] = {1, 2, 3, 4, 5};

    printf("Størrelse på int x: %zu bytes\n", sizeof(x));
    printf("Størrelse på long y: %zu bytes\n", sizeof(y));
    printf("Størrelse på char z: %zu bytes\n", sizeof(z));

    printf("Størrelse på str[]: %zu bytes\n", sizeof(str));
    printf("Lengden av str: %d\n", strlen(str));

    printf("Størrelse på numbers[]: %zu bytes\n", sizeof(numbers));

    printf("Antall elementer i numbers: %zu\n",
           sizeof(numbers) / sizeof(numbers[0]));

}

int main() {

    char *stackString = stackExample();  
    printf("Strengen fra stackExample: %s\n", stackString);


    char *heapString = heapExample();   
    printf("Dette er strengen som ligger på heapen: %s\n", heapString);

    free(heapString);
    
    sizeExample();
    return 0;
}