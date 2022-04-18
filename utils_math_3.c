#include <stdlib.h>
#include "main.h"

/**
 * round_float_to_int - Rounds a floating point number to an integer
 * @num: The floating point number to round
 * @len: The length of the floating-point number
 * @dec_pos: The position of the decimal point in the floating point number
 * @frac_len: The length of the fractional part in the floating point number
 *
 * Return: The integer, otherwise NULL
 */
char *round_float_to_int(char *num, int len, int dec_pos, int frac_len)
{
	int i;
	char *one, *result = NULL;

	result = malloc(sizeof(char) * (len - frac_len));
	if (result != NULL)
	{
		for (i = 0; i < (len - frac_len); i++)
			*(result + i) = *(num + i);
		*(result + i) = '\0';
		one = str_copy("1");
		if (one != NULL)
		{
			if (*(num + dec_pos + 1) != '\0' && *(num + dec_pos + 1) > '4')
				result = add_int(one, result, TRUE);
			else
				free(one);
		}
	}
	return (result);
}

/**
 * round_float - Rounds a floating point number
 * @num: The floating point number to round
 * @precision: The number of precision of the fractional part
 * @can_free: Specifies whether the given numbers can be freed
 *
 * Return: The rounded float, otherwise NULL
 */
char *round_float(char *num, unsigned int precision, char can_free)
{
	unsigned int dec_pos = index_of(num, '.'), len = (unsigned int)str_len(num);
	unsigned int size, frac_len = len - (dec_pos + 1), i;
	char *one, *result = NULL;

	if (precision == 0)
	{
		result = round_float_to_int(num, len, dec_pos, frac_len);
	}
	else if (frac_len != precision)
	{
		if (frac_len > precision)
		{
			size = len - (frac_len - precision);
			result = malloc(sizeof(char) * (size + 1));
			for (i = 0; i < len - (frac_len - precision); i++)
				*(result + i) = *(num + i);
			*(result + i) = '\0';
			if (*(num + (len - (frac_len - precision))) > '4')
			{
				one = str_copy(result);
				mem_set(one, size, '0');
				*(one + dec_pos) = '.';
				*(one + size - 1) = '1';
				result = add_float(result, one, TRUE);
			}
		}
		else
		{
			result = str_copy(num);
			result = append_char(result, '0', precision - frac_len, TRUE);
		}
	}
	if (can_free)
		free(num);
	return (result);
}
