/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 10:50:39 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/12 15:19:42 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <wchar.h>

int		help_make_table(char *s, t_init *d, t_point **start)
{
	d->i = 0;
	if (!init_start_object(start))
		return (-1);
	if (!(*start))
		return (-1);
	while (s[d->i] == ' ')
		d->i++;
	if ((s[d->i] >= 48 && s[d->i] <= 57) || (s[d->i] == '-' || s[d->i] == '+'))
		(*start)->z = (ft_atoi(((const char *)s + d->i)) * d->zrate);
	while (s[d->i] && ((s[d->i] >= 48 && s[d->i] <= 57) ||
				s[d->i] == '-' || s[d->i] == '+'))
		d->i++;
	(*start)->c = -3;
	if (s[d->i] == ',')
	{
		(*start)->c = ft_atoi_hex(s + d->i);
		while (s[d->i] && (ft_is_hex(s[d->i]) || ft_isdigit(s[d->i]) ||
					s[d->i] == 'x' || s[d->i] == ','))
			d->i++;
	}
	return (d->i);
}

void	help_make_table_more(t_init *d, t_point **start)
{
	if (d->x == 0)
	{
		d->x = d->xbck;
		d->y--;
	}
	(*start)->x = (((d->xbck - d->x--)) * d->spread);
	(*start)->y = ((((d->ybck - d->y))) * d->spread);
	if ((((*start)->z != 0) && (d->rand && d->force)))
	{
		(*start)->c = (((((rand()) % d->rand)) + (*start)->z) & 0xff) << 16;
		(*start)->c |= (((((rand()) % d->rand)) + (*start)->z) & 0xff) << 8;
		(*start)->c |= (((((rand()) % d->rand)) + (*start)->z) & 0xff);
	}
	else if (d->force && (*start)->z == 0)
	{
		(*start)->c = d->force;
	}
	else if ((*start)->c == -3)
		(*start)->c = d->colorz;
}

t_point	**make_table(char *s, t_init *d)
{
	t_point **start;
	t_point	**startbck;
	time_t	t;

	d->xbck = d->x;
	d->ybck = d->y;
	srand((unsigned)time(&t));
	if (!(start = (t_point **)malloc(sizeof(t_point *) * (d->x * d->y + 1))))
		return (NULL);
	while (((d->spread * d->y) > d->wheight) || (d->spread * d->x > d->wwidth))
		d->spread--;
	if (!d->spread)
		d->spread = 1;
	startbck = start;
	while (*s)
	{
		if ((help_make_table(s, d, start)) >= 0)
			s += d->i;
		while (*s && (!((*s >= 48 && *s <= 57) || *s == '-' || *s == '+')))
			s++;
		help_make_table_more(d, start);
		start++;
	}
	(*start) = NULL;
	return (startbck);
}
