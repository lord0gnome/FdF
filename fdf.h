/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:14:51 by guiricha          #+#    #+#             */
/*   Updated: 2016/03/20 20:41:24 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H
# include "libft/libft.h"
# include "GNL/get_next_line.h"
# include <mlx.h>
# include <stdlib.h>
# include "ft_printf/ft_printf.h"
# include <fcntl.h>

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int			c;
}				t_point;

t_point			*test_points(char *points);
t_point			*init_point(int x, int y, int z);
int				get_line_and_len(int fd, char **into);
int				test_valid(int *numlines, int *num_in_line, char *points);
t_point			**make_table(char *points, int numlines, int num_in_line);

#endif
