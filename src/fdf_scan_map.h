/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_scan_map.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/23 16:33:32 by hman          #+#    #+#                 */
/*   Updated: 2021/08/02 17:21:34 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_SCAN_MAP_H
# define FDF_SCAN_MAP_H

int		scan_file(char *filename, int *cols, int *rows);
void	process_line(char *line, int *cols, int fd);
int		count_cols(char *line, int fd);
void	free_split(char **numbers);

#endif