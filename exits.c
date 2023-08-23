#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination
 *@src: the source
 *@n: number of characters
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *st = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (st);
}

/**
 **_strncat - concatenates two strings
 *@dest: 1st string
 *@src: 2nd string
 *@n: the amount of bytes to be maximally used
 *Return: the result string
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *st = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (st);
}

/**
 **_strchr - char locatio in string input
 *@s: the string to check
 *@c: the character to search for
 *Return: pointer to the memory location
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
