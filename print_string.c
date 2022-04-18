#include "main.h"
/**
  *print_string - prints string followed by a new line.
  *@str: - pointer to char.
  *
  *Return: - returns int. 
  */
int print_string(char *str)
{
	int chars_printed = 0;

	if (str == (char *)0)
		return (print_string("(null)"));
	while (str && str[chars_printed])
	{
		_putchar(str[chars_printed]);
		chars_printed++;
	}
	return (chars_printed);
}
