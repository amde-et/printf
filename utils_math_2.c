#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * div_by_10_exp - Divides a number by a power of 10
 * @num: The number to divide
 * @n: The power of 10
 * @can_free: Specifies whether the given number can be freed
 *
 * Return: The quotient of the number and the power of 10, otherwise NULL
 */
char *div_by_10_exp(char *num, unsigned short n, char can_free)
{
	char *result;
	int i, j, dec_pos, new_pos, size, len;

	if (n == 0)
		return (num);
	len = str_len(num);
	dec_pos = index_of(num, '.');
	if (dec_pos < 0)
		size = len - n > 0 ? len + 1 : (len - n == 0 ? len + 2 : n - len + len + 2);
	else if (dec_pos > 0)
		size = dec_pos - n > 0 ? len
			: (dec_pos - n == 0 ? len + 1 : len + (n - dec_pos + 1));
	else
		size = len + n + 1;
	new_pos = dec_pos < 0 ? size - n - 1
		: (dec_pos > 0 ? size - (len - dec_pos + n) : 1);
	result = malloc(sizeof(char) * (size + 1));
	if (result)
	{
		mem_set(result, size, '0');
		j = len - 1;
		for (i = size - 1; i >= 0; i--)
		{
			if (i == new_pos)
				*(result + i) = '.';
			i -= (i == new_pos ? 1 : 0);
			if (*(num + j) == '.')
				j--;
			if (*(num + j) != '.' && j >= 0)
				*(result + i) = *(num + j);
			j--;
		}
		*(result + size) = '\0';
		if (can_free)
			free(num);
	}
	return (result);
}

/**
 * two_exp - Computes 2 raised to the given power
 * @n: The power
 *
 * Return: The value of 2 index n, otherwise NULL
 */
char *two_exp(short n)
{
	char *result, *pow_b5;
	short i;

	result = malloc(sizeof(char) * (2));
	if (result)
	{
		*(result + 0) = '1';
		*(result + 1) = '\0';
		if (n > 0)
		{
			for (i = 0; i < n; i++)
			{
				pow_b5 = malloc(sizeof(char) * (2));
				if (pow_b5)
				{
					*(pow_b5 + 0) = '2';
					*(pow_b5 + 1) = '\0';
					result = mul_int(pow_b5, result, TRUE);
				}
			}
		}
		else if (n < 0)
		{
			pow_b5 = five_exp(n * -1);
			result = div_by_10_exp(pow_b5, n * -1, TRUE);
		}
	}
	return (result);
}

/**
 * five_exp - Computes 5 raised to the given positive power
 * @n: The power
 *
 * Return: The value of 5 index n, otherwise NULL
 */
char *five_exp(unsigned short n)
{
	char *result, *base;
	unsigned short i;

	result = malloc(sizeof(char) * (2));
	if (result)
	{
		result[0] = '1';
		result[1] = '\0';
		for (i = 0; i < n; i++)
		{
			base = malloc(sizeof(char) * (2));
			if (base)
			{
				base[0] = '5';
				base[1] = '\0';
				result = mul_int(base, result, TRUE);
			}
		}
	}
	return (result);
}

/**
 * two_pexp - Computes 2 raised to the given positive power
 * @n: The positive index
 *
 * Return: The value of 2 exponent n
 */
unsigned int two_pexp(unsigned int n)
{
	unsigned int result = 1;
	unsigned int i;

	for (i = 0; i < n; i++)
		result *= 2;
	return (result);
}

/**
 * u_long_to_hex - Converts an unsigned long to its string representation
 * @num: The unsigned long number
 * @upper: Specifies whether the hexadecimals should be in uppercase
 *
 * Return: The string representation of the number in hexadecimal notation
 */
char *u_long_to_hex(unsigned long num, char upper)
{
	int i;
	char *str;
	char size = 20;
	unsigned long tmp = num;

	str = malloc(sizeof(char) * (size));
	if (str)
	{
		mem_set(str, size, 0);
		for (i = 0; i <= size && tmp > 0; i++)
		{
			*(str + i) = (tmp % 16) < 10 ? (tmp % 16) + '0'
				: (tmp % 16) - 10 + 'a' + (upper ? -6 - 26 : 0);
			tmp /= 16;
		}
		rev_string(str);
		str = trim_start(str, '0', TRUE);
		str = num == 0 ? str_cat("0", "", FALSE) : str;
	}
	return (str);
}
