#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include "libft.h"

# define TRUE 1
# define FALSE 0

typedef int t_bool;

typedef struct
{
	int x;
	int y;
}		t_point;

typedef struct
{
	int r;
	int g;
	int b;
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
	int resolution_height;
	int resolution_width;
	char *north_texture_path;
	char *south_texture_path;
	char *west_texture_path;
	char *east_texture_path;
	char *sprite_texture_path;
	t_color floor_color;
	t_color ceilling_color;
	t_map map;
}		t_parsing;

typedef t_bool (*func)(t_parsing *parsing, char *line) t_line_parser_func;

typedef struct
{
	char *id;
	t_line_parser_func func;
}		t_line_parser;

/*
** parse.c
*/

t_parsing *parse(char *filename);
t_bool parse_line(t_parsing *parsing, char *line);

#endif
