#include "main.h"

/**
 * print_binary - converts an unsigned int to binary
 * @num: int to be converted
 *
 * Return: no of resulting binary characters
 */
int print_binary(unsigned int num)
{
	int chars_printed = 0, idx = 0;
	char bin[sizeof(unsigned int) * 8];

	if (num == 0)
	{
		chars_printed += _putchar('0');
		return (chars_printed);
	}
	if (num == 1)
	{
		chars_printed += _putchar('1');
		return (chars_printed);
	}
	while (num > 0)
	{
		bin[idx] = '0' + (num % 2);
		num = num / 2;
		idx++;
	}
	idx--;
	while (idx >= 0)
	{
		chars_printed += _putchar(bin[idx]);
		idx--;
	}
	return (chars_printed);
}
