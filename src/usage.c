#include "./peroxide.h"

int
main(void)
{
	px_print("Hello, World!\n");

	px_print("This is a simple example of using the peroxide-h library.\n");

	const char* string = "string";

	// Get length of string

	size_t length = px_strlen(string);

	px_print("Length of 'string': ");

	const char* length_str = px_itoa(length);

	px_print(length_str);
	px_print("\n");

	// Use px_strcpy to copy string to a new buffer

	char buff[4];

	px_strcpy(buff, string, sizeof(buff));
	px_print("\nCopied string to buffer: ");
	px_print(buff);

	return 0;
}
