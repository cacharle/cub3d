/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:15:11 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/11 13:32:54 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		capture(t_state *state)
{
	render_update_window(state);
	write_bmp(&state->window);
	return (0);
}

void	write_bmp(t_image *image)
{

}
