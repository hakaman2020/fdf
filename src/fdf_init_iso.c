/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_init_iso.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/29 16:34:45 by hman          #+#    #+#                 */
/*   Updated: 2021/08/02 17:18:19 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_init_iso.h"
#include "fdf_isometric_ops.h"

//initial values for the map data
#define DEFAULT_SCALE		10
#define DEFAULT_OFFSET_X	0
#define DEFAULT_OFFSET_Y	0
#define DEFAULT_ANGLE		30

/*
**	this calculate the center of the isometric map and set the offset
**	accordingly
*/

void	set_initial_map_info(t_map_data *map_data, unsigned int window_width,
		unsigned int window_height)
{
	t_max_min	max_min_isomap;

	create_empty_iso_map(map_data);
	map_data->scale = DEFAULT_SCALE;
	map_data->offset.x = DEFAULT_OFFSET_X;
	map_data->offset.y = DEFAULT_OFFSET_Y;
	map_data->angle = DEFAULT_ANGLE;
	map_data->window_height = window_height;
	map_data->window_width = window_width;
	map_data->window_center.x = window_width / 2;
	map_data->window_center.y = window_height / 2;
	convert_to_iso_map(map_data);
	find_max_min_isomap(map_data, &max_min_isomap);
	set_center_isomap(map_data, &max_min_isomap);
	resize_isomap(map_data, &max_min_isomap);
	convert_to_iso_map(map_data);
}

void	set_center_isomap(t_map_data *map_data, t_max_min *max_min_isomap)
{
	float			width_isomap;
	float			height_isomap;

	width_isomap = max_min_isomap->max_x - max_min_isomap->min_x;
	height_isomap = max_min_isomap->max_y - max_min_isomap->min_y;
	map_data->offset.x = -(max_min_isomap->max_x - width_isomap / 2
			- map_data->window_center.x) / map_data->scale;
	map_data->offset.y = -(max_min_isomap->max_y - height_isomap / 2
			- map_data->window_center.y) / map_data->scale;
}

void	find_max_min_isomap(t_map_data *map_data, t_max_min *max_min_isomap)
{
	int	x;
	int	y;

	max_min_isomap->max_x = map_data->isomap[0][map_data->cols - 1].x;
	max_min_isomap->min_x = map_data->isomap[map_data->rows - 1][0].x;
	max_min_isomap->max_y = map_data->isomap[0][0].y;
	max_min_isomap->min_y = map_data->isomap[0][0].y;
	y = 0;
	while (y < map_data->rows)
	{
		x = 0;
		while (x < map_data->cols)
		{
			if (map_data->isomap[y][x].y > max_min_isomap->max_y)
				max_min_isomap->max_y = map_data->isomap[y][x].y;
			if (map_data->isomap[y][x].y < max_min_isomap->min_y)
				max_min_isomap->min_y = map_data->isomap[y][x].y;
			x++;
		}
		y++;
	}
}

/*
**	this function will adjust the scale if the current isomap is
**	too big for the screen.
**	RETURN	0 if the scale has not been changed
**			1 if the scale has been changed
*/

int	resize_isomap(t_map_data *map_data, t_max_min *max_min_isomap)
{
	float	width_isomap;
	float	height_isomap;
	float	scale_x;
	float	scale_y;

	width_isomap = max_min_isomap->max_x - max_min_isomap->min_x;
	height_isomap = max_min_isomap->max_y - max_min_isomap->min_y;
	if (width_isomap > map_data->window_width
		|| height_isomap > map_data->window_height)
	{
		scale_x = map_data->scale * (map_data->window_width / width_isomap);
		scale_y = map_data->scale * (map_data->window_height / height_isomap);
		if (scale_x > scale_y)
			map_data->scale = scale_y;
		else
			map_data->scale = scale_x;
		return (1);
	}
	return (0);
}
