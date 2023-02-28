/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_key_press.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/02 16:39:57 by hman          #+#    #+#                 */
/*   Updated: 2021/08/05 12:47:51 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_KEY_PRESS_H
# define FDF_KEY_PRESS_H

# include "fdf_structs.h"

# if LINUX == 0 
#  define KEY_CODE_LEFT		123
#  define KEY_CODE_RIGHT	124
#  define KEY_CODE_DOWN		125
#  define KEY_CODE_UP		126
#  define KEY_CODE_Z		6
#  define KEY_CODE_X		7
#  define KEY_CODE_Q		12
#  define KEY_CODE_A		0
#  define KEY_CODE_ESC		53
#  define INCREASE			1
#  define DECREASE			-1
# else
#  define KEY_CODE_LEFT		65361
#  define KEY_CODE_RIGHT	65363
#  define KEY_CODE_DOWN		65364
#  define KEY_CODE_UP		65362
#  define KEY_CODE_Z		122
#  define KEY_CODE_X		120
#  define KEY_CODE_Q		113
#  define KEY_CODE_A		97
#  define KEY_CODE_ESC		65307
#  define INCREASE			1
#  define DECREASE			-1
# endif

int		pressed_key(int keycode, t_all_data *all_data);
void	change_angle(int angle_chang, t_all_data *all_data);
void	change_scale(int scale_change, t_all_data *all_data);
void	move_iso_map(float x, float y, t_all_data *all_data);
void	update_window(t_all_data *all_data);

#endif