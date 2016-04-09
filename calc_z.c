/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_z.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/09 11:28:10 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/09 15:20:54 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		calc_z( t_point **s, t_init *d)
{
	t_point	**bck;

	bck = s;
	if (*s)
	{
		d->zlow = (*s)->z;
		d->zhigh = (*s)->z;
		s++;
	}
	while (*s)
	{
		if ((*s)->z > d->zhigh)
			d->zhigh = (*s)->z;
		if ((*s)->z < d->zlow)
			d->zlow = (*s)->z;
		s++;
	}
	s = bck;
	while (*s)
	{
	//	(*s)->c = ();
		s++;
	}
	while (abs(((d->zhigh - d->zlow) * d->zrate)) > 255)
		d->zrate = d->zrate < 0 ? d->zrate + 1 : d->zrate - 1;
	if (d->zrate == 0)
		d->zrate = 1;
	return (1);
}
