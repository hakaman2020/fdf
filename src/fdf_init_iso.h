/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_init_iso.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/29 16:35:03 by hman          #+#    #+#                 */
/*   Updated: 2021/07/29 17:51:27 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_INIT_ISO_H
# define FDF_INIT_ISO_H

# include "fdf_structs.h"

void	set_initial_map_info(t_map_data *map_data, unsigned int window_width,
			unsigned int window_height);
void	set_center_isomap(t_map_data *map_data, t_max_min *max_min_isomap);
void	find_max_min_isomap(t_map_data *map_data, t_max_min *max_min_isomap);
int		resize_isomap(t_map_data *map_data, t_max_min *max_min_isomap);

#endif