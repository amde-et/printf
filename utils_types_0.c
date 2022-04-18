#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * u_long_to_str - Converts an unsigned long to its string representation
 * @num: The unsigned long integer
 *
 * Return: The string representation of the unsigned long integer
 */
char *u_long_to_str(unsigned long num)
{
	char *str;
	unsigned long rem = num;
	char size = 20, j;

	str = malloc(sizeof(char) * (size + 1));
	if (str)
	{
		*(str + size) = '\0';
		mem_set(str, size, '0');
		j = size - 1;
		while (rem > 0)
		{
			*(str + j) = (rem % 10) + '0';
			rem /= 10;
			j--;
		}
		str = trim_start(str, '0', TRUE);
		str = num == 0 ? str_cat("0", "", FALSE) : str;
	}
	return (str);
}

/**
 * long_to_str - Converts a long to its string representation
 * @num: The long integer
 *
 * Return: The string representation of the long integer
 */
char *long_to_str(long num)
{
	char *str;
	long rem = num;
	char sign = rem < 0 ? -1 : 1;
	char size = 20, j;

	str = malloc(sizeof(char) * (size + 1));
	if (str)
	{
		*(str + size) = '\0';
		mem_set(str, size, '0');
		j = size - 1;
		if (rem == 0)
			*(str + j) = '0';

		while ((sign == -1 && rem < 0) || (sign == 1 && rem > 0))
		{
			*(str + j) = (rem % 10) * sign + '0';
			rem /= 10;
			j--;
		}
		if (sign < 0)
			*(str + j) = '-';
		str = trim_start(str, '0', TRUE);
		str = num == 0 ? str_cat("0", "", FALSE) : str;
	}
	return (str);
}

/**
 * ptr_to_str - Converts a pointer to its string representation
 * @ptr: The pointer
 *
 * Return: The string representation of the pointer
 */
char *ptr_to_str(void *ptr)
{
	int i, size;
	uintptr_t tmp;
	char *str, *str0;

	if (ptr)
	{
		tmp = (uintptr_t)ptr;
		size = sizeof(ptr) * 2;
		str = malloc(sizeof(char) * (size + 1));
		if (str)
		{
			str0 = malloc(sizeof(char) * (2 + 1));
			if (str0)
			{
				mem_set(str, size, '0');
				for (i = 0; i < size; i++)
				{
					*(str + i) = (tmp % 16) < 10 ? (tmp % 16) + '0'
						: (tmp % 16) - 10 + 'a';
					tmp /= 16;
				}
				*(str + i) = '\0';
				*(str0 + 0) = '0';
				*(str0 + 1) = 'x';
				*(str0 + 2) = '\0';
				rev_string(str);
				str = trim_start(str, '0', TRUE);
				str = *str == '\0' ? str_cat("0", "", FALSE) : str;
				str = str_cat(str0, str, TRUE);
			}
			if (!str0)
				free(str);
		}
	}
	else
	{
		str = str_copy("(nil)");
	}
	return (str);
}

/**
 * is_invalid - Checks if a given float is invalid
 * @flt_info: The float info struct to check
 *
 * Return: NULL if it is valid, otherwise inf or nan
 */
char *is_invalid(float_info_t *flt_info)
{
	uchar_t exp_bits_on = 0, exp_all_on;
	short mant_bits_on = 0;
	char lsb_on = FALSE, msb_on = FALSE;
	int i;

	if (flt_info != NULL)
	{
		for (i = 0; *(flt_info->exponent + i) != '\0'; i++)
		{
			if (*(flt_info->exponent + i) == '1')
				exp_bits_on++;
		}
		exp_all_on = i == exp_bits_on;
		for (i = 0; *(flt_info->mantissa + i) != '\0'; i++)
		{
			msb_on = i == 0 && *(flt_info->mantissa + i) == '1' ? TRUE : msb_on;
			lsb_on = *(flt_info->mantissa + i + 1) == '\0'
				&& *(flt_info->mantissa + i) == '1' ? TRUE : lsb_on;
			if (*(flt_info->mantissa + i) == '1')
				mant_bits_on++;
		}
		if (exp_all_on)
		{
			if ((flt_info->sign == '0' && mant_bits_on == 0)
				|| (flt_info->sign == '1' && mant_bits_on == 0))
			{
				return (str_copy("inf"));
			}
			else if ((flt_info->sign == '0' && mant_bits_on == 1 && lsb_on)
				|| (flt_info->sign == '0' && mant_bits_on == 2 && lsb_on && msb_on)
				|| (flt_info->sign == '0' && mant_bits_on == i))
			{
				return (str_copy("nan"));
			}
		}
	}
	return (NULL);
}
