#include "stdarg.h"
#include "unistd.h"

void put_str(char *string, int *length)
{
	if (!string)
		*length += write(1, "(null)", 6);
	while (*string)
		*length += write(1, string++, 1);
}

void put_digit(int number, int base, int *length)
{
	char *hexadecimal = "0123456789abcdef";

	if (number < 0)
	{
		number *= -1;
		*length = write(1, "-", 1);
	}
	if (number >= base)
		put_digit(number / base, base, length);
	*length += write(1, &hexadecimal[number % base], 1);
}

int ft_printf(const char *format, ... )
{
	int length = 0;

	va_list	pointer;
	va_start(pointer, format);

	while (*format)
	{
		if (*format == '%' && *(format+1))
		{
			format++;
			if (*format == 's')
				put_str((char *)va_arg(pointer, char *), &length);
			if (*format == 'd')
				put_digit((long long int)va_arg(pointer, int), 10, &length);
			if (*format == 'x')
				put_digit((long long int)va_arg(pointer, unsigned int), 16, &length);
		}
		else
			length += write(1, format, 1);
		format++;
	}

	return(va_end(pointer), length);
}

int main()
{
	ft_printf("%s", "Halo!");
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	return(1);
}