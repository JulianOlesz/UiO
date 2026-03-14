#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "stringops-todo.h"

#define CNRM "\x1b[0m"
#define CRED "\x1b[31m"
#define CGRN "\x1b[32m"

static int test_num = 1;

/*
 * A helper function to print whether a test passed or failed.
 * Prints color-coded in terminals that support color.
 */
static void logger(int passed, char *s)
{
   char *res;
   char *color;

   if (passed) {
      res = "PASS";
      color = CGRN;
   } else {
      res = "FAIL";
      color = CRED;
   }
   printf("[Test %d][%s%s%s] %s\n", test_num++, color, res, CNRM, s);
}

/*
 * Call stringsum with the parameters that are provided by the caller,
 * and check whether the result is as expected by the caller.
 */
static void test_stringsum(char *input, int expected)
{
   int test;
   char buf[256] = { 0 };

   test = stringsum(input);
   sprintf(buf, "Returned: %d, Expected: %d", test, expected);
   logger(test == expected, buf);
}

/*
 * Call distance_between with the parameters that are provided by the caller,
 * and check whether the result is as expected by the caller.
 */
static void test_distance_between(char *str, char c, int expected)
{
   int test;
   char buf[256] = { 0 };

   test = distance_between(str, c);
   sprintf(buf, "Returned: %d, Expected: %d", test, expected);
   logger(test == expected, buf);
}

/*
 * Call string_between and test whether it behaves as expected.
 * The return value of string_between is compaired with the expected
 * string after string_between has modified the buffer.
 *
 * Please note that test_string_between() makes a copy of the input string
 * using strdup() before it calls string_between(), and it deletes this
 * copy using free() before it returns to the caller.
 * This copy is necessary because the input string cannot be modified, but
 * we make the copy in our code so you don't have to learn allocation and
 * deallocation in C yet.
 */
static void test_string_between( char *str, char c, const char *expected )
{
    char *res_char;
    char buf[256] = { 0 };

    str = strdup( str );

    res_char = string_between( str, c );
    if( res_char == NULL )
        snprintf(buf, sizeof(buf), "Returned: NULL, Expected: %s", expected);
    else
        snprintf(buf, sizeof(buf), "Returned: %s, Expected: %s", res_char, expected);

    if (!res_char && expected) {
        logger(0, buf);
    } else {
        if (!expected)
            logger(!res_char, buf);
        else
            logger(!strcmp(res_char, expected), buf);
    }
    free( str );
}

/*
 * Call stringsum2 with the parameters that are provided by the caller,
 * and check whether the results of are as expected by the caller.
 * In the case of stringsum2, that is both the return values of the
 * function and the variable whose address is passed to stringsum2 in its
 * second parameter.
 */
static void test_stringsum2(char *input, int expected_ref, int expected_ret)
{
   int ret_ref;
   int ret_val;
   char buf[256] = { 0 };

   ret_val = stringsum2(input, &ret_ref);
   sprintf(buf, "Returned: %d, expected: %d, in parameter %d, expected %d",
                ret_val, expected_ret,
                ret_ref, expected_ref);
   logger(ret_ref == expected_ref, buf);
}

/*
 * This main program calls tests for your implementations of
 * stringsum, distance_between, string_between and stringsum2.
 * It is a good idea to extend these examples to ensure that your
 * programs works in all cases.
 */
int main(void)
{
   printf("Testing stringsum()\n");
   test_stringsum("Lorem ipsum dolor sit amet", 292);
   test_stringsum("L0rem 1psum d0l0r s1t amet", -1);
   test_stringsum("", 0);

   test_num = 1;
   printf("\nTesting distance_between()\n");
   test_distance_between("Lorem ipsum dolor sit amet", 'm', 19);
   test_distance_between("Lorem ipsum dolor sit amet", 'u', 0);
   test_distance_between("Lorem ipsum dolor sit amet", 'y', -1);
   test_distance_between("", 'z', -1);

   test_num = 1;
   printf("\nTesting string_between()\n");
   test_string_between("Lorem ipsum dolor sit amet", 'o', "rem ipsum dol");
   test_string_between("Lorem ipsum dolor sit amet", 'a', "");
   test_string_between("Lorem ipsum dolor sit amet", 'y', NULL);
   test_string_between("", 'z', NULL);

   test_num = 1;
   printf("\nTesting stringsum2()\n");
   test_stringsum2("Lorem ipsum dolor sit amet", 292,0);
   test_stringsum2("L0rem 1psum d0l0r s1t amet", -1, -1);
   test_stringsum2("", 0, -1);
   
   return 0;
}
