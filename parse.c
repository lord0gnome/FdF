/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:14:38 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/01 15:35:33 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "GNL/get_next_line.h"

static void	init_start_object(t_point *object)
{
	object->x = -1;
	object->y = -1;
	object->z = -1;
	object->c = -1;
	object->ld = -1;
}

t_point	**make_table(char *s, t_init *d)
{
	t_point **start;
	t_point	**startbck;

	d->xbck = d->x;
	d->ybck = d->y;
	if (!(start = (t_point **)malloc(sizeof(t_point *) * ((d->x) * (d->y + 2)) + 1)))
		return (NULL);
	//	ft_printf("lines;%d,  X;%d sizeofstart:%zu\n", numlines, num_in_line, sizeof(start));
		while (((d->spread * d->y) > (1080) / 2) || ((d->spread * d->x) > ((1920 / 2))))
			d->spread--;
	while (d->x--)
	{
		*start = NULL;
		start++;
	}
	startbck = start;
	d->x = d->xbck;
	while (*s)
	{
		if (!((*start) = (t_point *)malloc(sizeof(t_point))))
			return (NULL);
		init_start_object(*start);
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
			(*start)->c = ((abs((*start)->z) * 15) & 0xff) << 16;
			(*start)->c |= ((abs((*start)->z) * 14) & 0xff) << 8;
			(*start)->c |= ((abs((*start)->z) * 13) & 0xff);
		}
		else if ((*start)->c == -3)
			(*start)->c = 0xffffff;
		//ft_printf("pixel n%d x = [%d], y = [%d], z = [%d], c = [%d], linenumber = [%d]\n", tmpcount, (*start)->x, (*start)->y, (*start)->z, (*start)->c, numlines);
		start++;
	}
	d->x = d->xbck;
	d->x++;
	while (d->x--)
	{
		*start = NULL;
		start++;
	}
	*start = NULL;
	ft_putstr("bloop");
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
		new = ft_strjoin(new, "\n\0");
		ret += ft_strlen(new);
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
