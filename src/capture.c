/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:15:11 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/04 05:32:47 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define CAPTURE_FILENAME "capture.bmp"
#define IMG_DEPTH 3

int		capture(t_state *state)
{
	t_byte	file_header[FILE_HEADER_SIZE];
	t_byte	info_header[INFO_HEADER_SIZE];

	render_update_window(state);
	render_update_sprite(state);
	bmp_fill_header(&state->window, file_header, info_header);
	if (!bmp_write(&state->window, file_header, info_header))
	{
		state_destroy(state);
		return (1);
	}
	state_destroy(state);
	return (0);
}

/*
** bmp file format:
**     header:
**         file_header:
**             2: signature = "BM"
**             4: file size
**             4: reserved
**             4: offset to pixel array
**         info_header:
**	       4: header size
**	       4: image width
**	       4: image height
**	       2: number of color planes
**	       2: bits per pixel
**	       4: compression
**	       4: image size
**	       4: horizontal resolution
**	       4: vertical resolution
**	       4: colors in color table
**	       4: important color count
**     data:
**         pixel in rgb format (without alpha component)
**         padding added at the end of each pixel row
**         so the length of the row is a multiple of 4
*/

t_bool	bmp_write(t_image *image, t_byte file_header[FILE_HEADER_SIZE],
						t_byte info_header[INFO_HEADER_SIZE])
{
	int		fd;
	t_byte	*bmp_data;

	if ((fd = open(CAPTURE_FILENAME, O_WRONLY | O_CREAT, 0644)) < 0)
		return (FALSE);
	if ((bmp_data = malloc(sizeof(unsigned char) *
			(image->width * IMG_DEPTH))) == NULL)
	{
		close(fd);
		return (FALSE);
	}
	write(fd, file_header, FILE_HEADER_SIZE);
	write(fd, info_header, INFO_HEADER_SIZE);
	bmp_write_pixels(fd, image, bmp_data);
	close(fd);
	return (TRUE);
}

void	bmp_write_pixels(int fd, t_image *image, t_byte *bmp_data)
{
	int		i;
	int		j;
	t_byte	padding[3];
	int		padding_size;

	ft_bzero(padding, 3);
	padding_size = (4 - (image->width * IMG_DEPTH) % 4) % 4;
	i = image->height;
	while (--i >= 0)
	{
		j = -1;
		while (++j < image->width)
		{
			bmp_data[3 * j + 0] = image->data[4 * (i * image->width + j) + 0];
			bmp_data[3 * j + 1] = image->data[4 * (i * image->width + j) + 1];
			bmp_data[3 * j + 2] = image->data[4 * (i * image->width + j) + 2];
		}
		write(fd, bmp_data, image->width * 3);
		write(fd, padding, padding_size);
	}
}

void	bmp_fill_header(t_image *image, t_byte file_header[FILE_HEADER_SIZE],
						t_byte info_header[INFO_HEADER_SIZE])
{
	int	file_size;

	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (IMG_DEPTH * image->width
			+ ((4 - (image->width * IMG_DEPTH) % 4) % 4)) * image->height;
	ft_bzero(file_header, FILE_HEADER_SIZE);
	ft_bzero(info_header, INFO_HEADER_SIZE);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
	info_header[0] = (unsigned char)(INFO_HEADER_SIZE);
	info_header[4] = (unsigned char)(image->width);
	info_header[5] = (unsigned char)(image->width >> 8);
	info_header[6] = (unsigned char)(image->width >> 16);
	info_header[7] = (unsigned char)(image->width >> 24);
	info_header[8] = (unsigned char)(image->height);
	info_header[9] = (unsigned char)(image->height >> 8);
	info_header[10] = (unsigned char)(image->height >> 16);
	info_header[11] = (unsigned char)(image->height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(IMG_DEPTH * 8);
}
