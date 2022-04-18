#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * set_number - Retrieves a number from the given string
 * @str: The string to retrieve the number from
 * @number: The pointer to the number
 *
 * Return: The number of positions that were moved
 */
int set_number(const char *str, int *number)
{
	char digits[11] = {0};
	int i, j = 0;

	for (i = 0; str && *(str + i) != '\0'; i++)
	{
		if (j < 10 && is_digit(*(str + i)))
		{
			digits[j] = *(str + i);
			j++;
		}
		else
		{
			break;
		}
	}
	*number = cmp_nums(digits, MAX_WIDTH) <= 0 ? str_to_int(digits) : 0;
	return (i);
}

/**
 * set_length - Sets the length in a format info struct
 * @cur: The current character
 * @fmt_info: The pointer to the destination fmt_info_t struct
 * @pos: The pointer to the current position in the format string
 */
void set_length(char cur, int *pos, fmt_info_t *fmt_info)
{
	fmt_info->is_long = cur == 'l' ? TRUE : fmt_info->is_long;
	fmt_info->is_short = cur == 'h' ? TRUE : fmt_info->is_short;
	(*pos)++;
}

/**
 * set_flags - Sets the flags in a format info struct
 * @str: The flag character string for set_flags
 * @fmt_info: The pointer to the destination fmt_info_t struct
 *
 * Return: The number of flags that were read
 */
int set_flags(const char *str, fmt_info_t *fmt_info)
{
	int i = 0;

	while (*(str + i) != '\0' && is_flag(*(str + i)))
	{
		fmt_info->space = *(str + i) == ' ' ? TRUE : fmt_info->space;
		fmt_info->left = *(str + i) == '-' || fmt_info->left ? TRUE : FALSE;
		fmt_info->show_sign = *(str + i) == '+' || fmt_info->show_sign
			? TRUE : FALSE;
		fmt_info->group = *(str + i) == '\'' || fmt_info->group ? TRUE : FALSE;
		fmt_info->alt = *(str + i) == '#' || fmt_info->alt ? TRUE : FALSE;
		fmt_info->pad = *(str + i) == '0' ? '0' : fmt_info->pad;
		i++;
	}
	return (i);
}

/**
 * set_precision - Reads a format info data into the given struct
 * @str: The string contained the format tokens
 * @args: The arguments list
 * @fmt_info: The pointer to the destination fmt_info_t struct
 * @i: The pointer to the position in the format string
 * @error_status: The pointer to the error variable
 */
void set_precision(const char *str, va_list args,
	fmt_info_t *fmt_info, int *i, int *error_status)
{
	fmt_info->is_precision_set = TRUE;
	if (*(str + *i) == '*')
	{
		fmt_info->prec = va_arg(args, int);
		(*i)++;
	}
	else if (is_digit(*(str + *i)))
	{
		*i += set_number(str + *i, &(fmt_info->prec));
	}
	else if (is_specifier(*(str + *i)))
	{
		fmt_info->prec = 0;
		/* (*i)--; */
	}
	else
	{
		*error_status = -1;
	}
}

/**
 * read_format_info - Reads a format info data into the given struct
 * @str: The string contained the format tokens
 * @args: The arguments list
 * @fmt_info: The pointer to the destination fmt_info_t struct
 * @last_token: Pointer to the last token from the format specifier
 *
 * Return: The number of positions to skip after the format character (%)
 * , this is negative when there's an error
 */
int read_format_info(const char *str, va_list args,
	fmt_info_t *fmt_info, int *last_token)
{
	int i = 0, no_error = 1, order = 0;

	init_format_info(fmt_info);
	for (; str && *(str + i) != '\0' && !fmt_info->spec && no_error == 1;)
	{
		if (is_flag(*(str + i)) && order < 1)
		{
			i += set_flags(str + i, fmt_info), order = 1;
		}
		else if ((is_digit(*(str + i)) || *(str + i) == '*') && order < 2)
		{
			if (*(str + i) == '*')
				fmt_info->width = va_arg(args, int), i++;
			else
				i += set_number(str + i, &(fmt_info->width));
			fmt_info->is_width_set = TRUE, order = 2;
		}
		else if (*(str + i) == '.' && order < 3)
		{
			i++;
			set_precision(str, args, fmt_info, &i, &no_error), order = 3;
		}
		else if (is_length(*(str + i)) && order < 4)
		{
			set_length(*(str + i), &i, fmt_info), order = 4;
		}
		else if (is_specifier(*(str + i)) && order < 5)
		{
			fmt_info->spec = *(str + i), i++, order = 5;
			break;
		}
		else
		{
			no_error = -1;
		}
	}
	*last_token = order;
	return (i - 1);
}
