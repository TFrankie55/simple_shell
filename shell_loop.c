#include "main.h"

/**
 * without_comment - deletes comments from the input
 *
 * @input: input string
 * Return: input without comments
 */
char *without_comment(char *input)
{
	int index, up_to;

	up_to = 0;
	for (index = 0; input[index]; index++)
	{
		if (input[index] == '#')
		{
			if (index == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[index - 1] == ' ' || input[index - 1] == '\t' || input[index - 1] == ';')
				up_to = index;
		}
	}

	if (up_to != 0)
	{
		input = _realloc(input, index, up_to + 1);
		input[up_to] = '\0';
	}

	return (input);
}

/**
 * shell_loop - Loop of shell
 * @datash: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shell_loop(data_shell *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			loop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
