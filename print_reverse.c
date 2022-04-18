#include "main.h"

/**
 * print_reverse - prints a string in reverse order, followed by a new line.
 * @s: string to be printed in reverse order
 * Return: number of characters printed
 */
int print_reverse(char *s)
{
	int x, y, z, chars_printed = 0;
	char *str;

	x = 0;
	y = 0;
	z = 0;
	if (s)
	{
		while (*(s + x))
			x++;
		str = malloc(sizeof(char) * x);
		if (str == NULL)
		{
			free(str);
			return (0);
		}
		for (y = (x - 1); y >= 0; y--)
		{
			*(str + z) = *(s + y);
			z++;
		}
		*(str + x) = '\0';
		chars_printed = print_string(str);
		return (chars_printed);
	}
	return (0);
}
