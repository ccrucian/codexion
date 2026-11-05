#include "header.h"

char	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_valid_number(char **argv)
{
    int	i;
	int	j;

	j = 0;
	while (j < 7)
	{
		i = 0;
		if (argv[j][0] == '\0')
			return (0);
		while (argv[j][i])
		{
			if (!is_digit(argv[j][i]))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

void	convert_and_init_simulation(char **argv, t_simulation *sim)
{
	sim->number_of_coders = atoi(argv[1]);
	sim->time_to_burnout = atoi(argv[2]);
	sim->time_to_compile = atoi(argv[3]);
	sim->time_to_debug = atoi(argv[4]);
	sim->time_to_refactor = atoi(argv[5]);
	sim->numbers_of_compiles_required = atoi(argv[6]);
	sim->dongle_cooldown = atoi(argv[7]);
	if (strcmp(argv[8], "edf") == 0)
		sim->scheduler = EDF;
	else
		sim->scheduler = FIFO;
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (argc!= 9)
		return (0);
	if ((!is_valid_number(argv + 1)) ||
			(strcmp(argv[8], "edf") && strcmp(argv[8], "fifo")))
		return (0);
	convert_and_init_simulation(argv, &sim);
	return (0);
}
