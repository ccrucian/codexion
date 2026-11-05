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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
	if (ft_strcmp(argv[8], "edf") == 0)
		sim->scheduler = EDF;
	else
		sim->scheduler = FIFO;
	printf("%d\n", sim->number_of_coders);
	printf("%d\n", sim->scheduler);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (argc!= 9)
		return (0);
	if ((!is_valid_number(argv + 1)) ||
			(ft_strcmp(argv[8], "edf") && ft_strcmp(argv[8], "fifo")))
	{
		printf("IN");
		return (0);
	}
	convert_and_init_simulation(argv, &sim);
	printf("ok00");
	printf("%d\n", sim.number_of_coders);
	printf("%d\n", sim.scheduler);
	return (0);
}
