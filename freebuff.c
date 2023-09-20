#include "shell.h"

/**
* freebuff - frees buffers
* @buf: buffer to be freed
*
* Return: no return
*/
void freebuff(char **buf)
{
	int i = 0;
	int len = 0;

	if (!buf)
		return;

	while (buf[len])
		len++;

	for (; i < len; i++)
	{
		free(buf[i]);
	}

	free(buf);
}

