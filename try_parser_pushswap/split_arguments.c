#include "header.h"

int	count_arguments(char *argv)
{
	int	count;
	int	i;
	int	arg_detected;

	i = 0;
	count = 0;
	while (argv[i])
	{
		arg_detected = 0;
		while (argv[i] == ' ' && argv[i])
			i++;
		while (argv[i] != ' ' && argv[i])
		{
			if (!arg_detected)
			{
				arg_detected = 1;
				count++;
			}
			i++;
		}
	}
	return (count);

}

int	find_arguments(char **argv, int argc)
{
	int	args_count;
	int	j;

	args_count = 0;
	j = 0;
	while (j < argc)
	{
		if (argv[j][0] == '\0')
			free_and_exit(NULL);
		args_count += count_arguments(argv[j]);
		j++;
	}
	return (args_count);
}

char	*next_word(char *str)
{
	static int	chr = 0;
	char		*next_word;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (str[chr] == ' ')
		chr++;
	while ((str[chr + len] != ' ') && str[chr + len])
		len++;
	next_word = (char *)malloc(sizeof(char) * (len + 1));
	if (!next_word)
		return (NULL);
	while ((str[chr] != ' ') && str[chr])
		next_word[i++] = str[chr++];
	next_word[i] = '\0';
	if (i == 0)
		chr = 0;
	return (next_word);
}

char	**fill_output(char **output, char **argv, int args_count)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (i < args_count)
	{
		output[i] = next_word(argv[j]);
		if (!output)
			return (cleanup_output(output, i);

	}

	return (output);
}

char	**split_arguments(char **argv, int argc)
{
	char	**output;
	int	args_count;

	args_count = find_arguments(argv, argc);
	if (!args_count || args_count != 8)
		exit(EXIT_FAILURE);
	output = malloc(sizeof(char *) * (args_count + 1));
	if (!output)
		return (NULL);
	output = fill_output(output, argv, args_count);

	return (output);
}
