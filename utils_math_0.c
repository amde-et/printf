#include <stdlib.h>
#include "main.h"

/**
 * hex_digit - converts a decimal less than 16 to its hexadecimal form
 * @c: The decimal
 *
 * Return: The hexadecimal digit, otherwise '\0'
 */
char hex_digit(char c)
{
	char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'a', 'b', 'c', 'd', 'e', 'f'
	};

	return (c >= 0 && c <= 15 ? *(digits + c) : '\0');
}

/**
 * cmp_nums - Compares the left number to the right number
 * @left: The left number
 * @right: The right number
 *
 * Return: 1 if left is > right, -1 if left < right, otherwise 0
 */
char cmp_nums(char *left, char *right)
{
	char *num1 = left;
	char *num2 = right;
	int len1 = str_len(num1) - 1, len2 = str_len(num2) - 1, i = 0;

	for (i = 0; (*(num1 + i) == '0' && *(num1 + i + 1) != '\0') && i < len1; i++)
		;
	num1 = num1 + i;
	len1 = str_len(num1);
	for (i = 0; (*(num2 + i) == '0' && *(num2 + i + 1) != '\0') && i < len2; i++)
		;
	num2 = num2 + i;
	len2 = str_len(num2);
	if (len1 > len2)
	{
		return (1);
	}
	else if (len1 < len2)
	{
		return (-1);
	}
	else
	{
		for (i = 0; i < len1; i++)
		{
			if (*(num1 + i) > *(num2 + i))
				return (1);
			if (*(num1 + i) < *(num2 + i))
				return (-1);
		}
		return (0);
	}
}

/**
 * str_to_int - Converts a string to an int
 * @num: The string to convert
 *
 * Return: The converted number
 */
int str_to_int(char *num)
{
	int i = 1, len, exp = 1;
	int res = 0;

	len = str_len(num);
	for (i = len - 1; i >= 0; i--)
	{
		if (*(num + i) == '-')
			res *= -1;
		else if (is_digit(*(num + i)))
		{
			res += (*(num + i) - '0') * exp;
			exp *= 10;
		}
	}
	return (res);
}

/**
 * bin_to_int - Converts an array of bits to an int
 * @bin_str: The array of bits
 *
 * Return: The decimal equivalent of the array of bits
 */
int bin_to_int(char *bin_str)
{
	int len = str_len(bin_str);
	int i;
	int exp = 1;
	int result = 0;

	for (i = len - 1; i >= 0 && *(bin_str + i) != '\0'; i--)
	{
		if (*(bin_str + i) == '0' || *(bin_str + i) == '1')
		{
			result += (*(bin_str + i) - '0') * exp;
			exp *= 2;
		}
	}
	return (result);
}

/**
 * long_to_oct - Converts a long integer to its octal representation
 * @num: The number to convert
 *
 * Return: The octal representation of the number, otherwise NULL
 */
char *long_to_oct(unsigned long num)
{
	int i = 0, size = num == 0 ? 2 : 21;
	unsigned long num_c = num;
	char *str;

	str = malloc(sizeof(char) * (size));
	if (str)
	{
		mem_set(str, size, 0);
		if (num == 0)
		{
			*(str + i) = '0';
			return (str);
		}
		for (i = 0; i <= size; i++)
		{
			*(str + i) = (num_c % 8) + '0';
			num_c /= 8;
		}
		rev_string(str);
		str = trim_start(str, '0', TRUE);
		str = num == 0 ? str_cat("0", "", FALSE) : str;
	}
	return (str);
}
