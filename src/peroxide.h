/*
	* peroxide-h - A safer C library
*/

#ifndef PEROXIDE_H
#define PEROXIDE_H

// Implement necessary libs for system calls

#ifdef __linux__
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
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

#endif // PEROXIDE_H
