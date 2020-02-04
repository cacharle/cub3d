/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:29:27 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/04 04:40:35 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MIN_RES 20
#define MAX_RES_HEIGHT 2160
#define MAX_RES_WIDTH 3840

t_bool	parse_resolution(t_state *state, char *line)
{
	long	tmp;

	errno = 0;
	if ((tmp = ft_strtol(line, &line, 10)) < MIN_RES)
		return (FALSE);
	if (tmp > MAX_RES_WIDTH)
		return (FALSE);
	state->window.width = tmp;
	if (*line != ' ')
		return (FALSE);
	while (*line == ' ')
		line++;
	if ((tmp = ft_strtol(line, &line, 10)) < MIN_RES)
		return (FALSE);
	if (tmp > MAX_RES_HEIGHT)
		return (FALSE);
	state->window.height = tmp;
	if (*line != '\0' || errno != 0 || state->window.height > 2160)
		return (FALSE);
	return (TRUE);
}
