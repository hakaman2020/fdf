/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_image_ops.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/02 15:32:49 by hman          #+#    #+#                 */
/*   Updated: 2021/08/02 15:58:04 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_IMAGE_OPS_H
# define FDF_IMAGE_OPS_H

# include "fdf_structs.h"

void	draw_pixel(t_img *img, int x, int y, unsigned int colour);
void	draw_iso_map(t_map_data *map_data, t_img *img);
void	draw_horizontal_lines(t_map_data *map_data, t_img *img);
void	draw_vertical_lines(t_map_data *map_data, t_img *img);
void	clear_image(t_img *img);
#endif
