#include "main.h"

/**
 * _printf - Function that prints formatted output.
 *
 * @format: a string composed of zero or more characters to print or use as
 * directives that handle subsequent arguments and special characters.
 *
 * Description: This function can take a variable number and type of arguments
 * that should be printed to standard output.
 *
 * Return: int
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i = 0, chars_printed = 0;

	va_start(args, format);
	while (format && format[i])
	{
		if (format[i] != '%')
		{
			chars_printed += _putchar(format[i]);
		}
		else if (format[i + 1])
		{
			i++;
			if (format[i] == 'c' || format[i] == 's')
				chars_printed += format[i] == 'c' ? _putchar(va_arg(args, int)) :
				print_string(va_arg(args, char *));
			else if (format[i] == 'd' || format[i] == 'i')
				chars_printed += print_num(va_arg(args, int));
			else if (format[i] == 'b')
				chars_printed += print_binary((unsigned int)va_arg(args, int));
			else if (format[i] == 'r')
				chars_printed += print_reverse(va_arg(args, char *));
			else if (format[i] == 'R')
				chars_printed += print_rot13(va_arg(args, char *));
			else if (format[i] == 'o' || format[i] == 'u' ||
			format[i] == 'x' || format[i] == 'X')
				chars_printed += print_odh(format[i], (unsigned int)va_arg(args, int));
			else if (format[i] == 'S')
				chars_printed += print_S(va_arg(args, char *));
			else if (format[i] == 'p')
				chars_printed += print_pointer(va_arg(args, void *));
			else
				chars_printed += print_unknown_spec(format[i]);
		}
		i++;
	}
	va_end(args);
	return (chars_printed);
}
