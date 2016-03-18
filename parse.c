/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:14:38 by guiricha          #+#    #+#             */
/*   Updated: 2016/03/18 19:13:20 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**test_points(char *points)
{
	int		len;
	size_t	index;
	t_point	*new;
	int		y;
	int		z;


	len = 0;
	y = 0;
	ft_printf("and %p  ", &new);
		index = 0;
		while (line[index])
		{
			z = ft_atoi(line + index);
			table* = init_point(0 + (index * 50), 0 + (y * 50), z);
//			ft_printf("x :%d y :%d z :%d adress :%p\n", new->x, new->y, new->z, &new);
			ft_putnbr(ft_nbrlen(z));
			index += ft_nbrlen(z);
		}
		y++;
	return (new);
}
