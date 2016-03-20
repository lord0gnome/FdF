/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:14:38 by guiricha          #+#    #+#             */
/*   Updated: 2016/03/20 18:25:44 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "GNL/get_next_line.h"

int	test_and_store(int *numlines, int *num_in_line, char *points)
{
	int	i;
	int	nilbck;

	i = 0;
	*num_in_line = 0;
	*numlines = 0;
	nilbck = *num_in_line;
	while(points[i])
	{
		if (nilbck != *num_in_line)
			return (-1);
		nilbck = *num_in_line;
		while (points[i] != '\n')
		{
			if (ft_isdigit(points[i]))
			{
				*num_in_line += 1;
				while (ft_isdigit(points[i]))
					i++;
			}
			else
				return (-2);
			if (points[i] == ' ')
				i++;
			else if (points[i] != '\n')
				return (-3);
		}
		*numlines += 1;
		i++;
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
