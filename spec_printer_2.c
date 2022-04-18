#include <stdarg.h>
#include <stdlib.h>
#include "main.h"

/**
 * convert_fmt_b - Prints the binary format of an unsigned int argument
 * @args_list: The arguments list
 * @fmt_info: The format info
 */
void convert_fmt_b(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, size = 32, len = 0;
	unsigned int num = va_arg(*args_list, unsigned int), tmp;
	char *str;

	str = malloc(sizeof(char) * (size + 1));
	if (str)
	{
		mem_set(str, size, '\0');
		tmp = num;
		for (i = 0; i < size && tmp > 0; i++, len++)
		{
			*(str + i) = (tmp % 2) + '0';
			tmp /= 2;
		}
		if (!fmt_info->left)
		{
			for (i = 0; i < MAX(len, fmt_info->width) - len; i++)
				_putchar(fmt_info->pad);
		}
		for (i = size - 1; i >= 0; i--)
		{
			if (*(str + i) != '\0')
				_putchar(*(str + i));
		}
		if (num == 0)
			_putchar('0');
		if (fmt_info->left)
		{
			for (i = 0; i < MAX(len, fmt_info->width) - len; i++)
				_putchar(' ');
		}
	}
}

/**
 * convert_fmt_S - Prints a string and the hex code for
 * \ non-printable characters
 * @args_list: The arguments list
 * @fmt_info: The format info
 *
 * Return: The number of characters written
 */
void convert_fmt_S(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, len;
	char *str = va_arg(*args_list, char *);

	if (str)
	{
		len = str_len(str);
		if (!fmt_info->left)
		{
			for (i = 0; i < MAX(len, fmt_info->width) - len; i++)
				_putchar(fmt_info->pad);
		}
		for (i = 0; *(str + i) != '\0'; i++)
		{
			if (*(str + i) < 32 || *(str + i) >= 127)
			{
				_putchar('\\');
				_putchar('x');
				_putchar(TO_UPPER(hex_digit(*(str + i) / 16)));
				_putchar(TO_UPPER(hex_digit(*(str + i) % 16)));
			}
			else
			{
				_putchar(*(str + i));
			}
		}
		if (fmt_info->left)
		{
			for (i = 0; i < MAX(len, fmt_info->width) - len; i++)
				_putchar(fmt_info->pad);
		}
	}
	else
	{
		_putstr("(null)");
	}
}

/**
 * convert_fmt_R - Prints the rot13'ed string
 * @args_list: The arguments list
 * @fmt_info: The format info
 *
 * Return: The number of characters written
 */
void convert_fmt_R(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, len, is_low_1, is_low_2, is_upper, is_lower;
	char *str = va_arg(*args_list, char *);

	if (str)
	{
		len = str_len(str);
		if (!fmt_info->left)
		{
			for (i = 0; i < MAX(len, fmt_info->width) - len; i++)
				_putchar(fmt_info->pad);
		}
		for (i = 0; str && *(str + i) != '\0'; i++)
		{
			is_low_1 = *(str + i) >= 'a' && *(str + i) <= 'm';
			is_low_2 = *(str + i) >= 'A' && *(str + i) <= 'M';
			is_upper = *(str + i) >= 'A' && *(str + i) <= 'Z';
			is_lower = *(str + i) >= 'a' && *(str + i) <= 'z';

			if (is_lower || is_upper)
				_putchar(((is_low_1 + is_low_2) * (*(str + i) + 13))
					+ ((1 - is_low_1 - is_low_2) * (*(str + i) - 13)));
			else
				_putchar(*(str + i));
		}
		if (fmt_info->left)
		{
			for (i = 0; i < MAX(len, fmt_info->width) - len; i++)
				_putchar(fmt_info->pad);
		}
	}
}

/**
 * convert_fmt_r - Prints the reversed string
 * @args_list: The arguments list
 * @fmt_info: The format info
 *
 * Return: The number of characters written
 */
void convert_fmt_r(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, len;
	char *str = va_arg(*args_list, char *);

	if (str)
	{
		len = str_len(str);
		if (!fmt_info->left)
		{
			for (i = 0; i < MAX(len, fmt_info->width) - len; i++)
				_putchar(fmt_info->pad);
		}
		for (i = len - 1; i >= 0; i--)
		{
			_putchar(*(str + i));
		}
		if (fmt_info->left)
		{
			for (i = 0; i < MAX(len, fmt_info->width) - len; i++)
				_putchar(fmt_info->pad);
		}
	}
}
