/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_key_press.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/01 17:10:42 by hman          #+#    #+#                 */
/*   Updated: 2021/08/05 12:49:05 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/mlx_linux/mlx.h"
#include "fdf_image_ops.h"
#include "fdf_isometric_ops.h"
#include "fdf.h"
#include "fdf_key_press.h"

int	pressed_key(int keycode, t_all_data *all_data)
{
	if (keycode == KEY_CODE_UP)
		move_iso_map(0, -10, all_data);
	else if (keycode == KEY_CODE_DOWN)
		move_iso_map(0, 10, all_data);
	else if (keycode == KEY_CODE_LEFT)
		move_iso_map(-10, 0, all_data);
	else if (keycode == KEY_CODE_RIGHT)
		move_iso_map(10, 0, all_data);
	else if (keycode == KEY_CODE_Z)
		change_scale(INCREASE, all_data);
	else if (keycode == KEY_CODE_X)
		change_scale(DECREASE, all_data);
	else if (keycode == KEY_CODE_Q)
		change_angle(INCREASE, all_data);
	else if (keycode == KEY_CODE_A)
		change_angle(DECREASE, all_data);
	else if (keycode == KEY_CODE_ESC)
		exit_window();
	return (0);
}

void	change_angle(int angle_change, t_all_data *all_data)
{
	if (angle_change == INCREASE && (all_data->map_data->angle + 5 <= 45))
	{
		all_data->map_data->angle = all_data->map_data->angle + 5;
		convert_to_iso_map(all_data->map_data);
	}
	else if (angle_change == DECREASE && (all_data->map_data->angle - 5 >= 0))
	{
		all_data->map_data->angle = all_data->map_data->angle - 5;
		convert_to_iso_map(all_data->map_data);
	}
	update_window(all_data);
}

void	change_scale(int scale_change, t_all_data *all_data)
{
	int	delta_change;

	if (all_data->map_data->scale > 1 || scale_change == INCREASE)
	{
		if (all_data->map_data->scale < 20)
			delta_change = 1;
		else
			delta_change = 10;
		all_data->map_data->scale = all_data->map_data->scale
			+ (scale_change * delta_change);
		convert_to_iso_map(all_data->map_data);
	}
	update_window(all_data);
}

void	move_iso_map(float x, float y, t_all_data *all_data)
{
	t_float_coor	movement;

	movement.x = x;
	movement.y = y;
	all_data->map_data->offset.x = all_data->map_data->offset.x
		+ (x / all_data->map_data->scale);
	all_data->map_data->offset.y = all_data->map_data->offset.y
		+ (y / all_data->map_data->scale);
	translate_iso_map(movement, all_data->map_data);
	update_window(all_data);
}

void	update_window(t_all_data *all_data)
{
	clear_image(&all_data->mlx_vars->img);
	draw_iso_map(all_data->map_data, &all_data->mlx_vars->img);
	mlx_put_image_to_window(all_data->mlx_vars->mlx,
		all_data->mlx_vars->mlx_win, all_data->mlx_vars->img.img_ptr, 0, 0);
}
