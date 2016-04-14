/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <guiricha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:16:56 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/12 11:50:14 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "./libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

t_stock	*get_fd(t_stock **start, int const fd, int *ret)
{
	t_stock *temp;
	t_stock	*new;

	temp = *start;
	if (temp)
	{
		if (temp->fd == fd)
			return (temp);
		while (temp->next)
		{
			temp = temp->next;
			if (temp->fd == fd)
				return (temp);
		}
	}
	if (!(new = (t_stock*)malloc(sizeof(t_stock))))
		*ret = -1;
	new->fd = fd;
	new->next = NULL;
	if (temp)
		temp->next = new;
	if (!(new->buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		*ret = -1;
	new->s = 0;
	return (new);
}

int		read_buf(int const fd, t_stock *d)
{
	if (fd < 0)
		return (-1);
	if (d->buff)
		ft_bzero(d->buff, BUFF_SIZE + 1);
	d->i = 0;
	d->s = read(fd, d->buff, BUFF_SIZE);
	return (d->s);
}

int		handle_i(t_ints *v, t_stock *d, char **line)
{
	char	*tmp;

	if (v->i)
	{
		tmp = *line;
		if (!(*line = (char *)malloc(sizeof(char) * (v->size + v->i + 1))))
			return (0);
		if (v->size)
			ft_memcpy(*line, tmp, v->size);
		ft_strncpy(*line + v->size, d->buff + d->i, (size_t)v->i);
		(*line)[v->size + v->i] = 0;
		v->size += v->i;
		d->i += v->i;
		free(tmp);
	}
	if (!v->i && (d->buff[d->i] == '\n'))
	{
		v->ret = 1;
		if (d->buff[d->i] == '\n' && !(v->size))
			*line = ft_strdup("");
		d->i++;
	}
	return (v->ret);
}

int		gnl_do(int const fd, char **line, t_stock *d)
{
	t_ints	v;

	v.size = 0;
	v.ret = 42;
	while (v.ret == 42)
	{
		if (d->i >= d->s)
			v.ret = read_buf(fd, d);
		if (v.ret == -1 || v.ret == 0)
		{
			if (v.ret == 0)
				v.ret = 1;
			return (v.ret);
		}
		v.ret = 42;
		v.i = 0;
		while (d->buff[v.i + d->i] != '\n' && d->i + v.i < d->s)
			v.i++;
		if (!(handle_i(&v, d, line)))
			return (-1);
	}
	return (v.ret);
}

int		get_next_line(int const fd, char **line)
{
	static t_stock	*current;
	t_stock			*d;
	int				ret;

	ret = 1;
	if (!line)
		return (-1);
	*line = NULL;
	if (!current)
	{
		if (!(current = (t_stock*)malloc(sizeof(t_stock))))
			return (-1);
		if (!(current->buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
			return (-1);
		current->fd = fd;
		current->next = NULL;
		current->s = 0;
	}
	d = get_fd(&current, fd, &ret);
	if (ret == -1 || ret == 0)
		return (ret);
	if ((d->i >= d->s || !d->s) && ((ret = read_buf(fd, d)) == -1 || ret == 0))
		return (ret);
	ret = gnl_do(fd, line, d);
	return (ret);
}
