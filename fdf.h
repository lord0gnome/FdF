/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:14:51 by guiricha          #+#    #+#             */
/*   Updated: 2016/03/29 14:33:20 by guiricha         ###   ########.fr       */
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

typedef struct	s_line
{
	int	sx;
	int	sy;
	int	dx;
	int	dy;
	int x1;
	int x2;
	int y1;
	int y2;
	int	err;
	int	err2;
}				t_line;

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int			c;
}				t_point;

int				ft_is_hex(char c);
int				ft_atoi_hex(const char *str);
t_point			*test_points(char *points);
t_point			*init_point(int x, int y, int z);
int				get_line_and_len(int fd, char **into);
int				test_valid(int *numlines, int *num_in_line, char *points);
t_point			**make_table(char *s, int numlines, int num_in_line);

#endif
