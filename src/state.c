/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:39:57 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/30 15:13:42 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Initialize the state attributes that weren't already filled by the parsing
*/

t_state	*state_new(t_state *state)
{
	int	i;

	state->running = TRUE;
	if ((state->mlx_ptr = mlx_init()) == NULL)
		return (state_destroy(state));
	if ((state->window_ptr = mlx_new_window(state->mlx_ptr,
			state->window.width, state->window.height, WINDOW_TITLE)) == NULL)
		return (state_destroy(state));
	printf("init mlx and mlx window\n");
	i = -1;
	while (++i < TEXTURES_NUM)
	{
		load_texture(state->mlx_ptr, &state->textures[i],
				state->textures_path[i]);
		if (state->textures[i].id == NULL)
			return (error_put_return_state_destroy("load texture", state));
	}
	if ((state->window.id = mlx_new_image(state->mlx_ptr,
			state->window.width, state->window.height)) == NULL)
		return (state_destroy(state));
	state->window.data = mlx_get_data_addr(state->window.id,
			&state->window.depth, &state->window.size_line,
			&state->window.endian);
	printf("init mlx window image\n");
	state_init_player(state);
	printf("init player\n");
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
	return (state);
}

void	*state_destroy(t_state *state)
{
	int	i;

	if (state == NULL)
		return (NULL);
	i = -1;
	while (++i < TEXTURES_NUM)
	{
		free(state->textures_path[i]);
		if (state->mlx_ptr != NULL && state->textures[i].id != NULL)
			mlx_destroy_image(state->mlx_ptr, state->textures[i].id);
	}
	printf("free window image\n");
	if (state->mlx_ptr != NULL && state->window.id != NULL)
		mlx_destroy_image(state->mlx_ptr, state->window.id);
	printf("free window\n");
	if (state->mlx_ptr && state->window_ptr)
		mlx_destroy_window(state->mlx_ptr, state->window_ptr);
	printf("free map\n");
	if (state->map != NULL)
		while (state->map_height-- > 0 && state->map[state->map_height] != NULL)
			free(state->map[state->map_height]);
	free(state->map);
	printf("free state\n");
	free(state);
	return (NULL);
}

void	load_texture(void *mlx_ptr, t_image *image, char *path)
{
	if ((image->id = mlx_xpm_file_to_image(
			mlx_ptr, path, &image->width, &image->height)) == NULL)
		return ;
	image->data = mlx_get_data_addr(image->id, &image->depth,
									&image->size_line, &image->endian);
}
