/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 14:04:31 by guiricha          #+#    #+#             */
/*   Updated: 2016/03/17 14:27:44 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*p_new_object(int x, int y, int z, int c)
{
	t_point	*new;

	if (!(new = (t_point *)malloc(sizeof(t_point))))
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	new->c = c;
	new->next = NULL;
	return (new);
}

void	p_add_to_lst(t_point **last, t_point *new)
{
	(new)->next = (*last);
	*last = new;
}
