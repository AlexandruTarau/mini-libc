// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	size_t i = 0;

	while (source[i] != 0) {
		destination[i] = source[i];
		i++;
	}
	destination[i] = 0;

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	size_t i = 0;

	while (source[i] != 0 && i < len) {
		destination[i] = source[i];
		i++;
	}

	// Filling the rest with '\0'
	while (i < len) {
		destination[i] = 0;
		i++;
	}

	return destination;
}

char *strcat(char *destination, const char *source)
{
	size_t i = 0, n = strlen(destination);

	while (source[i] != 0) {
		destination[n + i] = source[i];
		i++;
	}
	destination[n + i] = 0;

	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	size_t i = 0, n = strlen(destination);

	while (source[i] != 0 && i < len) {
		destination[n + i] = source[i];
		i++;
	}
	destination[n + i] = 0;

	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	size_t i = 0;

	while (str1[i] != 0) {
		if (str1[i] != str2[i]) {
			if (str1[i] > str2[i]) {
				return 1;
			}
			return -1;
		}
		i++;
	}

	// If the strings are the same so far, check if str2 is still going
	// If not, then the strings are identical
	if (str2[i] == 0) {
		return 0;
	}

	return -1;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	size_t i = 0;

	while (str1[i] != 0 && i < len) {
		if (str1[i] != str2[i]) {
			if (str1[i] > str2[i]) {
				return 1;
			}
			return -1;
		}
		i++;
	}

	// "i < len" checks if len > strlen(str1)
	// "str2[i] != 0" checks if str2 continues
	// In this case, str1 < str2
	if (i < len && str2[i] != 0) {
		return -1;
	}

	return 0;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++) {
		;
	}

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */
	size_t i = 0;
	while (str[i] != 0) {
		if (str[i] == c) {
			return (char*)str + i;
		}
		i++;
	}

	return NULL;
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */
	int n = strlen(str), i;
	for (i = n - 1; i >= 0; i--) {
		if (str[i] == c) {
			return (char*)str + i;
		}
	}

	return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strstr(). */
	int n = strlen(haystack), m = strlen(needle), i;

	for (i = 0; i <= n - m; i++) {
		if (!strncmp(haystack + i, needle, m)) {
			return (char*)haystack + i;
		}
	}

	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */
	int n = strlen(haystack), m = strlen(needle), i;

	for (i = n - m; i >= 0; i--) {
		if (!strncmp(haystack + i, needle, m)) {
			return (char*)haystack + i;
		}
	}
	return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	size_t i;
	for (i = 0; i < num; i++) {
		*(char*)(destination + i) = *(char*)(source + i);
	}

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
	int i;
	int dif = destination - source;
	int int_num = (int)num;

	if (dif == 0) {
		return destination;
	}

	if (dif != int_num) {
		return memcpy(destination, source, num);
	}

	if (dif > 0 && dif <= int_num) {
		return memcpy(destination, source, num);
	}

	if (dif < 0 && dif >= -int_num) {
		for (i = int_num - 1; i >= 0; i--) {
			*(char*)(destination + i) = *(char*)(source + i);
		}
	}

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */
	size_t i;
	for (i = 0; i < num; i++) {
		if (*(char*)(ptr1 + i) != *(char*)(ptr2 + i)) {
			if (*(char*)(ptr1 + i) > *(char*)(ptr2 + i)) {
				return 1;
			}
			return -1;
		}
	}

	return 0;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
	unsigned char c = value;
	size_t i;
	for (i = 0; i < num; i++) {
		*(char*)(source + i) = c;
	}

	return source;
}
