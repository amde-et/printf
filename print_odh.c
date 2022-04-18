#include "main.h"

/**
 * dec_to_oct - converts decimal to octal notation
 *
 * @num: number to be converted
 * Return: characters printed
 */
int dec_to_oct(unsigned int num)
{
	int chars_printed = 0;

	if (!num)
		return (0);
	chars_printed += (dec_to_oct(num / 8));
	chars_printed += _putchar('0' + num % 8);
	return (chars_printed);
}

/**
 * dec_to_hex - converts decimal to hexadecimal notation
 *
 * @c: letter case specifier
 * @num: number to be converted
 * Return: characters printed
 */
int dec_to_hex(char c, unsigned int num)
{
	int chars_printed = 0;

	if (!num)
		return (0);
	chars_printed += dec_to_hex(c, num / 16);
	if (num % 16 < 10)
		chars_printed += _putchar('0' + num % 16);
	else if (num % 16 > 9 && c == 'x')
		chars_printed += _putchar(87 + num % 16);
	else
		chars_printed += _putchar(55 + num % 16);
	return (chars_printed);
}

/**
 * print_odh - prints a number in its octal, decimal or hex representation
 *
 * @c: type to be converted into
 * @num: number to be converted
 * Return: characters printed
 */
int print_odh(char c, unsigned int num)
{
	int chars_printed = 0;

	if (c == 'u')
		chars_printed += print_num(num);
	else if (c == 'o' && num == 0)
		chars_printed = print_string("00");
	else if (c == 'o')
		chars_printed += dec_to_oct(num);
	else if ((c == 'x' || c == 'X') && num == 0)
		chars_printed += print_string("00");
	else
		chars_printed += dec_to_hex(c, num);
	return (chars_printed);
}
