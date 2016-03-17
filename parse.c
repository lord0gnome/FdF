/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:14:38 by guiricha          #+#    #+#             */
/*   Updated: 2016/03/17 15:22:32 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*test_points(int fd)
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
	while ((get_next_line(fd, &line)) > 0)
	{
		index = 0;
		while (line[index])
		{
			z = ft_atoi(line);
			new = p_new_object(0 + index*50, 0 + y*50,z, z + 0x00999999);
			p_add_to_lst(start, new);
			index += ft_nbrlen(z);
			if (line[index])
				index++;
		}
		y++;
	}
	return (*start);
}
