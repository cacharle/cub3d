/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 06:40:37 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/18 02:43:17 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_TITLE "cub3D"
# define MLXK_ESC 53
# define MLXK_W 13
# define MLXK_A 0
# define MLXK_S 1
# define MLXK_D 2
# define MLXK_LEFT 123
# define MLXK_RIGHT 124

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

# define TRUE 1
# define FALSE 0

# define SQUARE(x) ((x) * (x))

typedef int	t_bool;

typedef struct
{
	double	x;
	double	y;
}			t_vector;

typedef struct
{
	int		hexcode;
	struct
	{
		t_byte b;
		t_byte g;
		t_byte r;
		t_byte empty;
	}	rgb;	
}		t_color;

typedef enum
{
	CELL_EMPTY,
	CELL_WALL,
	CELL_ITEM,
	CELL_LOOK_NORTH,
	CELL_LOOK_SOUTH,
	CELL_LOOK_WEST,
	CELL_LOOK_EAST
}	t_cell;

typedef t_cell** t_map;

typedef struct
{
	int		resolution_height;
	int		resolution_width;
	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;
	char	*sprite_texture_path;
	t_color	floor_color;
	t_color	ceilling_color;
	t_map	map;
	int		map_width;
	int		map_height;
}			t_parsing;

typedef struct	s_state
{
	t_bool		running;
	void		*mlx_ptr;
	void		*window_ptr;
	int			window_width;
	int			window_height;
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_map		map;
	int			map_width;
	int			map_height;
	t_color		ceilling_color;
	t_color		floor_color;
}				t_state;

typedef t_bool	(*t_option_parser_func)(t_parsing *parsing, char *line);

typedef struct				s_option_parser
{
	char					*id;
	t_option_parser_func	func;
}							t_option_parser;

/*
** parse.c
*/

t_parsing	*parse(char *filename);
char		**get_file_lines(char *filename);
t_bool		parse_line(t_parsing *parsing, char *line);
t_parsing	*parse_map(t_parsing *parsing, char **lines);
t_cell		*create_map_row(char *line);

/*
** parse_*.c
*/

t_bool parse_resolution(t_parsing *parsing, char *line);
t_bool parse_north_texture(t_parsing *parsing, char *line);
t_bool parse_south_texture(t_parsing *parsing, char *line);
t_bool parse_west_texture(t_parsing *parsing, char *line);
t_bool parse_east_texture(t_parsing *parsing, char *line);
t_bool parse_sprite_texture(t_parsing *parsing, char *line);
t_bool parse_floor_color(t_parsing *parsing, char *line);
t_bool parse_ceilling_color(t_parsing *parsing, char *line);

/*
** event.c
*/

int			handle_key(int key, void *param);

/*
** graphics.c
*/

t_state		*create_state(void *mlx_ptr, void *window_ptr, t_parsing *parsing);
int graphics_update(void *param);
void draw_column(t_state *state, int x);
t_vector vector_add(t_vector a, t_vector b);
t_vector vector_scale(t_vector v, double scalar);

/*
** render.c
*/


/*
** linear_algebra.c
*/

t_vector vector_add(t_vector a, t_vector b);
t_vector vector_scale(t_vector v, double scalar);
t_vector vector_rotate(t_vector v, double angle);

#endif
