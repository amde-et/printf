#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * multiply - Computes the product of a number and a multiple of 10
 * @num: The first number
 * @multiple: The second number (a multiple of 10)
 *
 * Return: A pointer containing the result, otherwise program fails
 */
char *multiply(char *num, char *multiple)
{
	int size, mult_len, num_len, i, j;
	char *result, rem, carry = 0;

	mult_len = str_len(multiple);
	num_len = str_len(num);
	size = mult_len + num_len;
	result = malloc(sizeof(char) * (size + 1));
	if (result != NULL)
	{
		mem_set(result, size, '0');
		*(result + size) = '\0';
		mult_len--;
		j = size - mult_len - 1;
		for (i = 1; i <= mult_len; i++)
			*(result + size - i) = '0';
		for (i = num_len - 1; i >= 0; i--)
		{
			if (!(*(num + i) >= '0' && *(num + i) <= '9'))
				break;
			if (!(*multiple >= '0' && *multiple <= '9'))
				break;
			rem = ((*(num + i) - '0') * (*multiple - '0') + carry) % 10;
			carry = ((*(num + i) - '0') * (*multiple - '0') + carry) / 10;
			*(result + j) = rem + '0';
			j--;
		}
		if (carry > 0)
			*(result + j) = carry + '0';
		return (result);
	}
	return (NULL);
}

/**
 * add_int - Adds two positive integers
 * @left: The first number
 * @right: The second number
 * @can_free: Specifies whether the given numbers can be freed
 *
 * Return: The sum of the two integers, otherwise NULL
 */
char *add_int(char *left, char *right, int can_free)
{
	int i, size, len1, len2;
	char dig1, dig2, carry, rem, *result;

	len1 = str_len(left);
	len2 = str_len(right);
	size = MAX(len1, len2) + 1;
	result = malloc(sizeof(char) * (size + 1));
	if (result)
	{
		mem_set(result, size, '0');
		carry = 0;
		i = size - 1;
		len1--;
		len2--;
		for (; i >= 0; i--)
		{
			dig1 = len1 >= 0 ? *(left + len1) - '0' : 0;
			dig2 = len2 >= 0 ? *(right + len2) - '0' : 0;
			rem = (dig1 + dig2 + carry) % 10;
			carry = (dig1 + dig2 + carry) / 10;
			*(result + i) = rem + '0';
			len1--;
			len2--;
		}
		*(result + size) = '\0';
		result = trim_start(result, '0', TRUE);
		if (can_free)
		{
			free(left);
			free(right);
		}
	}
	return (result);
}

/**
 * add_float - Adds two positive floating point numbers
 * @left: The first number
 * @right: The second number
 * @can_free: Specifies whether the given numbers can be freed
 *
 * Return: The sum of the two floats, otherwise NULL
 */
