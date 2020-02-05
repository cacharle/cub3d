/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:39:57 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/05 01:49:22 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Initialize the state attributes that weren't already filled by the parsing
*/

t_state	*state_new(t_state *state)
{
	if (state == NULL)
		return (NULL);
	state->running = TRUE;
	if ((state->mlx_ptr = mlx_init()) == NULL)
		return (state_destroy(state));
	if ((state->window_ptr = mlx_new_window(state->mlx_ptr,
			state->window.width, state->window.height, WINDOW_TITLE)) == NULL)
		return (state_destroy(state));
	if (!state_init_textures(state))
		return (error_put_return_state_destroy("load texture", state));
	if ((state->window.id = mlx_new_image(state->mlx_ptr,
			state->window.width, state->window.height)) == NULL)
		return (state_destroy(state));
	state->window.data = mlx_get_data_addr(state->window.id,
			&state->window.depth, &state->window.size_line,
			&state->window.endian);
	state_init_player(state);
	if ((state->z_buffer = malloc(sizeof(double)
					* state->window.width)) == NULL)
		return (error_put_return_state_destroy("create z buffer", state));
	if (!state_init_sprites(state))
		return (error_put_return_state_destroy("create sprites pos", state));
	return (state);
}

void	state_init_player(t_state *state)
{
	int	i;
	int j;

	i = -1;
	while (++i < state->map_height)
	{
		j = -1;
		while (++j < state->map_width)
			if (helper_is_player_cell(state->map[i][j]))
			{
				state->pos.x = (double)j + 0.5;
				state->pos.y = (double)i + 0.5;
			}
	}
	helper_init_dir_plane(state, (int)state->pos.y, (int)state->pos.x);
}

t_state	*state_new_empty(void)
{
	int		i;
	t_state	*state;

	if ((state = (t_state*)malloc(sizeof(t_state))) == NULL)
		return (NULL);
	state->mlx_ptr = NULL;
	state->window_ptr = NULL;
	state->window.id = NULL;
	i = -1;
	while (++i < TEXTURES_NUM)
	{
		state->textures_path[i] = NULL;
		state->textures[i].id = NULL;
	}
	state->dir.x = 0.0;
	state->dir.y = 0.0;
	state->map = NULL;
	state->ceilling_color.hexcode = 0x0;
	state->floor_color.hexcode = 0x0;
	state->z_buffer = NULL;
	state->sprites = NULL;
	state->pflags = 0x0;
	return (state);
}

void	*state_destroy(t_state *state)
{
	int	i;

	if (state == NULL)
		return (NULL);
	i = -1;
	free(state->z_buffer);
	free(state->sprites);
	while (++i < TEXTURES_NUM)
	{
		free(state->textures_path[i]);
		if (state->mlx_ptr != NULL && state->textures[i].id != NULL)
			mlx_destroy_image(state->mlx_ptr, state->textures[i].id);
	}
	if (state->mlx_ptr != NULL && state->window.id != NULL)
		mlx_destroy_image(state->mlx_ptr, state->window.id);
	if (state->mlx_ptr && state->window_ptr)
		mlx_destroy_window(state->mlx_ptr, state->window_ptr);
	if (state->map != NULL)
		while (state->map_height-- > 0 && state->map[state->map_height] != NULL)
			free(state->map[state->map_height]);
	free(state->map);
	free(state);
	return (NULL);
}

t_bool	state_init_textures(t_state *state)
{
	int		i;
	t_image	*tex;

	i = -1;
	while (++i < TEXTURES_NUM)
	{
		tex = &state->textures[i];
		if ((tex->id = mlx_xpm_file_to_image(state->mlx_ptr,
				state->textures_path[i], &tex->width, &tex->height))
				== NULL)
			return (FALSE);
		tex->data = mlx_get_data_addr(tex->id, &tex->depth,
										&tex->size_line, &tex->endian);
		if (tex->id == NULL)
			return (FALSE);
	}
	return (TRUE);
}
