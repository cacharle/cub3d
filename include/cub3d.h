/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 06:40:37 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/03 01:43:17 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

# define CUB3D_BUFFER_SIZE 64

# define WINDOW_TITLE "cub3D"
# define MLXK_ESC 53
# define MLXK_W 13
# define MLXK_A 0
# define MLXK_S 1
# define MLXK_D 2
# define MLXK_LEFT 123
# define MLXK_RIGHT 124

# define MLX_LITTLE_ENDIAN 0
# define MLX_BIG_ENDIAN 1

# define TRUE 1
# define FALSE 0

typedef int	t_bool;

typedef struct
{
	double	x;
	double	y;
}			t_vector;

typedef union
{
	unsigned int	hexcode;
	struct
	{
		t_byte		b;
		t_byte		g;
		t_byte		r;
		t_byte		alpha;
	}				rgb;
}					t_color;

typedef enum
{
	CELL_EMPTY = 0,
	CELL_WALL = 1,
	CELL_ITEM = 2,
	CELL_LOOK_NORTH,
	CELL_LOOK_SOUTH,
	CELL_LOOK_WEST,
	CELL_LOOK_EAST
}	t_cell;

typedef t_cell** t_map;

enum
{
	TEX_NORTH,
	TEX_SOUTH,
	TEX_WEST,
	TEX_EAST,
	TEX_SPRITE
};

# define TEXTURES_NUM (TEX_SPRITE - TEX_NORTH + 1)

typedef struct
{
	int		width;
	int		height;
	void	*id;
	char	*data;
	int		depth;
	int		size_line;
	int		endian;
}			t_image;

typedef struct
{
	t_vector	pos;
	double		dist;
}				t_sprite;

typedef struct	s_state
{
	t_bool		running;
	void		*mlx_ptr;
	void		*window_ptr;
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_map		map;
	int			map_width;
	int			map_height;
	t_color		ceilling_color;
	t_color		floor_color;
	t_image		window;
	char		*textures_path[TEXTURES_NUM];
	t_image		textures[TEXTURES_NUM];
	double		*z_buffer;
	int			sprites_num;
	t_sprite	*sprites;
}				t_state;

typedef enum
{
	SIDE_NS,
	SIDE_WE
}	t_side;

typedef struct	s_render_state
{
	int			x;
	t_vector	ray;
	t_vector	map_pos;
	t_vector	delta;
	t_side		side;
	double		perp_dist;
	int			line_height;
	t_vector	probe;
	t_vector	map_step;
	int			draw_start;
	int			draw_end;
	t_cell		target;
}				t_render_state;

typedef t_bool	(*t_option_parser_func)(t_state *state, char *line);

typedef struct				s_option_parser
{
	char					*id;
	t_option_parser_func	func;
}							t_option_parser;

typedef unsigned int	t_byte4;
typedef unsigned short	t_byte2;
typedef unsigned char	t_byte1;

typedef struct
{
	struct
	{
		t_byte2	file_type;
		t_byte4	file_size;
		t_byte2	reserved1;
		t_byte2	reserved2;
		t_byte4	offset;
	}			file_header;
	struct
	{
		t_byte4	size;
		t_byte4	width;
		t_byte4	height;
		t_byte2	planes;
		t_byte2	depth;
		t_byte4	compression;
		t_byte4	size_image;
		t_byte4	w_pix_per_meter;
		t_byte4	h_pix_per_meter;
		t_byte4	color_used;
		t_byte4	color_important;
	}			info_header;
	// struct
	// {
	// 	t_byte1	blue;
	// 	t_byte1	green;
	// 	t_byte1	red;
	// 	t_byte1	reserved;
	// }			color_table;
}	t_bmp_header;

/*
** parse/parse.c
*/

t_state		*parse(char *filename);
char		**get_file_lines(char *filename);
t_bool		parse_line(t_state *state, char *line);
t_state		*parse_map(t_state *state, char **lines);
t_cell		*create_map_row(char *line);

/*
** parse/parse_check.c
*/

t_state		*parse_check(t_state *state);

/*
** parse/parse_resolution.c
*/

t_bool		parse_resolution(t_state *state, char *line);

/*
** parse/parse_textures.c
*/

t_bool		parse_north_texture(t_state *state, char *line);
t_bool		parse_south_texture(t_state *state, char *line);
t_bool		parse_west_texture(t_state *state, char *line);
t_bool		parse_east_texture(t_state *state, char *line);
t_bool		parse_sprite_texture(t_state *state, char *line);

/*
** parse/parse_color.c
*/

t_bool		parse_floor_color(t_state *state, char *line);
t_bool		parse_ceilling_color(t_state *state, char *line);

/*
** event.c
*/

int			event_keydown(int key, t_state *state);
int			event_quit(t_state *state);

/*
** state.c
*/

t_state		*state_new(t_state *state);
void		state_init_player(t_state *state);
t_state		*state_new_empty(void);
void		*state_destroy(t_state *state);
void		load_texture(void *mlx_ptr, t_image *image, char *path);

/*
** render.c
*/

int			render_update(void *param);
void		render_update_window(t_state *state);
void		render_column(t_state *state, int x);
void		render_window_column(t_state *state, t_render_state *rstate);
void		render_texture(t_state *state, t_render_state *rstate, int *i);

/*
** vector.c
*/

t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_sub(t_vector a, t_vector b);
t_vector	vector_scale(t_vector v, double scalar);
t_vector	vector_rotate(t_vector v, double angle);
double		vector_norm(t_vector v);
t_vector	vector_new(double x, double y);
t_vector	vector_apply(t_vector v, double (*f)(double));

/*
** error.c
*/

void		error_put_usage_exit(char *name);
void		error_put(char *message);
void		*error_put_return(char *message);
void		*error_put_return_state_destroy(char *message, t_state *state);
void		*error_put_return_lines_state_destroy(
				char *message, t_state *state, char **lines);

/*
** helper.c
*/

t_bool		helper_is_player_cell(t_cell cell);
void		helper_free_splited(char **splited);
void		helper_rotate_player(t_state *state, double rotation);
void		helper_init_dir_plane(t_state *state, int y, int x);
t_bool		state_init_sprites(t_state *state);

/*
** render_state.c
*/

void		rstate_ray(t_state *state, t_render_state *rstate);
void		rstate_delta(t_render_state *rstate);
void		rstate_init_probe(t_state *state, t_render_state *rstate);
void		rstate_perp_dist(t_state *state, t_render_state *rstate);
void		rstate_line_height(t_state *state, t_render_state *rstate);
void		rstate_next_probe(t_render_state *rstate);

/*
** texture.c
*/

t_image		*texture_select(t_state *state, t_render_state *rstate);
int			texture_x(t_state *state, t_render_state *rstate, t_image *texture);

/*
** capture.c
*/

int			capture(t_state *state);
t_bool		bmp_write(t_image *image, t_bmp_header *header);
void		bmp_fill_header(t_image *image, t_bmp_header *header);

/*
** render_sprite.c
*/

void	render_update_sprite(t_state *state);


#endif
