/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:14:51 by guiricha          #+#    #+#             */
/*   Updated: 2016/03/18 16:16:10 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

#include "libft/libft.h"
#include "GNL/get_next_line.h"
#include <mlx.h>
#include <stdlib.h>
#include "ft_printf/ft_printf.h"

typedef struct	s_point
{
	int				x;
	int				y;
	int				z;
	int				c;
}				t_point;

t_point	*test_points(char *points);
t_point	*init_point(int x, int y, int z);
int		convert_and_count(int fd, char **str);

#endif
