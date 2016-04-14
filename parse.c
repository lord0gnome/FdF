/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:14:38 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/12 13:16:06 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>

int		is_mine(char c)
{
	if (c != ' ' && c != 'x' && !ft_isdigit(c) && !ft_is_hex(c) &&
		c != '\n' && c != ',' && c != '-' && c != '0')
		return (0);
	return (1);
}

void	help_test_valid(char *points, t_init *n)
{
	if (ft_isdigit(points[n->i]) || points[n->i] == '-')
	{
		n->x++;
		while (ft_isdigit(points[n->i]) || points[n->i] == '-')
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
}

int		test_valid(char *points, t_init *n)
{
	n->xbck = -1;
	while (points[n->i])
	{
		if (!is_mine(points[n->i]))
			return (-3);
		n->x = 0;
		while (points[n->i] != '\n')
		{
			help_test_valid(points, n);
			if (points[n->i] != '\n' && points[n->i] != '-' &&
					!ft_isdigit(points[n->i]))
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

char	*help_glal(char *new, int *ret, char **into, char **bck)
{
	if (new)
	{
		if (!is_mine(*new))
			return (NULL);
		new = ft_strjoin(new, "\n\0");
		*ret += ft_strlen(new);
	}
	if (*into)
		*bck = *into;
	return (new);
}

int		get_line_and_len(int fd, char **into)
{
	int		ret;
	int		oldret;
	char	*new;
	char	*bck;

	ret = 0;
	oldret = ret;
	*into = NULL;
	if (((read(fd, NULL, 0)) < 0))
		return (-1);
	while (get_next_line(fd, &new) > 0)
	{
		if (!(new = help_glal(new, &ret, into, &bck)))
			return (-1);
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
