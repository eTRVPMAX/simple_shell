#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}
/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * Return: pointer to the resulting string
 */
char *_strcat(char *dest, const char *src)
{
	char *ptr = dest;

	while (*ptr != '\0')
	{
		ptr++;
	}

	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}

	*ptr = '\0';

	return (dest);
}
/**
 * _putchar - Writes a character to the output.
 * @c: character to print
 * Return: character to standard output
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * _puts - prints a string to stdout
 * @str: pointer to the string to print
 * Return: void
 */
void _puts(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
	_putchar('\n');
}
/**
 * _strchr - Locates the first occurrence of a character in a string
 * @str: The string to search in
 * @c: The character to locate
 * Return: Pointer to the first occurrence of the character in the string,
 * or NULL if the character is not found
 */
char *_strchr(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
		{
			return (str);
		}
		str++;
	}
	return (NULL);
}

