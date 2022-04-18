# printf
_printf
_printf is a simple custom printf function that formats and prints data to the standard output.

Description
_printf() functiion formats and prints data to the standard output according to the format specified.

The function has the following conversion specifies:

%c - prints a character
%d - prints a integer
%s - prints a string
%i - prints an integer
% - prints percentage;
%b - print binary numbers
%u - print unsigned integers of type int
%x - print hexadecimal numbers in lowercase
%X - print hexadecimal numbers in uppercase
%o - print octal numbers
%r - prints string in reverse order
%R - prints string in ROT13 encoding
%p - print pointer addresses
' ' - print a space
- modifier for unsigned conversions
+: prints a plus sign in front of the number
Installation
you can clone this repository and use the function on your local machine.

git clone https://github.com/Abinet508/printf.git
Usage
include the main.h header file on the function for using _printf().
All the files are to be compiled on Ubuntu 14.04 LTS
Compile your code with `gcc -Wall -Werror -Wextra -pedantic *.c`
#include <stdio.h>
#include "main.h"

int main(void)
{
    int i = 10;
    int print;
    char *s = "printf by Teddy & Mark";
    _printf("%d %s %c\n", i, s, 'c');
     print =  _printf("%d", s); /* get number of characters */
     printf("%d\n", print); /* print number of characters */
    return 0;
}

Copyright
Copyright (c) 2022 Amdebirhan Abebe Abel Yitages
