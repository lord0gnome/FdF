/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:14:38 by guiricha          #+#    #+#             */
/*   Updated: 2016/03/17 16:52:54 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**test_points(int fd)
{
	char	*line;
	int		len;
	size_t	index;
	t_point **start;
	t_point	*new;
	int		y;
	int		z;


	len = 0;
	y = 0;
	start = &new;
	ft_printf("%p and %p  ", start, &new);
	while ((get_next_line(fd, &line)) > 0)
	{
		index = 0;
		while (line[index])
		{
			z = ft_atoi(line + index);
			new = p_new_object(0 + index*50, 0 + y*50, z, 0x00ffffff);
	ft_printf("after :%p and %p  \n", start, &new);
			p_add_to_end(start, new);
	ft_printf("before : %p and %p  \n", start, &new);
			ft_putnbr(ft_nbrlen(z));
			index += ft_nbrlen(z);
		}
		y++;
	}
	return (start);
}
