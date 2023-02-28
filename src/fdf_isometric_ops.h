/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_isometric_ops.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/14 16:10:18 by hman          #+#    #+#                 */
/*   Updated: 2021/07/29 15:07:33 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_ISOMETRIC_OPS_H
# define FDF_ISOMETRIC_OPS_H

# include "fdf_structs.h"

void			create_empty_iso_map(t_map_data *map_data);
void			convert_to_iso_map(t_map_data *map_data);
t_float_coor	convert_to_iso_coor(int x_map, int y_map, t_map_data *map_data);
void			translate_iso_map(t_float_coor move, t_map_data *map_data);

#endif