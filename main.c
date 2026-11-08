#include "header.h"

int	init_coders(int number, t_coder **coders)
{
	*coders = (t_coder *)malloc(sizeof(t_coder) * number);
	if (!*coders)
		return (0);
	return 1;
}

void    init_coder_fields(t_coder *coders, t_simulation *sim)
{
    int i;

    i = 0;
    while (i < sim->number_of_coders)
    {
        coders[i].id = i + 1;
        coders[i].sim = sim;
        coders[i].last_compile_start = sim->start_time;
        coders[i].compile_count = 0;
        coders[i].have_two_dongles = 0;
        i++;
    }
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
	long long	elapsed;

	usleep(2000);
    coder = (t_coder *)arg;
	elapsed = get_time_in_ms() - coder->sim->start_time;
	printf("%lld coder %d is coding\n", elapsed, coder->id);
    return (NULL);
}

int	create_coders_threads(t_coder *coders, t_simulation *sim)
{
	int i;

	i = 0;
	while (i < sim->number_of_coders)
	{
		if (pthread_create(&coders[i].thread, NULL,
			 &routine, &coders[i]))
		{
			join_coders(coders, i);
			return (1);
		}
        i++;
	}
	return (0);
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

	coders = NULL;
	if (argc != 9)
		return (0);
	if (!parse_args(argc, argv, &sim))
		return (1);
	if (!init_coders(sim.number_of_coders, &coders))
		return (1);
	if (start_simulation_time(&sim))
		return (free(coders), 1);
	init_coder_fields(coders, &sim);
	if (create_coders_threads(coders, &sim))
		return (free(coders), 1);
	join_coders(coders, sim.number_of_coders);
	free(coders);
	return (0);
}
