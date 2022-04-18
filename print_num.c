#include "main.h"
#include <stdio.h>

/**
 * print_num - prints the digits of an interger
 * @n: integer to be printed
 * Return: no return value
 */
int print_num(long int n)
{
	unsigned long int x, base;
	int chars_printed = 0;

	x = 0;
	base = 10;
	if (n < 0)
	{
		chars_printed += _putchar(45);
		x = -n;
	}
	else
	{
		x = n;
	}
	if (x < base)
	{
		chars_printed += _putchar('0' + x);
	}
	else
	{
		while (x >= base)
		{
			base *= 10;
			if (base == 1000000000000000000)
				break;
		}
		if (!(x > 1000000000000000000))
			base /= 10;
		chars_printed += _putchar('0' + (x / base));
		base /= 10;
		while (base >= 10)
		{
			chars_printed += _putchar('0' + ((x / base) % 10));
			base /= 10;
		}
		chars_printed += _putchar('0' + (x % 10));
	}
	return (chars_printed);
}
