#include "main.h"

/**
 * is_digit - Checks if the given character is a digit character
 * @c: The character to check
 *
 * Return: 1 or 0
 */
char is_digit(char c)
{
	return (c >= '0' && c <= '9' ? TRUE : FALSE);
}

/**
 * is_non_custom_specifier - Checks if the given character is a non-custom
 * specifier character
 * @c: The character to check
 *
 * Return: 1 or 0
 */
char is_non_custom_specifier(char c)
{
	switch (c)
	{
	case '%':
	case 'c':
	case 'd':
	case 'E':
	case 'e':
	case 'F':
	case 'f':
	case 'i':
	case 'n':
	case 'o':
	case 'p':
	case 's':
	case 'u':
	case 'X':
	case 'x':
		return (TRUE);
	default:
		return (FALSE);
	}
}

/**
 * is_specifier - Checks if the given character is a
 * \ specifier character
 * @c: The character to check
 *
 * Return: 1 or 0
 */
char is_specifier(char c)
{
	if (is_non_custom_specifier(c))
	{
		return (TRUE);
	}
	else
	{
		switch (c)
		{
		case 'b':
		case 'R':
		case 'r':
		case 'S':
			return (TRUE);
		default:
			return (FALSE);
		}
	}
}

/**
 * is_flag - Checks if the given character is a flag character
 * @c: The character to check
 *
 * Return: 1 or 0
 */
char is_flag(char c)
{
	switch (c)
	{
	case '-':
	case '+':
	case '\'':
	case ' ':
	case '#':
	case '0':
		return (TRUE);
	default:
		return (FALSE);
	}
}

/**
 * is_length - Checks if the given character is a length character
 * @c: The character to check
 *
 * Return: 1 or 0
 */
char is_length(char c)
{
	switch (c)
	{
	case 'h':
	case 'l':
		return (TRUE);
	default:
		return (FALSE);
	}
}
