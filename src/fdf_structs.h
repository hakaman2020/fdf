/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_structs.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/07 12:49:29 by hman          #+#    #+#                 */
/*   Updated: 2021/08/02 16:08:23 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_STRUCTS_H
# define FDF_STRUCTS_H

// this struct holds the data concerning the image buffer
typedef struct s_img
{
	void	*img_ptr;
	char	*address;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
	int		width;
	int		height;
}				t_img;

// this struct holds all the mlx related instances
typedef struct s_mlx_vars
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
}				t_mlx_vars;

//this struct is for keeping the x y coordinates on the screen
typedef struct s_coor
{
	int	x;
	int	y;
}				t_coor;

//this struct is for keeping the x y coordinates on the screen in float
//format
typedef struct s_float_coor
{
	float	x;
	float	y;
}				t_float_coor;

//this struct will keep track of all the map data and current values 
typedef struct s_map_data
{
	int				**map;
	t_float_coor	**isomap;
	int				cols;
	int				rows;
	float			scale;
	t_float_coor	offset;
	t_coor			window_center;
	unsigned int	window_width;
	unsigned int	window_height;
	float			angle;
}				t_map_data;

//this structs is to store the maximum and minimum values of x and y in a 
//in a iso map
typedef struct s_max_min
{
	float	max_x;
	float	min_x;
	float	max_y;
	float	min_y;
}				t_max_min;

// this struct holds both mlx_vars and map_data struct 
typedef struct s_all_data
{
	t_mlx_vars	*mlx_vars;
	t_map_data	*map_data;
}				t_all_data;

#endif