/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:14:38 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/08 16:52:04 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "GNL/get_next_line.h"
#include <unistd.h>

t_point	**make_table(char *s, t_init *d)
{
	t_point **start;
	t_point	**startbck;
	time_t	t;

	d->xbck = d->x;
	d->ybck = d->y;
	srand((unsigned) time(&t));
	if (!(start = (t_point **)malloc(sizeof(t_point *) * ((((d->x) * (d->y) + 1))))))
		return (NULL);
	while ((((d->spread + d->zrate) * (d->y)) > (d->wHeight)) || ((d->spread * d->x) > ((d->wWidth))))
		d->spread--;
	d->spread = d->x * d->y < 1200 ? d->spread - (d->spread/4) : d->spread - 2;
	if (!d->spread)
		d->spread = 1;
	startbck = start;
	while (*s)
	{
		init_start_object(start);
		if (!(*start))
			return (NULL);
		if ((*s >= 48 && *s <= 57) || (*s == '-' || *s == '+'))
			(*start)->z = (ft_atoi(((const char *)s)) * d->zrate) % 450;
		while (*s && ((*s >= 48 && *s <= 57) || *s == '-' || *s == '+'))
			s++;
		(*start)->c = -3;
		if (*s == ',')
		{
			(*start)->c = ft_atoi_hex(s);
			while (*s && (ft_is_hex(*s) || ft_isdigit(*s) || *s == 'x' || *s == ','))
				s++;
		}
		while (*s && (!((*s>= 48 && *s <= 57) || *s == '-' || *s == '+')))
			s++;
		if (d->x == 0)
		{
			d->x = d->xbck;
			d->y--;
		}
		(*start)->x = (((d->xbck - d->x--)) * d->spread);
		(*start)->y = ((((d->ybck - d->y))) * d->spread);
		if (((*start)->c == -3 && (*start)->z != 0 && d->rand))
		{
			(*start)->c = ((((rand() % d->rand))) & 0xff) << 16;
			(*start)->c |= ((((rand() % d->rand))) & 0xff) << 8;
			(*start)->c |= ((((rand() % d->rand))) & 0xff);
		}
		else if ((*start)->c == -3)
			(*start)->c = d->colorz;
		start++;
	}
	(*start) = NULL;
	return (startbck);
}

int	test_valid(char *points, t_init *n)
{
	n->xbck = -1;
	while(points[n->i])
	{
		n->x = 0;
		while (points[n->i] != '\n')
		{
			if (ft_isdigit(points[n->i]) || points[n->i] == '-')
			{
				n->x++;
				while (ft_isdigit(points[n->i]))
					n->i++;
				if (points[n->i] == ',')
					if (points[n->i + 1] && points[n->i + 1] == '0')
						if (points[n->i + 2] && points[n->i + 2] == 'x')
							n->i += 3;
				while (ft_is_hex(points[n->i]) || ft_isdigit(points[n->i]))
					n->i++;
			}
			while (points[n->i] == ' ')
				n->i++;
			if (points[n->i] != '\n' && points[n->i] != '-' && !ft_isdigit(points[n->i]))
				return (-1);
			if (points[n->i] == '-')
				n->i++;
		}
		n->i++;
		if (n->xbck != -1 && n->xbck != n->x)
			return (-2);
		n->xbck = n->x;
		n->y++;
	}
	n->ybck = n->y;
	return (1);
}

int	get_line_and_len(int fd, char **into)
{
	int	ret;
	int oldret;
	char *new;
	char *bck;

	ret = 0;
	oldret = ret;
	*into = NULL;
	if (((read(fd, NULL, 0)) < 0))
		return (-1);
	while(get_next_line(fd, &new) > 0)
	{
		if (new)
		{
			new = ft_strjoin(new, "\n\0");
			ret += ft_strlen(new);
		}
		if (*into)
			bck = *into;
		if (!(*into = (char *)malloc(sizeof(char) * ret + 1)))
			return (0);
		if (bck)
			*into = ft_strcpy(*into, bck);
		ft_strncpy(*into + oldret, new, ret - oldret + 1);
		oldret = ret;
	}
	if (*into == NULL)
		return (-1);
	return (ret);
}
