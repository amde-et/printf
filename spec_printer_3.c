#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * convert_fmt_fF - Prints the decimal representation of a double
 * @args_list: The arguments list
 * @fmt_info: The format info
 *
 * Return: The number of characters written
 */
void convert_fmt_fF(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, len, num_len, zeros_count, max_w;
	double num = va_arg(*args_list, double);
	char *str, has_sign = (fmt_info->show_sign && num >= 0) || num < 0;
	ushort_t exp_size = fmt_info->is_long_double ? 15 : 11;
	ushort_t mant_size = fmt_info->is_long_double ? 64 : 52;
	float_info_t *flt_info;

	flt_info = new_float_info(exp_size, mant_size);
	if (flt_info != NULL)
	{
		set_float_parts(num, exp_size, mant_size, flt_info);
		str = is_invalid(flt_info);
		if (str == NULL)
		{
			str = float_to_str(flt_info, FALSE);
			str = round_float(str, fmt_info->is_precision_set ? fmt_info->prec : 6, T);
			num_len = str_len(str) + ((fmt_info->show_sign && num >= 0) ? 1 : 0);
			max_w = MAX(fmt_info->width, num_len);
			zeros_count = (max_w - num_len) * !fmt_info->left * (fmt_info->pad == '0');
			len = max_w - (zeros_count + num_len);
			for (i = 0; !fmt_info->left && i < len; i++)
				_putchar(' ');
			if (has_sign)
				_putchar(num < 0 ? '-' : '+');
			for (i = 0; !fmt_info->left && i < zeros_count; i++)
				_putchar('0');
			for (i = has_sign ? 1 : 0; *(str + i) != '\0'; i++)
				_putchar(*(str + i));
			for (i = 0; fmt_info->left && i < len; i++)
				_putchar(' ');
		}
		else
		{
			for (i = 0; i < str_len(str); i++)
				_putchar(fmt_info->spec == 'f' ? TO_LOWER(str[i]) : TO_UPPER(str[i]));
		}
		if (str != NULL)
			free(str);
		free_float_info(flt_info);
	}
}
