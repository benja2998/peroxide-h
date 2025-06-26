/*
	* peroxide-h is a safer C library for C programming language.
*/

#ifndef PEROXIDE_H
#define PEROXIDE_H

// Implement necessary libs for system calls

#ifdef __linux__
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <windows.h> // Microsoft does not want to use consistent syscalls, so we will use windows.h
// TODO: Implement functions for Windows
#endif

// Implement px_strlen

static inline size_t px_strlen(const char *str) {
	if (str == NULL) {
		return 0; // Handle null pointer
	}

	size_t length = 0;
	while (str[length] != '\0') {
		length++;
	}
	return length;
}

// Implement px_print

static inline void px_print(const char *message) {
	if (message == NULL) {
		return; // Handle null pointer
	}

#ifdef __linux__
	// Use write syscall for Linux
	write(STDOUT_FILENO, message, px_strlen(message));
#endif
}

// Implement px_intlen

static inline size_t px_intlen(int number) {
	size_t length = 0;

	if (number < 0) {
		length++; // Count the negative sign
		number = -number; // Make the number positive
	}

	do {
		length++;
		number /= 10;
	} while (number > 0);

	return length;
}

// Implement px_malloc

static inline void *px_malloc(size_t size) {
	if (size == 0) {
		return NULL; // Handle zero allocation
	}

	void *ptr = malloc(size);
	if (ptr == NULL) {
		px_print("Memory allocation failed\n");
		return NULL; // Handle memory allocation failure
	}

	return ptr;
}

// Implement px_atoi

static inline int px_atoi(const char *str) {
	if (str == NULL || *str == '\0') {
		return 0; // Handle null pointer or empty string
	}

	int result = 0;
	int sign = 1;

	// Skip whitespace
	while (*str == ' ') {
		str++;
	}

	// Check for sign
	if (*str == '-') {
		sign = -1;
		str++;
	} else if (*str == '+') {
		str++;
	}

	// Convert string to integer
	while (*str >= '0' && *str <= '9') {
		result = result * 10 + (*str - '0');
		str++;
	}

	return result * sign;
}

// Implement px_itoa

static inline char *px_itoa(int number) {
	// Convert each digit to a character
	
	size_t length = px_intlen(number);

	char *buffer = (char *)px_malloc(length + 1); // +1 for null terminator
	if (buffer == NULL) {
		return NULL; // Handle memory allocation failure
	}

	buffer[length] = '\0'; // Null-terminate the string
	size_t index = length - 1;

	if (number < 0) {
		buffer[0] = '-'; // Handle negative numbers
		number = -number;
		index--;
	}

	do {
		buffer[index] = (number % 10) + '0'; // Convert digit to character
		number /= 10;
		index--;
	} while (number > 0);

	return buffer; // Return the string representation of the integer
}

// Implement px_free

static inline void px_free(void *ptr) {
	if (ptr == NULL) {
		return; // Handle null pointer
	}

	free(ptr); // Free the allocated memory
}

// Implement px_strcopy

static inline char *px_strcopy(const char *source, const char *destination) {
	// Cut out the source string by destination length
	
	if (source == NULL || destination == NULL) {
		return NULL; // Handle null pointers
	}

	size_t dest_length = px_strlen(destination);

	size_t source_length = px_strlen(source);

	if (source_length > dest_length) {
		px_print("Source string is longer than destination buffer\n");
		px_print("Copy operation failed. Your program is safe!\n");
		return NULL; // Handle source longer than destination
	}

	char *result = (char *)px_malloc(dest_length + 1); // +1 for null terminator
	
	if (result == NULL) {
		return NULL; // Handle memory allocation failure
	}

	size_t i;

	for (i = 0; i < source_length && i < dest_length; i++) {
		result[i] = source[i]; // Copy each character
	}

	result[i] = '\0'; // Null-terminate the result string
	
	return result; // Return the copied string
}

#endif // PEROXIDE_H
