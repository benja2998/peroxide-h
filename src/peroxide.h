/*
 * peroxide-h is a safer C library for C programming language.
 */

#ifndef PEROXIDE_H
#define PEROXIDE_H

// Implement necessary libs for system calls

#ifdef __linux__
#include <stdarg.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <windows.h> // Microsoft does not want to use consistent syscalls, so we will use windows.h
#else
#include <stdio.h>
int main()
{
	printf("Unsupported platform. Please use Linux or Windows.\n");
	return 1; // Exit with an error code
}
#endif

static inline char  *px_itoa(int number);
static inline void   px_free(void *ptr);
static inline size_t px_strlen(const char *str);
static inline void   px_print(const char *format, ...);
static inline size_t px_intlen(int number);
static inline void  *px_malloc(size_t size);
static inline int    px_atoi(const char *str);
static inline char  *px_strcpy(char *destination, const char *source, size_t dest_capacity);

// Implement px_strlen

static inline size_t px_strlen(const char *str)
{
	if (str == NULL)
	{
		return 0; // Handle null pointer
	}

	size_t length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return length;
}

// Implement px_print

static inline void px_print(const char *format, ...)
{
	if (format == NULL)
	{
		return;
	}

#ifdef __linux__
	va_list args;
	va_start(args, format);

	char ch;
	while ((ch = *format++) != '\0')
	{
		if (ch == '%' && *format != '\0')
		{
			switch (*format++)
			{
				case 's':
				{
					const char *str = va_arg(args, const char *);
					if (str)
						write(STDOUT_FILENO, str, px_strlen(str));
					break;
				}
				case 'd':
				{
					int   num = va_arg(args, int);
					char *str = px_itoa(num);
					if (str)
					{
						write(STDOUT_FILENO, str, px_strlen(str));
						px_free(str);
					}
					break;
				}
				default:
					write(STDOUT_FILENO, &ch, 1);
					break;
			}
		}
		else
		{
			write(STDOUT_FILENO, &ch, 1);
		}
	}

	va_end(args);
#endif
}

// Implement px_intlen

static inline size_t px_intlen(int number)
{
	size_t length = 0;

	if (number < 0)
	{
		length++;         // Count the negative sign
		number = -number; // Make the number positive
	}

	do
	{
		length++;
		number /= 10;
	} while (number > 0);

	return length;
}

// Implement px_malloc

static inline void *px_malloc(size_t size)
{
	if (size == 0)
	{
		return NULL; // Handle zero allocation
	}

	void *ptr = malloc(size);
	if (ptr == NULL)
	{
		px_print("Memory allocation failed\n");
		return NULL; // Handle memory allocation failure
	}

	return ptr;
}

// Implement px_atoi

static inline int px_atoi(const char *str)
{
	if (str == NULL || *str == '\0')
	{
		return 0; // Handle null pointer or empty string
	}

	int result = 0;
	int sign = 1;

	// Skip whitespace
	while (*str == ' ')
	{
		str++;
	}

	// Check for sign
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}

	// Convert string to integer
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}

	return result * sign;
}

// Implement px_itoa

static inline char *px_itoa(int number)
{
	// Convert each digit to a character

	size_t length = px_intlen(number);

	char *buffer = (char *)px_malloc(length + 1); // +1 for null terminator
	if (buffer == NULL)
	{
		return NULL; // Handle memory allocation failure
	}

	buffer[length] = '\0'; // Null-terminate the string
	size_t index = length - 1;

	if (number < 0)
	{
		buffer[0] = '-'; // Handle negative numbers
		number = -number;
		index--;
	}

	do
	{
		buffer[index] = (number % 10) + '0'; // Convert digit to character
		number /= 10;
		index--;
	} while (number > 0);

	return buffer; // Return the string representation of the integer
}

// Implement px_free

static inline void px_free(void *ptr)
{
	if (ptr == NULL)
	{
		return; // Handle null pointer
	}

	free(ptr); // Free the allocated memory
}

// Implement px_strcpy

static inline char *px_strcpy(char *destination, const char *source, size_t dest_capacity)
{
	if (destination == NULL || source == NULL || dest_capacity == 0)
	{
		return NULL;
	}

	size_t i;
	for (i = 0; i < dest_capacity - 1 && source[i] != '\0'; i++)
	{
		destination[i] = source[i];
	}

	destination[i] = '\0';

	if (source[i] != '\0')
	{
		px_print("WARNING: Source string is too long for destination buffer\n");
		return NULL;
	}

	return destination;
}

#endif // PEROXIDE_H
