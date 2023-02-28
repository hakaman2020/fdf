/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_isometric_ops.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/14 15:37:54 by hman          #+#    #+#                 */
/*   Updated: 2021/07/29 15:06:57 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "errors.h"
#include "fdf_structs.h"
#include "fdf_isometric_ops.h"

/*
**	create an empty 2d array of x,y coordinates in float form for the isometric
**	map
*/

void	create_empty_iso_map(t_map_data *map_data)
{
	int				y;

	map_data->isomap = malloc((map_data->rows) * sizeof(t_float_coor *));
	if (map_data->isomap == NULL)
		exit_on_error("Something went wrong with malloc.");
	y = 0;
	while (y < map_data->rows)
	{
		map_data->isomap[y] = malloc(map_data->cols * sizeof (t_float_coor));
		if (map_data->isomap[y] == NULL)
			exit_on_error("Something went wrong with malloc");
		y++;
	}
}

/*
** convert the input map data into a 2d array x,y coordinates according to 
** isometric projection.
*/
void	convert_to_iso_map(t_map_data *map_data)
{
	int			x;
	int			y;

	y = 0;
	while (y < map_data->rows)
	{	
		x = 0;
		while (x < map_data->cols)
		{
			map_data->isomap[y][x] = convert_to_iso_coor(x, y, map_data);
			x++;
		}
		y++;
	}
}

/*
**	this function convert map coordinates into isometric coordinates
**	Return	the x,y coordinates in isometric projection
*/

t_float_coor	convert_to_iso_coor(int x_map, int y_map, t_map_data *map_data)
{
	t_float_coor	iso_coor;
	float			iso_angle_rad;

	iso_angle_rad = (map_data->angle / 180.0f) * M_PI;
	iso_coor.x = ((x_map - y_map) * cos(iso_angle_rad) + map_data->offset.x)
		* map_data->scale + map_data->window_center.x;
	iso_coor.y = ((x_map + y_map) * sin(iso_angle_rad)
			- map_data->map[y_map][x_map] + map_data->offset.y)
		* map_data->scale + map_data->window_center.y;
	return (iso_coor);
}

/*
**	it will add the x,y coordinates to the all the isometric coordinates
**	in the isometric map , thus moving the map
*/

void	translate_iso_map(t_float_coor move, t_map_data *map_data)
{
	int	x;
	int	y;

	y = 0;
	while (y < map_data->rows)
	{
		x = 0;
		while (x < map_data->cols)
		{
			map_data->isomap[y][x].x = map_data->isomap[y][x].x + move.x;
			map_data->isomap[y][x].y = map_data->isomap[y][x].y + move.y;
			x++;
		}
		y++;
	}
}
