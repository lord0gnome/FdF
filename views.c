/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   views.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 14:46:45 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/12 15:11:08 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point		**iso_view(t_point **s, t_init *d)
{
	t_point	**bck;

	bck = s;
	while (*s)
	{
		d->var1 = (*s)->x;
		d->var2 = (*s)->y;
		(*s)->x = d->var1 + d->var2;
		(*s)->y = (d->var2 - d->var1) / d->pitch;
		if ((*s)->z != 0)
			(*s)->y -= (*s)->z;
		s++;
	}
	return (bck);
}

t_point		**iso_view_left(t_point **s, t_init *d)
{
	t_point	**bck;

	bck = s;
	while (*s)
	{
		d->var1 = (*s)->x;
		d->var2 = (*s)->y;
		(*s)->x = d->var1 - d->var2;
		(*s)->y = (d->var2 + d->var1) / d->pitch;
		if ((*s)->z != 0)
			(*s)->y -= (*s)->z;
		s++;
	}
	return (bck);
}
