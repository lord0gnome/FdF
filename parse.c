/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:14:38 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/05 16:37:27 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "GNL/get_next_line.h"
#include <stdio.h>

static void	init_start_object(t_point **object)
{
	((*object) = (t_point *)malloc(sizeof(t_point)));
	(*object)->x = 0;
	(*object)->y = 0;
	(*object)->z = 0;
	(*object)->c = 0;
	(*object)->ldx = 0;
	(*object)->ldy = 0;
}

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
	while (((d->spread * d->y) > (d->wHeight / 2)) || ((d->spread * d->x) > ((d->wWidth / 2))))
		d->spread--;
	startbck = start;
		while (*s)
		{
			init_start_object(start);
			if (!(*start))
				return (NULL);
			if ((*s >= 48 && *s <= 57) || (*s == '-' || *s == '+'))
				(*start)->z = ft_atoi((const char *)s);
			while (*s && ((*s >= 48 && *s <= 57) || *s == '-' || *s == '+'))
				s++;
			if (*s == ',')
			{
				(*start)->c = ft_atoi_hex(s);
				while (*s && (ft_is_hex(*s) || ft_isdigit(*s) || *s == 'x' || *s == ','))
					s++;
			}
			else
				(*start)->c = -3;
			while (*s && (!((*s>= 48 && *s <= 57) || *s == '-' || *s == '+')))
				s++;
			if (d->x == 0)
			{
				d->x = d->xbck;
				d->y--;
			}
			(*start)->x = (((d->xbck - d->x--)) * d->spread);
			(*start)->y = ((((d->ybck - d->y))) * d->spread);
			if ((*start)->c == -3 && (*start)->z != 0)
			{
				(*start)->c = ((abs(((*start)->z)) + (rand() % 240)) & 0xff) << 16;
				(*start)->c |= ((abs(((*start)->z)) + (rand() % 240)) & 0xff) << 8;
				(*start)->c |= ((abs(((*start)->z)) + (rand() % 240)) & 0xff);
			}
			else if ((*start)->c == -3)
				(*start)->c = d->colorz == 1 ? 0xffffff : 0;
			start++;
		}
	return (startbck);
}

int	test_valid(char *points, t_init *n)
{
	n->i = 0;
	n->y = 0;
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
				return (-3);
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
	n->i = 0;
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
	return (ret);
}