char *add_float(char *left, char *right, char can_free)
{
	int len1, len2, dec_pos1, dec_pos2, frac_len1, frac_len2, size;
	int i, rem, carry, dig1, dig2, dec_pos;
	char *sum, trim;

	for (len1 = 0; *(left + len1) != '\0'; len1++)
		dec_pos1 = *(left + len1) == '.' ? len1 : dec_pos1;
	for (len2 = 0; *(right + len2) != '\0'; len2++)
		dec_pos2 = *(right + len2) == '.' ? len2 : dec_pos2;
	frac_len1 = len1 - dec_pos1 - 1, frac_len2 = len2 - dec_pos2 - 1;
	dec_pos = frac_len1 > frac_len2 ? dec_pos1 : dec_pos2;
	size = MAX(len1, len2) + 1, sum = malloc(sizeof(char) * (size + 1));
	if (sum == NULL)
		return (NULL);
	mem_set(sum, size, '0'), carry = 0, len1--, len2--;
	for (i = size - 1; i >= 0; i--)
	{
		frac_len1 = len1 - dec_pos1 - 1, frac_len2 = len2 - dec_pos2 - 1;
		dig1 = len1 > dec_pos1
			? ((len1 - dec_pos1 - 1) >= frac_len2 ? *(left + len1) - '0' : 0)
			: ((len1 == dec_pos1) || (len1 < 0) ? 0 : *(left + len1) - '0');
		len1 -= (len1 > dec_pos1
			? ((len1 - dec_pos1 - 1) >= frac_len2 ? 1 : 0)
			: (len2 <= dec_pos2 ? 1 : 0));
		dig2 = len2 > dec_pos2
			? ((len2 - dec_pos2 - 1) >= frac_len1 ? *(right + len2) - '0' : 0)
			: ((len2 == dec_pos2) || (len2 < 0) ? 0 : *(right + len2) - '0');
		len2 -= (len2 > dec_pos2
			? ((len2 - dec_pos2 - 1) >= frac_len1 ? 1 : 0)
			: (len1 <= dec_pos1 ? 1 : 0));
		rem = (dig1 + dig2 + carry) % 10, carry = (dig1 + dig2 + carry) / 10;
		*(sum + i) = (i - 1 == dec_pos) ? '.' : rem + '0';
	}
	*(sum + size) = '\0';
	if ((can_free >> 0) & TRUE)
		free(left);
	if ((can_free >> 1) & TRUE)
		free(right);
	trim = (size > 1) && (sum[0] == '0');
	return (trim ? sub_str(sum, 1, 01) : sum);
}

/**
 * mul_int - Computes the product of two positive integers
 * @left: The first number
 * @right: The second number
 * @can_free: Specifies whether the given numbers can be freed
 *
 * Return: The product of the two numbers, otherwise NULL
 */
char *mul_int(char *left, char *right, char can_free)
{
	char *result, *product;
	int size, i, len2;

	size = str_len(left);
	len2 = str_len(right);
	size += len2;
	result = malloc(sizeof(char) * (size + 1));
	if (result != NULL)
	{
		mem_set(result, size, '0');
		*(result + size) = '\0';
		for (i = 0; i < len2; i++)
		{
			product = multiply(left, right + i);
			result = add_int(product, result, TRUE);
		}
		while (*result == '0' && *(result + 1) != '\0')
			left_shift(result, size);
		if (can_free)
		{
			free(left);
			free(right);
		}
	}
	return (result);
}

/**
 * mul_float - Computes the product of two positive floats
 * @left: The first number
 * @right: The second number
 * @can_free: Specifies whether the given numbers can be freed
 *
 * Return: The product of the two floats, otherwise NULL
 */
char *mul_float(char *left, char *right, char can_free)
{
	char *left_c = str_copy(left);
	char *right_c = str_copy(right);
	int len1, len2, dec_pos1, dec_pos2, frac_len1, frac_len2, size, old_size;
	char *product;

	len1 = str_len(left_c);
	len2 = str_len(right_c);
	dec_pos1 = index_of(left_c, '.');
	dec_pos2 = index_of(right_c, '.');
	frac_len1 = len1 - (dec_pos1 + 1);
	frac_len2 = len2 - (dec_pos2 + 1);
	if (frac_len1 < frac_len2)
		left_c = append_char(left_c, '0', frac_len2 - frac_len1, TRUE);
	if (frac_len2 < frac_len1)
		right_c = append_char(right_c, '0', frac_len1 - frac_len2, TRUE);
	size = MAX(len1, len2);
	product = malloc(sizeof(char) * (size + 1));
	if (product)
	{
		mem_set(product, size, '0');
		left_c = delete_char(left_c, '.', TRUE);
		right_c = delete_char(right_c, '.', TRUE);
		old_size = size - 1;
		product = mul_int(left_c, right_c, TRUE);
		size = str_len(product) - old_size;
		product = insert_char(product,
			size - MAX(frac_len1, frac_len2) + 1, '.', TRUE);
		product = trim_end(product, '0', TRUE);
		if (can_free)
		{
			free(left);
			free(right);
		}
	}
	return (product);
}
