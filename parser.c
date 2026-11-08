#include "header.h"

int	parse_int(char *str, int *result)
{
	int	i;
	int	n;
	int	digit;

	i = 0;
	n = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		digit = str[i] - '0';
		if (n > (INT_MAX - digit) / 10)
			return (0);
		n = n * 10 + digit;
		i++;
	}
	*result = n;
	return (1);
}

void	init_simulation_state(t_simulation *sim)
{
	sim->next_sequence = 0;
	sim->stopped = 0;
	sim->heap.data = NULL;
	sim->heap.size = 0;
	sim->heap.capacity = 0;
	sim->coders = NULL;
	sim->dongle = NULL;
}

int	parse_args(int argc, char **argv, t_simulation *sim)
{
	if (argc != 9)
		return (0);
	if (!parse_int(argv[1], &sim->number_of_coders)
		|| sim->number_of_coders == 0)
		return (0);
	if (!parse_int(argv[2], &sim->time_to_burnout)
		|| !parse_int(argv[3], &sim->time_to_compile)
		|| !parse_int(argv[4], &sim->time_to_debug)
		|| !parse_int(argv[5], &sim->time_to_refactor))
		return (0);
	if (!parse_int(argv[6], &sim->numbers_of_compiles_required)
		|| !parse_int(argv[7], &sim->dongle_cooldown))
		return (0);
	if (strcmp(argv[8], "edf") == 0)
		sim->scheduler = EDF;
	else if (strcmp(argv[8], "fifo") == 0)
		sim->scheduler = FIFO;
	else
		return (0);
	init_simulation_state(sim);
	return (1);
}
