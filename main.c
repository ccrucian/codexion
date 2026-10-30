#include "header.h"

int	is_valid_shceduler(char *argv)
{
	char	*s1;
	char	*s2;
	int	i;
	int	j;
	
	s1 = "efd";
	s2 = "fifo";
	i = 0;
	j = 0;


}

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
		sim->time_toburno
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (argc!= 9)
		return (0);
	if (!is_valid_number(argv + 1) ||
		(strcmp(argv[8], "edf") && str_cmp(argv[8], "fifo"));
		return (0);
	convert_and_init_simulation(argv + 1, &sim);
}
