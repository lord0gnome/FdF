/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:14:51 by guiricha          #+#    #+#             */
/*   Updated: 2016/03/17 14:29:53 by guiricha         ###   ########.fr       */
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
	struct s_point	*next;
}				t_point;

t_point	*test_points(int fd);
t_point	*p_new_object(int x, int y, int z, int c);
void	p_add_to_lst(t_point **last, t_point *new);

#endif
