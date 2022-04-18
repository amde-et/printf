#include "main.h"
/**
 * print_S - prints a string with custom formatting
 *
 * @str: string to be formatted
 * Return: number of chars printed
 */
int print_S(char *str)
{
	int i = 0, chars_printed = 0;
	char c;

	while (str[i])
	{
		c = str[i];
		if ((c > 0 && c  < 32) || c >= 127)
		{
			chars_printed += _putchar('\\');
			chars_printed += _putchar('x');
			chars_printed += _putchar('0');
			chars_printed += print_odh('X', (unsigned int)c);
		}
		else
		{
			chars_printed += _putchar(c);
		}
		i++;
	}
	return (chars_printed);
}
