/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_bres_algo.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/29 14:33:41 by hman          #+#    #+#                 */
/*   Updated: 2021/08/04 14:54:01 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bres_algo.h"
#include "fdf_image_ops.h"

#define COLOR_CYAN 0X0000FFFF
/*
**	this function will implement the bresenham algorithm for drawing a line
**	source used: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
*/

void	draw_line(t_coor point1, t_coor point2, t_img *img)
{
	if (abs_int(point2.y - point1.y) < abs_int(point2.x - point1.x))
	{
		if (point1.x > point2.x)
			draw_line_low_slope(point2, point1, img);
		else
			draw_line_low_slope(point1, point2, img);
	}
	else
	{
		if (point1.y > point2.y)
			draw_line_high_slope(point2, point1, img);
		else
			draw_line_high_slope(point1, point2, img);
	}
}

/*
**	this function will draw the line according to the bresenham line algorithm
**	where the slope is between 0 and 1
*/

void	draw_line_low_slope(t_coor point1, t_coor point2, t_img *img)
{
	int	dx;
	int	dy;
	int	yi;
	int	difference;

	dx = point2.x - point1.x;
	dy = point2.y - point1.y;
	yi = 1;
	if (dy < 0)
		yi = -1;
	if (dy < 0)
		dy = -dy;
	difference = (2 * dy) - dx;
	while (point1.x <= point2.x)
	{
		draw_pixel(img, point1.x, point1.y, COLOR_CYAN);
		if (difference > 0)
		{
			point1.y = point1.y + yi;
			difference = difference + (2 * (dy - dx));
		}
		else
			difference = difference + (2 * dy);
		point1.x = point1.x + 1;
	}
}

void	draw_line_high_slope(t_coor point1, t_coor point2, t_img *img)
{
	int	dy;
	int	dx;
	int	xi;
	int	difference;

	dy = point2.y - point1.y;
	dx = point2.x - point1.x;
	xi = 1;
	if (dx < 0)
		xi = -1;
	if (dx < 0)
		dx = -dx;
	difference = (2 * dx) - dy;
	while (point1.y <= point2.y)
	{
		draw_pixel(img, point1.x, point1.y, COLOR_CYAN);
		if (difference > 0)
		{
			point1.x = point1.x + xi;
			difference = difference + (2 * (dx - dy));
		}
		else
			difference = difference + (2 * dx);
		point1.y = point1.y + 1;
	}
}

/*
**	this function will retun the absolute number of the integer
**	Word of caution it assumes the number is within the range of an integer
*/
long	abs_int(int number)
{
	if (number >= 0)
		return ((long) number);
	else
		return ((long) -1 * number);
}
