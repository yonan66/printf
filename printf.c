#include "custom_main.h"

void print_custom_buffer(char out[], int *out_ind);

/**
 * custom_printf - Custom Printf function
 * @custom_format: custom format.
 * Return: Number of printed characters.
 */
int custom_printf(const char *custom_format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int custom_flags, custom_width, custom_precision, custom_size, out_ind = 0;
	va_list custom_list;
	char out[CUSTOM_BUFF_SIZE];

	if (custom_format == NULL)
		return (-1);

	va_start(custom_list, custom_format);

	for (i = 0; custom_format && custom_format[i] != '\0'; i++)
	{
		if (custom_format[i] != '%')
		{
			out[out_ind++] = custom_format[i];
			if (out_ind == CUSTOM_BUFF_SIZE)
				print_custom_buffer(out, &out_ind);
			/* write(1, &custom_format[i], 1); */
			printed_chars++;
		}
		else
		{
			print_custom_buffer(out, &out_ind);
			custom_flags = get_custom_flags(custom_format, &i);
			custom_width = get_custom_width(custom_format, &i, custom_list);
			custom_precision = get_custom_precision(custom_format, &i, custom_list);
			custom_size = get_custom_size(custom_format, &i);
			++i;
			printed = handle_custom_print(custom_format, &i, custom_list, out,
				custom_flags, custom_width, custom_precision, custom_size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_custom_buffer(out, &out_ind);

	va_end(custom_list);

	return (printed_chars);
}

/**
 * print_custom_buffer - Prints the contents of the out buffer if it exists
 * @out: Array of characters
 * @out_ind: Index at which to add the next character, represents the length.
 */
void print_custom_buffer(char out[], int *out_ind)
{
	if (*out_ind > 0)
		write(1, &out[0], *out_ind);

	*out_ind = 0;
}
