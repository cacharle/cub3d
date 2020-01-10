#include "cub3d.h"

void	error_put_usage_exit(char *name)
{
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd(": missing file operand", STDERR_FILENO);
	ft_putstr_fd("Usage: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd(" [.cub file] [--save]", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
