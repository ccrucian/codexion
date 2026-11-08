#include "header.h"

int	init_coders(int number, t_coder **coders)
{
	*coders = (t_coder *)malloc(sizeof(t_coder) * number);
	if (!*coders)
		return (0);
	return 1;
}

void	join_coders(t_coder *coders, int number_of_coders)
{
	int	i;
	
	i = 0;
	while (i < number_of_coders)
	{
		pthread_join(coders[i].thread, NULL);
		i++;
	}
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

/* Convert seconds and microseconds in ms */
long long    get_time_in_ms(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) != 0)
		return(-1);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	start_simulation_time(t_simulation *sim)
{
	sim->start_time = get_time_in_ms();

	if (sim->start_time == -1)
	{
		printf("Start time simulation error");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;
	t_coder *coders;
	long t;

	coders = NULL;
	if (argc != 9)
		return (0);
	if (!parse_args(argc, argv, &sim))
		return (1);
	if (!init_coders(sim.number_of_coders, &coders))
		return (1);
	if (start_simulation_time(&sim))
		return (free(coders), 0);
	create_coders_threads(coders, &sim);
	join_coders(coders, sim.number_of_coders);
	free(coders);

	t = get_time_in_ms() - sim.start_time;
	printf("%ld\n", t);
	sleep(2);
	t = get_time_in_ms() - sim.start_time;
	printf("%ld\n", t);

	return (0);
}
