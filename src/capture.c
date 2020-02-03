/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:15:11 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/03 02:25:43 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define BM_FILE_TYPE 19778
#define DATA_OFFSET 1078
#define BITMAP_INFO_HEADER_SIZE 0x424d
#define CAPTURE_FILENAME "capture.bmp"

int		capture(t_state *state)
{
	t_bmp_header	header;

	render_update_window(state);
	bmp_fill_header(&state->window, &header);
	if (!bmp_write(&state->window, &header))
	{
		state_destroy(state);
		return (1);
	}
	return (0);
}

unsigned char* createBitmapFileHeader(int height, int width, int paddingSize){
	int fileSize = 14 + 40 + (3*width+paddingSize) * height;

	static unsigned char fileHeader[] = {
		0,0, /// signature
		0,0,0,0, /// image file size in bytes
		0,0,0,0, /// reserved
		0,0,0,0, /// start of pixel array
	};

	fileHeader[ 0] = (unsigned char)('B');
	fileHeader[ 1] = (unsigned char)('M');
	fileHeader[ 2] = (unsigned char)(fileSize    );
	fileHeader[ 3] = (unsigned char)(fileSize>> 8);
	fileHeader[ 4] = (unsigned char)(fileSize>>16);
	fileHeader[ 5] = (unsigned char)(fileSize>>24);
	fileHeader[10] = (unsigned char)(14 + 40);

	return fileHeader;
}

unsigned char* createBitmapInfoHeader(int height, int width){
	static unsigned char infoHeader[] = {
		0,0,0,0, /// header size
		0,0,0,0, /// image width
		0,0,0,0, /// image height
		0,0, /// number of color planes
		0,0, /// bits per pixel
		0,0,0,0, /// compression
		0,0,0,0, /// image size
		0,0,0,0, /// horizontal resolution
		0,0,0,0, /// vertical resolution
		0,0,0,0, /// colors in color table
		0,0,0,0, /// important color count
	};

	infoHeader[ 0] = (unsigned char)(40);
	infoHeader[ 4] = (unsigned char)(width    );
	infoHeader[ 5] = (unsigned char)(width>> 8);
	infoHeader[ 6] = (unsigned char)(width>>16);
	infoHeader[ 7] = (unsigned char)(width>>24);
	infoHeader[ 8] = (unsigned char)(height    );
	infoHeader[ 9] = (unsigned char)(height>> 8);
	infoHeader[10] = (unsigned char)(height>>16);
	infoHeader[11] = (unsigned char)(height>>24);
	infoHeader[12] = (unsigned char)(1);
	infoHeader[14] = (unsigned char)(3*8);

	return infoHeader;
}

t_bool	bmp_write(t_image *image, t_bmp_header *header)
{
	int	fd;

	unsigned char padding[3] = {0, 0, 0};
	int paddingSize = (4 - (image->width*3) % 4) % 4; //redundant?
	unsigned char* fileHeader = createBitmapFileHeader(image->height, image->width, paddingSize);
	unsigned char* infoHeader = createBitmapInfoHeader(image->height, image->width);

	if ((fd = open(CAPTURE_FILENAME, O_WRONLY | O_CREAT, S_IRWXU)) < 0)
		return (FALSE);

	write(fd, fileHeader, 14);
	write(fd, infoHeader, 40);
	/* write(fd, &header, sizeof(t_bmp_header)); */
	for (int i = 0; i < image->width; i++)
	{
		for (int j = 0; j < image->height; j++)
		{
			write(fd, &image->data[4 * (i * image->width + j)], 3);
		}
		write(fd, padding, paddingSize);
	}
	/* write(fd, image->data, image->width * image->height * 4); */
	close(fd);
	return (TRUE);
}

void	bmp_fill_header(t_image *image, t_bmp_header *header)
{
	header->file_header.file_type = BM_FILE_TYPE;
	header->file_header.file_size = sizeof(t_bmp_header) + image->width * image->height * 3;
	header->file_header.reserved1 = 0;
	header->file_header.reserved1 = 0;
	header->file_header.offset = sizeof(t_bmp_header);

	header->info_header.size = sizeof(header->info_header);
	header->info_header.width = image->width;
	header->info_header.height = image->height;
	header->info_header.planes = 0;
	header->info_header.depth = 8 * 3;
	header->info_header.compression = 0;
	header->info_header.size_image = image->width * image->height * 3;
	header->info_header.w_pix_per_meter = 0;
	header->info_header.h_pix_per_meter = 0;
	header->info_header.color_used = 0;
	header->info_header.color_important = 0;

	/* header->color_table.blue = 0xff; */
	/* header->color_table.green = 0xff; */
	/* header->color_table.red = 0xff; */
	/* header->color_table.reserved = 0; */
}
