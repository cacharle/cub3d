#include "cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl("Error");
		return (1);
	}

	t_parsing *p = parse(argv[1]);


	return (0);
}
