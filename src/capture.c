/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:15:11 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/02 08:33:14 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define BM_FILE_TYPE 19778
#define DATA_OFFSET 1078
#define BITMAP_INFO_HEADER_SIZE 40
#define CAPTURE_FILENAME "capture.bmp"

int		capture(t_state *state)
{
	t_bmp_header	header;

	render_update_window(state, CELL_WALL);
	bmp_fill_header(&state->window, &header);
	if (!bmp_write(&state->window, &header))
	{
		state_destroy(state);
		return (1);
	}
	return (0);
}

t_bool	bmp_write(t_image *image, t_bmp_header *header)
{
	int	fd;

	if ((fd = open(CAPTURE_FILENAME, O_WRONLY | O_CREAT)) < 0)
		return (FALSE);
	printf("%d\n", fd);
	write(fd, &header, sizeof(t_bmp_header));
	write(fd, image->data, image->width * image->height * 4);
	close(fd);
	return (TRUE);
}

void	bmp_fill_header(t_image *image, t_bmp_header *header)
{
	header->file_header.file_type = BM_FILE_TYPE;
	header->file_header.file_size = sizeof(t_bmp_header) + image->width * image->height * 4;
	header->file_header.reserved1 = 0;
	header->file_header.reserved1 = 0;
	header->file_header.offset = DATA_OFFSET;
	header->info_header.size = sizeof(t_bmp_header) + image->width * image->height * 4;
	header->info_header.width = image->width;
	header->info_header.height = image->height;
	header->info_header.planes = 0;
	header->info_header.depth = 8 * 4;
	header->info_header.compression = 0;
	header->info_header.size_image = 0;
	header->info_header.w_pix_per_meter = 0;
	header->info_header.h_pix_per_meter = 0;
	header->info_header.color_used = 0;
	header->info_header.color_important = 0;
	header->color_table.blue = 0xff;
	header->color_table.green = 0xff;
	header->color_table.red = 0xff;
	header->color_table.reserved = 0;
}
