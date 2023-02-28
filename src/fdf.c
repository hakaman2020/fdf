/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/22 14:17:43 by hman          #+#    #+#                 */
/*   Updated: 2021/08/05 14:08:41 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h> //exit()
#include <math.h>

#include "fdf.h"
#include "fdf_parser.h"
#include "fdf_init_iso.h"
#include "fdf_isometric_ops.h"
#include "fdf_bres_algo.h"
#include "fdf_structs.h"
#include "fdf_key_press.h"
#include "fdf_image_ops.h"
#include "errors.h"

#if LINUX == 0
# include "../lib/mlx/mlx.h"		//mlx librarry for mac
#else
# include "../lib/mlx_linux/mlx.h"	// mlx library for linux
#endif

//default window dimensions
#define WINDOW_X 1000	//window width
#define WINDOW_Y 1000	//window height

int	main(int argc, char **argv)
{
	t_mlx_vars	mlx_vars;	
	t_map_data	map_data;
	t_all_data	all_data;

	if (argc != 2)
		exit_on_error("Usage: ./fdf [FILENAME].fdf");
	fdf_parser(argv[1], &map_data);
	set_initial_map_info(&map_data, WINDOW_X, WINDOW_Y);
	initialize(&mlx_vars);
	all_data.mlx_vars = &mlx_vars;
	all_data.map_data = &map_data;
	draw_iso_map(&map_data, &mlx_vars.img);
	mlx_put_image_to_window(mlx_vars.mlx, mlx_vars.mlx_win,
		mlx_vars.img.img_ptr, 0, 0);
	mlx_key_hook(mlx_vars.mlx_win, &pressed_key, &all_data);
	if (!LINUX)
		mlx_hook(mlx_vars.mlx_win, 17, 1L << 17, &exit_window, NULL);
	else
		mlx_hook(mlx_vars.mlx_win, 33, 0, &exit_window, NULL);
	mlx_loop(mlx_vars.mlx);
	return (0);
}

/*
**	initialize the mlx instance variables
*/

void	initialize(t_mlx_vars *mlx_vars)
{
	mlx_vars->mlx = mlx_init();
	if (mlx_vars->mlx == NULL)
		exit_on_error("Mlx initiation error.");
	mlx_vars->mlx_win = mlx_new_window(mlx_vars->mlx, WINDOW_X, WINDOW_Y,
			"FDF");
	if (mlx_vars->mlx_win == NULL)
		exit_on_error("Something went wrong creating a windows.");
	mlx_vars->img.img_ptr = mlx_new_image(mlx_vars->mlx, WINDOW_X, WINDOW_Y);
	if (mlx_vars->img.img_ptr == NULL)
		exit_on_error("Something went wrong creating the image buffer.");
	mlx_vars->img.address = mlx_get_data_addr(mlx_vars->img.img_ptr,
			&mlx_vars->img.bits_per_pixel,
			&mlx_vars->img.line_size, &mlx_vars->img.endian);
	mlx_vars->img.width = WINDOW_X;
	mlx_vars->img.height = WINDOW_Y;
}

/*
**	destroy the window instance and exit the application
*/
int	exit_window(void)
{
	exit(0);
	return (0);
}
