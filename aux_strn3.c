
#include "main.h"

/**
 * rev_string - reverses a string.
 * @str: string.
 * Return: no return.
 */
void rev_string(char *str)
{
	int count = 0, i, j;
	char *strn, temp;

	while (count >= 0)
	{
		if (str[count] == '\0')
			break;
		count++;
	}
	strn = str;
	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(strn + j);
			*(strn + j) = *(strn + (j - 1));
			*(strn + (j - 1)) = temp;
		}
	}
}
