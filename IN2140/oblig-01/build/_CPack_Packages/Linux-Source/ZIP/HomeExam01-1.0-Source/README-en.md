# IN2140 vår 2026

## Oblig 1: Get to know C (Norwegian)

For norsk, se [her](README.md).

In this mandatory assignment, you implement your own functions in a number of small programs to become better acquainted with the C programming language. You find the handout for this assignment [here](oblig-01.tgz).

The tasks will be solved individually; you can discuss solution techniques with other students, but sharing code is not allowed.
See the [guidelines](https://www.uio.no/studier/eksamen/obligatoriske-aktiviteter/mn-ifi-oblig.html) for mandatory tasks and other submissions at Ifi.

The examiners will test submissions on Ifi's Linux machines, available through login.ifi.uio.no ([how](LOGIN-en.md)).
Your programs must compile and run on these machines. If you have any questions about the tasks, ask your group teacher.

**Answers are delivered through Devilry by Monday, February 23 at 11:59 PM.
It is important that you deliver as described in the bottom of this file.**

### Task 1: Vowel Replacement

In this task, you will complete a program that replaces all vowel occurrences with another letter in a sentence.

The program takes two arguments: one sentence and one letter. All five English vowels in the sentence, i.e. ‘a’, ‘e’, ‘i’, ‘o’ and ‘u’ should be replaced with the letter. Then print the changed sentence to the terminal.

**Example**

```
$ ./vowelshift "Lorem ipsum dolor sit amet" a
Laram apsam dalar sat amat
```

### Exercise 2: String operations

This exercise is about strings and various string operations. You should implement the following functions in the file stringsops-todo.c

Code errors in the implementation can cause segmentation faults in the program. In that case, we recommend that you use Gdb and Valgrind to find out where in the program the error occurs.

(a) stringsum

Write the function

```
int stringsum (char* s)
```

that takes a char pointer as an argument and returns an int value that we call the string sum. We define the string sum as the accumulated value of all characters in the string, where the value corresponds to the alphabetical position: ‘a’ has the value 1, ‘b’ has the value 2, and so on. We do not distinguish between uppercase and lowercase letters. Spaces and the terminating null byte are not included in the sum. If the string contains any characters that are not uppercase or lowercase letters or spaces, the function should return -1.

There are several ways to simplify this task; it may be a good idea to create a simple solution before improving it so that it meets all the criteria in the task.

Tip: A char is a one-byte numeric value, which can have values from -128 to 127, and is most often interpreted as a letter using the ASCII table. This can be exploited for an efficient solution – by calculating the numeric values needed to solve the problem from the ASCII values of the letters.

(b) distance_between

Write the function

```
int distance_between(char* s, char c)
```

which takes a char pointer and a char as arguments and returns the distance (i.e. the difference between the positions) from the first to the last occurrence of the character in the string. If the character occurs only once, the function should return 0. If the character does not occur, the function should return -1.

(c) string_between

Write the function

```
char* string_between(char* s, char c)
```

which takes a char pointer and a char as arguments and returns the substring that is between the first and last occurrence of the character in the string. If the character occurs only once, the function should return the empty string. If the character does not occur, the function should return the null pointer.

If the character occurs at least twice, neither the first nor the last occurrence should be included in the string you return.

Here you should NOT allocate a new string, but instead you should change the input string, and return a pointer to the correct location.

(d) stringsum2

Write the function

```
int stringsum2(char* s, int* res)
```

which works like stringsum, but rather than returning the string sum, it places it in the int that res points to. The function returns 0 in all cases where stringsum would return a number greater than 0. It returns -1 otherwise.

### Exercise 3: The worm in the apple

You have a variable apple that is defined in the file [the_apple.c](the_apple.c).
The variable apple is also declared in the header file [the_apple.h](the_apple.h).

The main functions of the program is located in the file apple-main.c.
The functions mentioned below, which you should implemented, shall be located in the file apple-todo.c

There is only one worm in the apple, but the worm can grow large by duplicating its letters. Then it might look like this:

```
"leappleappleappleappwwwwooooooorrrrrrr\n"
" rrmmmmmlleappleappleappleappleappleappleap\n"
```

(a) Write the function

```
int locateworm(char* apple)
```

that finds the worm in the apple using only basic language constructs such as if ... else, for, while, do, and so on—that is, no functions intended for string manipulation, such as strcpy, strchr, or strstr.

Specifically, the function should return the number that is the (zero-based) array index of the first letter belonging to the worm, or -1 if the worm does not exist.

(b) Write the function

```
int removeworm(char* apple)
```

that cuts out the worm from the apple by overwriting it with spaces. The function returns the length of the worm (the number of bytes that were replaced with spaces) or 0 if the worm does not exist.

### Compilation

To compile the programs, we have created a specification file called CMakeLists.txt. These files are read by a software package called CMake, which can create Makefiles on Linux. It can also create project files for Visual Studio or XCode, but for IN2140 you will use terminal windows and Makefiles.

You can download and compile this project as follows:
- open a terminal
- in the terminal, unpack the provided files:
```
tar zxvf oblig-01.tgz
```
- go into the oblig-01 directory
```
cd oblig-01
```
- create a subdirectory to build the programs from the provided source code
```
mkdir build
```
- go into the build directory
```
cd build
```
- use CMake to create a Makefile that suits your machine
```
cmake ..
```
- compile to create executable files from the wedge code
```
make
```
- run the programs, e.g.
```
./vowelshift "This is a text on the command line" u
```

If you need to install CMake on:
| OS      | Metode  |
|---------|---------|
| MacOS   | Manual: Download from https://cmake.org/download/ |
| MacOS   | With Homebrew: brew install cmake |
| Linux   | Manual: Download from https://cmake.org/download/ |
| Linux   | using Apt: sudo apt-get install cmake |
| Linux   | using Snap: sudo snap install cmake |
| Windows | Manual: Download from Download from https://cmake.org/download/ |
| Windows | For Visual Studio integration see https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170 |

### Delivery

You should submit your code to [Devilry](https://devilry.ifi.uio.no/) as an archive file.
The archive file should be a Zip file and must contain all source files and documentation files.

If you follow the 'make' recipe under [Compilation](#Compilation), you can create the archive file
by calling
```
make package_source
```
The file is then named `HomeExam01-1.0-Source.zip`.
