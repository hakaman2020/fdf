/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_image_ops.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/02 15:32:29 by hman          #+#    #+#                 */
/*   Updated: 2021/08/02 15:58:23 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf_image_ops.h"
#include "fdf_bres_algo.h"

#define COLOR_BLACK 0x00000000

void	draw_pixel(t_img *img, int x, int y, unsigned int colour)
{
	char	*dst;
	int		offset;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		offset = y * img->line_size + x * (img->bits_per_pixel / 8);
		dst = img->address + offset;
		*(unsigned int *)dst = colour;
	}
}

void	draw_iso_map(t_map_data *map_data, t_img *img)
{
	draw_horizontal_lines(map_data, img);
	draw_vertical_lines(map_data, img);
}

void	draw_horizontal_lines(t_map_data *map_data, t_img *img)
{
	int		x;
	int		y;
	t_coor	point1;
	t_coor	point2;

	y = 0;
	while (y < map_data->rows)
	{
		x = 1;
		while (x < map_data->cols)
		{
			point1.x = (int) round(map_data->isomap[y][x - 1].x);
			point1.y = (int) round(map_data->isomap[y][x - 1].y);
			point2.x = (int) round(map_data->isomap[y][x].x);
			point2.y = (int) round(map_data->isomap[y][x].y);
			draw_line(point1, point2, img);
			x++;
		}
		y++;
	}
}

void	draw_vertical_lines(t_map_data *map_data, t_img *img)
{
	int		x;
	int		y;
	t_coor	point1;
	t_coor	point2;

	x = 0;
	while (x < map_data->cols)
	{
		y = 1;
		while (y < map_data->rows)
		{
			point1.x = (int) round(map_data->isomap[y - 1][x].x);
			point1.y = (int) round(map_data->isomap[y - 1][x].y);
			point2.x = (int) round(map_data->isomap[y][x].x);
			point2.y = (int) round(map_data->isomap[y][x].y);
			draw_line(point1, point2, img);
			y++;
		}
		x++;
	}
}

void	clear_image(t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			draw_pixel(img, x, y, COLOR_BLACK);
			x++;
		}
		y++;
	}
}
