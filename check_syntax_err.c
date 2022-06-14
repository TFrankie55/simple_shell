#include "main.h"

/**
 * repeated_char - counts the repetitions of a char
 *
 * @input: input string
 * @ind: index
 * Return: repetitions
 */
int repeated_char(char *input, int ind)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, ind + 1));

	return (ind);
}

/**
 * error_sep_op - finds syntax errors
 *
 * @input: input string
 * @ind: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int error_sep_op(char *input, int ind, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, ind + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (ind);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (ind);

		if (last == '|')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (ind);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (ind);

		if (last == '&')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (ind);
		}
	}

	return (error_sep_op(input + 1, ind + 1, *input));
}

/**
 * first_char - finds index of the first char
 *
 * @input: input string
 * @ind: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *input, int *ind)
{

	for (*ind = 0; input[*ind]; *ind += 1)
	{
		if (input[*ind] == ' ' || input[*ind] == '\t')
			continue;

		if (input[*ind] == ';' || input[*ind] == '|' || input[*ind] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - prints when a syntax error is found
 *
 * @datash: data structure
 * @input: input string
 * @ind: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void print_syntax_error(data_shell *datash, char *input, int ind, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[ind] == ';')
	{
		if (bool == 0)
			msg = (input[ind + 1] == ';' ? ";;" : ";");
		else
			msg = (input[ind - 1] == ';' ? ";;" : ";");
	}

	if (input[ind] == '|')
		msg = (input[ind + 1] == '|' ? "||" : "|");

	if (input[ind] == '&')
		msg = (input[ind + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_syntax_error - intermediate function to
 * find and print a syntax error
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(data_shell *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char(input, &begin);
	if (f_char == -1)
	{
		print_syntax_error(datash, input, begin, 0);
		return (1);
	}

	i = error_sep_op(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		print_syntax_error(datash, input, begin + i, 1);
		return (1);
	}

	return (0);
}
