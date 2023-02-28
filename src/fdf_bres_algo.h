/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_bres_algo.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/30 12:25:10 by hman          #+#    #+#                 */
/*   Updated: 2021/08/02 17:23:54 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BRES_ALGO_H
# define FDF_BRES_ALGO_H

# include "fdf_structs.h"

void	draw_line(t_coor point1, t_coor point2, t_img *img);
void	draw_line_low_slope(t_coor point1, t_coor point2, t_img *img);
void	draw_line_high_slope(t_coor point1, t_coor point2, t_img *img);
long	abs_int(int number);

#endif