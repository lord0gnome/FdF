/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:14:38 by guiricha          #+#    #+#             */
/*   Updated: 2016/03/22 16:32:12 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "GNL/get_next_line.h"

t_point	**make_table(char *s, int numlines, int num_in_line)
{
	int		n;
	t_point **start;
	t_point	**startbck;
	int		xcount;
	int		ycount;
	int		c;

	start = (t_point **)malloc(sizeof(t_point *) * (num_in_line * numlines) + 1);
	startbck = start;
	xcount = num_in_line;
	ycount = numlines;
	while (*s)
	{
		if (*s >= 48 && *s <= 57)
			n = ft_atoi((const char *)s);
		while (*s && (*s >= 48 && *s <= 57))
			s++;
		if (*s == ',')
		{
			c = ft_atoi_hex(s);
			while (*s && (ft_is_hex(*s) || ft_isdigit(*s) || *s == 'x' || *s == ','))
				s++;
		}
		else
			c = 0xffffff;
		while (*s && (!(*s>= 48 && *s <= 57)))
			s++;
		(*start) = (t_point *)malloc(sizeof(t_point));
		if (num_in_line == 0)
		{
			num_in_line = xcount;
			numlines--;
		}
		(*start)->x = ((xcount - num_in_line--) * 25 + 50);
		(*start)->y = ((ycount - numlines) * 25 + 50);
		(*start)->z = n;
		(*start)->c = c;
		start++;
	}
	*start = NULL;
	ft_putstr("bloop");
	return (startbck);
}

int	test_valid(int *numlines, int *num_in_line, char *points)
{
	int	i;
	int	nilbck;

	i = 0;
	*numlines = 0;
	nilbck = -1;
	while(points[i])
	{
		*num_in_line = 0;
		while (points[i] != '\n')
		{
			if (ft_isdigit(points[i]))
			{
				*num_in_line += 1;
				while (ft_isdigit(points[i]))
					i++;
				if (points[i] == ',')
					if (points[i + 1] && points[i + 1] == '0')
						if (points[i + 2] && points[i + 2] == 'x')
							i += 3;
				while (ft_is_hex(points[i]) || ft_isdigit(points[i]))
					i++;
			}
			while (points[i] == ' ')
				i++;
			if (points[i] != '\n' && !ft_isdigit(points[i]))
				return (-3);
		}
		i++;
		if (nilbck != -1 && nilbck != *num_in_line)
			return (-2);
		nilbck = *num_in_line;
		*numlines += 1;
	}
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
		*into = (char *)malloc(sizeof(char) * ret + 1);
		if (bck)
			*into = ft_strcpy(*into, bck);
		ft_strncpy(*into + oldret, new, ret - oldret + 1);
		oldret = ret;
	}
	return (ret);
}
