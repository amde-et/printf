#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * set_float_parts - Sets the float_info fields to the appropriate
 * \ parts of a given float
 * @num: The given float
 * @exponent_size: The number of bits in the exponent part
 * @mantissa_size: The number of bits in the mantissa part
 * @float_info: The float_info struct
 */
void set_float_parts(double num,	uchar_t exponent_size,
	uchar_t mantissa_size, float_info_t *float_info)
{
	int i;
	char *str;
	uchar_t size = exponent_size + mantissa_size + 1;
	size_t tmp = *((size_t *)&num);

	if (float_info == NULL)
		return;
	str = malloc(sizeof(char) * (size + 1));
	if (str != NULL)
	{
		for (i = 0; i < size; i++)
			*(str + i) = ((tmp >> i) & 1)  + '0';
		*(str + size) = '\0';
		rev_string(str);
		float_info->sign = *str;
		for (i = 0; i < exponent_size; i++)
			*(float_info->exponent + i) = *(str + i + 1);
		*(float_info->exponent + i) = '\0';
		for (i = 0; i < mantissa_size; i++)
			*(float_info->mantissa + i) = *(str + i + exponent_size + 1);
		*(float_info->mantissa + i) = '\0';
		free(str);
	}
}

/**
 * mantissa_to_dec_fraction - Converts the mantissa of a float to a fraction
 * @mantissa: The mantissa to convert
 * @frac_len: The maximum length of the decimal fraction
 *
 * Return: The converted fraction
 */
char *mantissa_to_dec_fraction(char *mantissa, unsigned short frac_len)
{
	char *str, i, *pow2;
	int len = str_len(mantissa);

	str = malloc(sizeof(char) * (frac_len + 3));
	if (str != NULL)
	{
		mem_set(str, frac_len + 2, '0');
		*(str + 1) = '.';
		*(str + frac_len + 2) = '\0';
		for (i = 0; i < len; i++)
		{
			if (*(mantissa + i) == '1')
			{
				pow2 = two_exp(-(i + 1));
				str = add_float(pow2, str, TRUE);
			}
		}
	}
	return (str);
}

/**
 * float_to_str - Converts an IEEE 754 float to its string representation
 * @flt_info: The information about the float
 * @can_free: Specifies whether the given numbers can be freed
 *
 * Return: The string representation of the float, otherwise NULL
 */
char *float_to_str(float_info_t *flt_info, char can_free)
{
	uchar_t exponent_size = str_len(flt_info->exponent);
	short bias = two_pexp(exponent_size) / 2 - 1, exponent;
	char *power, *fraction, *product, *float_num, *pow_frac;
	unsigned short frac_len = 22;/* Only doubles are supported */

	exponent = bin_to_int(flt_info->exponent) - bias;
	power = two_exp(exponent);
	fraction = mantissa_to_dec_fraction(flt_info->mantissa, frac_len);
	fraction[0] = '1';
	if (exponent >= 0)
	{
		pow_frac = malloc(sizeof(char) * 3);
		if (pow_frac)
		{
			*(pow_frac + 0) = '.';
			*(pow_frac + 1) = '0';
			*(pow_frac + 2) = '\0';
			power = str_cat(power, pow_frac, TRUE);
		}
	}
	product = mul_float(fraction, power, TRUE);
	float_num = str_cat(flt_info->sign == '1' ? "-" : "", product, FALSE);
	free(product);
	if (can_free)
		free_float_info(flt_info);
	return (float_num);
}
