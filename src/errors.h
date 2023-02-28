/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/15 16:44:23 by hman          #+#    #+#                 */
/*   Updated: 2021/07/15 16:51:41 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <stdlib.h> //for exit()

void	exit_on_error(char *s);
void	exit_on_error_fd(char *s, int fd);

#endif