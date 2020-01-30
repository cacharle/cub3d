/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:29:27 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/11 09:44:18 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	parse_resolution(t_state *state, char *line)
{
	if ((state->window.width = ft_atoi(line)) < 0)
		return (FALSE);
	if ((line = ft_strrchr(line, ' ') + 1) == NULL)
		return (FALSE);
	if ((state->window.height = ft_atoi(line)) < 0)
		return (FALSE);
	return (TRUE);
}
