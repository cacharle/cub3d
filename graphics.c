#include "cub3d.h"

t_state		*create_state(t_parsing *parsing)
{
	t_state *state;

	if ((state = (t_state*)malloc(sizeof(t_state))) == NULL)
		return (NULL);
	state->running = TRUE;
	state->pos.x = 8.0;
	state->pos.y = 8.0;
	state->dir.x = -1.0;
	state->dir.y = 0.0;
	state->plane.x = 0.0;
	state->plane.y = 0.66;
	state->map = parsing->map;
	return (state);
}

void update(t_state *state)
{


}

void draw_column(int x)
{


}
