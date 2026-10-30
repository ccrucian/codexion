#include "header.h"

void	free_argv_mem(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL || *argv == NULL)
		return ;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

void	free_and_exit(char **argv)
{
	free_argv_mem(argv);
	write(FD_STDERR, "Error\n", 6);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	if (argc == 1 || (argc == 2 && !argv[1]))
		return EXIT_FAILURE;
	argv = split_arguments(argv[1], argc - 1);
	if (!argv)
		free_and_exit(argv);

}
