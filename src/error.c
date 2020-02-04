/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:33:14 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/04 02:17:53 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	error_put(char *message)
{
	ft_putstr("Error\nCouldnt ");
	ft_putendl(message);
}

void	*error_put_return(char *message)
{
	error_put(message);
	return (NULL);
}

void	*error_put_return_state_destroy(char *message, t_state *state)
{
	state_destroy(state);
	return (error_put_return(message));
}

void	*error_put_return_lines_state_destroy(
			char *message, t_state *state, char **lines)
{
	helper_free_splited(lines);
	return (error_put_return_state_destroy(message, state));
}
