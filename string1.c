#include "shell.h"

/**
 * _strcpy - copy a string
 * @dest: destination
 * @src: source
 *
 * Return: pointer to des
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the input string
 *
 * Return: pointer to the result
 */
char *_strdup(const char *str)
{
	int leng = 0;
	char *r;

	if (str == NULL)
		return (NULL);
	while (*str++)
		leng++;
	r = malloc(sizeof(char) * (leng + 1));
	if (!r)
		return (NULL);
	for (leng++; leng--;)
		r[leng] = *--str;
	return (r);
}

/**
 *_puts - prints a string
 *@str: the input string
 *
 * Return: void
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar - writes c to stdout
 * @c: The input character
 *
 * Return: success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int j;
	static char bu[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, bu, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		bu[j++] = c;
	return (1);
}
