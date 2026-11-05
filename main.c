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

void	*routine(void *arg)
{
    t_coder *coder;

    coder = (t_coder *)arg;
	printf("Coder %d is coding\n", coder->id);
    return (NULL);
}

void	create_coders_threads(t_coder *coders, t_simulation *sim)
{
	int n;
	int i;

	n = sim->number_of_coders;
	i = 0;
	while (i < n)
	{
        coders[i].id = i + 1;
		pthread_create(&coders[i].thread, NULL, &routine, &coders[i]);
        i++;
	}
}

int	main(int argc, char **argv)
{
	t_simulation	sim;
	t_coder coders[atoi(argv[1])];
	struct timeval current;
	struct timeval start;
	long t;

	if (argc != 9)
		return (0);
	if ((!is_valid_number(argv + 1)) ||
		    (strcmp(argv[8], "edf") && strcmp(argv[8], "fifo")))
		return (0);
	convert_and_init_simulation(argv, &sim);
	create_coders_threads(coders, &sim);
	gettimeofday(&start, NULL);
	usleep(200);
	gettimeofday(&current, NULL);
	t = (current.tv_sec - start.tv_sec) * 1000;
	printf("%ld\n", t);
	return (0);
}
