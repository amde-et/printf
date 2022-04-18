#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * convert_fmt_di - Prints a signed integer
 * @args_list: The arguments list
 * @fmt_info: The format info
 *
 * Return: The number of characters written
 */
void convert_fmt_di(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, len = 0, zeros_count = 0, num_len;
	long num;
	char *str, inv_plus;

	if (fmt_info->is_long)
		num = va_arg(*args_list, long);
	else if (fmt_info->is_short)
		num = (short)va_arg(*args_list, long);
	else
		num = va_arg(*args_list, int);
	str = long_to_str(num);
	if (str)
	{
		inv_plus = num >= 0 && (fmt_info->show_sign || fmt_info->space) ? 1 : 0;
		if (fmt_info->is_precision_set && !fmt_info->prec && !num)
		{
			print_repeat(' ', fmt_info->width);
		}
		else
		{
			num_len = str_len(str) + (inv_plus ? 1 : 0);
			if (fmt_info->is_precision_set)
				zeros_count = MAX(fmt_info->prec + (inv_plus || num < 0 ? 1 : 0),
					num_len) - num_len;
			else
				zeros_count = fmt_info->pad == '0' ? MAX(fmt_info->width,
					num_len) - num_len : 0;
			if (fmt_info->is_width_set)
				len = (MAX(fmt_info->width, num_len) - num_len) - zeros_count;
			for (i = 0; !fmt_info->left && i < len; i++)
				_putchar(' ');
			if (num < 0 || inv_plus)
				_putchar(num < 0 ? '-'
					: (fmt_info->space && !fmt_info->show_sign ? ' ' : '+'));
			put_num(zeros_count, num, str);
			for (i = 0; fmt_info->left && i < len; i++)
				_putchar(' ');
		}
		free(str);
	}
}

/**
 * convert_fmt_xX - Prints the hexadecimal format of an unsigned int argument
 * @args_list: The arguments list
 * @fmt_info: The format info
 *
 * Return: The number of characters written
 */
void convert_fmt_xX(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, len = 0, zeros_count = 0, max_w, max_p, num_len;
	unsigned long num;
	char *str;

	if (fmt_info->is_short)
		num = (va_arg(*args_list, unsigned long) << 2 * 8) >> 2 * 8;
	else if (fmt_info->is_long)
		num = va_arg(*args_list, unsigned long);
	else
		num = va_arg(*args_list, unsigned int);
	str = u_long_to_hex(num, fmt_info->spec == 'X');
	if (str)
	{
		if (fmt_info->is_precision_set && !fmt_info->prec && !num)
		{
			print_repeat(' ', fmt_info->width);
		}
		else
		{
			num_len = str_len(str) + (num ? fmt_info->alt * 2 : 0);
			max_w = MAX(fmt_info->width, num_len), max_p = MAX(fmt_info->prec, num_len);
			zeros_count = (max_p - num_len) * !fmt_info->left;
			len = max_w - (NO_NEG(zeros_count) + num_len);
			for (i = 0; !fmt_info->left && i < len; i++)
				_putchar(fmt_info->pad);
			if (fmt_info->alt && num)
				_putstr(fmt_info->spec == 'X' ? "0X" : "0x");
			for (i = 0; i < zeros_count; i++)
				_putchar('0');
			for (i = 0; *(str + i) != '\0'; i++)
			{
				_putchar(*(str + i));
			}
			for (i = 0; fmt_info->left && i < len; i++)
				_putchar(' ');
		}
		free(str);
	}
}

/**
 * convert_fmt_o - Prints the octadecimal format of a signed int argument
 * @args_list: The arguments list
 * @fmt_info: The format info
 *
 * Return: The number of characters written
 */
void convert_fmt_o(va_list *args_list, fmt_info_t *fmt_info)
{
	int i = 0, zeros_count = 0, num_len = 0, len = 0, max_w, max_p;
	unsigned long num;
	char *str;

	if (fmt_info->is_long)
		num = va_arg(*args_list, unsigned long);
	else if (fmt_info->is_short)
		num = (va_arg(*args_list, unsigned long) << 2 * 8) >> 2 * 8;
	else
		num = va_arg(*args_list, unsigned int);
	str = long_to_oct(num);
	if (str)
	{
		if (fmt_info->is_precision_set && !fmt_info->prec && !num)
		{
			print_repeat(' ', fmt_info->width);
		}
		else
		{
			num_len = NO_LESS(str_len(str), 1);
			max_w = MAX(fmt_info->width, num_len);
			max_p = MAX(fmt_info->prec, num_len);
			zeros_count = (max_p - num_len) * !fmt_info->left;
			len = max_w - (NO_NEG(zeros_count) + num_len);
			for (i = 0; !fmt_info->left && i < len; i++)
				_putchar(fmt_info->pad);
			if (fmt_info->alt && zeros_count == 0 && num)
				_putchar('0');
			for (i = 0; i < zeros_count; i++)
				_putchar('0');
			for (i = 0; *(str + i) != '\0'; i++)
				_putchar(*(str + i));
			for (i = 0; fmt_info->left && i < len; i++)
				_putchar(' ');
		}
		free(str);
	}
}

/**
 * convert_fmt_u - Prints an unsigned integer
 * @args_list: The arguments list
 * @fmt_info: The format info
 */
void convert_fmt_u(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, len = 0, zeros_count = 0, num_len;
	unsigned long num, max_w, max_p;
	char *str;

	if (fmt_info->is_long)
		num = va_arg(*args_list, unsigned long);
	else if (fmt_info->is_short)
		num = (va_arg(*args_list, unsigned int) << 2 * 8) >> 2 * 8;
	else
		num = va_arg(*args_list, unsigned int);
	str = u_long_to_str(num);
	if (str)
	{
		if (FMT_PREC_EMPTY(fmt_info) && !num)
		{
			print_repeat(' ', fmt_info->width);
		}
		else
		{
			num_len = str_len(str);
			max_w = MAX(fmt_info->width, num_len);
			max_p = MAX(fmt_info->prec, num_len);
			zeros_count = (max_p - num_len) * !fmt_info->left;
			len = max_w - (NO_NEG(zeros_count) + num_len);
			for (i = 0; !fmt_info->left && i < len; i++)
				_putchar(fmt_info->pad);
			for (i = 0; i < zeros_count; i++)
				_putchar('0');
			for (i = 0; *(str + i) != '\0'; i++)
				_putchar(*(str + i));
			for (i = 0; fmt_info->left && i < len; i++)
				_putchar(' ');
		}
		free(str);
	}
}
