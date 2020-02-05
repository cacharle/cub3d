/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 09:52:34 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/05 00:04:53 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	parse_ceilling_color(t_state *state, char *line)
{
	long	tmp;

	if (state->pflags & PFLAGS_C)
		return (FALSE);
	errno = 0;
	state->ceilling_color.hexcode = 0x0;
	if ((tmp = ft_strtol(line, &line, 10)) > 255 || tmp < 0)
		return (FALSE);
	state->ceilling_color.rgb.r = (t_byte)tmp;
	if (*line++ != ',' || !ft_isdigit(*line))
		return (FALSE);
	if ((tmp = ft_strtol(line, &line, 10)) > 255 || tmp < 0)
		return (FALSE);
	state->ceilling_color.rgb.g = (t_byte)tmp;
	if (*line++ != ',' || !ft_isdigit(*line))
		return (FALSE);
	if ((tmp = ft_strtol(line, &line, 10)) > 255 || tmp < 0)
		return (FALSE);
	state->ceilling_color.rgb.b = (t_byte)tmp;
	if (errno != 0)
		return (FALSE);
	state->pflags |= PFLAGS_C;
	return (TRUE);
}

t_bool	parse_floor_color(t_state *state, char *line)
{
	long	tmp;

	if (state->pflags & PFLAGS_F)
		return (FALSE);
	errno = 0;
	state->floor_color.hexcode = 0x0;
	if ((tmp = ft_strtol(line, &line, 10)) > 255 || tmp < 0)
		return (FALSE);
	state->floor_color.rgb.r = (t_byte)tmp;
	if (*line++ != ',' || !ft_isdigit(*line))
		return (FALSE);
	if ((tmp = ft_strtol(line, &line, 10)) > 255 || tmp < 0)
		return (FALSE);
	state->floor_color.rgb.g = (t_byte)tmp;
	if (*line++ != ',' || !ft_isdigit(*line))
		return (FALSE);
	if ((tmp = ft_strtol(line, &line, 10)) > 255 || tmp < 0)
		return (FALSE);
	state->floor_color.rgb.b = (t_byte)tmp;
	if (errno != 0)
		return (FALSE);
	state->pflags |= PFLAGS_F;
	return (TRUE);
}
