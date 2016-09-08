/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 11:17:55 by guiricha          #+#    #+#             */
/*   Updated: 2016/09/08 18:16:12 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "minilibx_macos/X.h"
#include "fdf.h"
#include <stdlib.h>
#include <math.h>

static void	getlows(t_point **s, t_init *d)
{
	d->var1 = (*s)->x;
	d->var2 = (*s)->y;
	while (*s)
	{
		if ((*s)->x < d->var1)
			d->var1 = (*s)->x;
		if ((*s)->y < d->var2)
			d->var2 = (*s)->y;
		s++;
	}
}

t_point		**offset(t_point **s, t_init *d)
{
	t_point **bck;

	bck = s;
	if (*s)
	{
		getlows(s, d);
		s = bck;
		while (*s)
		{
			(*s)->y += abs(d->var2) + 10;
			(*s)->x += abs(d->var1) + 10;
			if (((*s)->y >= d->wheight - 3 || (*s)->y <= 0) ||
					(*s)->x >= d->wwidth - 3 || (*s)->x <= 0)
				(*s)->dnd = 1;
			s++;
		}
	}
	return (bck);
}

static int	main_tests(int argc, char **argv, int *fd, t_init *n)
{
	if (argc < 2 || (*fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_putstr("open error or too few arguments.\n");
		return (-1);
	}
	if ((get_line_and_len(*fd, &n->parsed)) < 0)
	{
		ft_putstr("read error.");
		return (-2);
	}
	if ((test_valid(n->parsed, n)) < 0)
	{
		ft_putstr("parse error, file is |\n");
		ft_putstr(n->parsed);
		return (-3);
	}
	return (-5);
}

void		main_loop(t_point **new, t_init *n)
{
	calc_z(new, n);
	new = n->left ? iso_view_left(new, n) : iso_view(new, n);
	new = offset(new, n);
	n->npoint = new;
	bzero(n->imagestr, n->sl * n->wheight);
	draw_pixels(n->imagestr, new, n);
	mlx_put_image_to_window(n->init, n->window, n->image, 0, 0);
	mlx_loop(n->init);
}

int			funtimes(t_init *n)
{
	if (n->toggle)
	{
		n->pitch = n->pitch - 0.05 == 0 ? n->pitch - 0.1 : n->pitch - 0.05;
		n->zrate -= 0.1;
		if (n->pitch < 1.5)
			n->toggle = 0;
	}
	else if (!n->toggle)
	{
	n->pitch = n->pitch + 0.05 == 0 ? n->pitch + 0.1 : n->pitch + 0.05;
	n->zrate += 0.1;
	if (n->pitch > 6)
		n->toggle = 1;
	}
	n->npoint = NULL;
	n->npoint = make_table(n->parsed, n);
	calc_z(n->npoint, n);
	n->npoint = n->left ? iso_view_left(n->npoint, n) : iso_view(n->npoint, n);
	n->npoint = offset(n->npoint, n);
	bzero(n->imagestr, n->sl * n->wheight);
	draw_pixels(n->imagestr, n->npoint, n);
	mlx_put_image_to_window(n->init, n->window, n->image, 0, 0);
	ft_putnbr(n->zrate);
	draw_pixels(n->imagestr, n->npoint, n);
	return (1);
}

int			main(int argc, char **argv)
{
	int		fd;
	int		endian;
	t_init	*n;

	if (!(init_init(&n)))
		return (-1);
	if ((main_tests(argc, argv, &fd, n)) != -5)
		return (-1);
	apply_args(argc, argv, n);
	if (!(n->npoint = make_table(n->parsed, n)))
		return (-1);
	n->init = mlx_init();
	n->window = mlx_new_window(n->init, n->wwidth, n->wheight, "fdf");
	n->image = mlx_new_image(n->init, n->wwidth, n->wheight);
	n->imagestr = mlx_get_data_addr(n->image, &(n->bpp), &(n->sl), &endian);
	mlx_hook(n->window, KeyPress, KeyPressMask, &better_key_func, n);
	mlx_loop_hook(n->init, &funtimes, n);
	main_loop(n->npoint, n);
	return (1);
}
