/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 11:17:55 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/08 16:51:36 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "fdf.h"
#include <stdlib.h>
#include <math.h>

int			my_key_func(int keycode, void *param)
{
	param = &keycode;
	if ((keycode) == 53)
		exit(EXIT_SUCCESS);
	return (0);
}

t_point		**offset(t_point **start, t_init *d)
{
	t_point **bck;

	bck = start;
	if (*start)
	{
		d->var1 = (*start)->x;
		d->var2 = (*start)->y;
		while (*start)
		{
			if ((*start)->x < d->var1)
				d->var1 = (*start)->x;
			if ((*start)->y < d->var2)
				d->var2 = (*start)->y;
			start++;
		}
		start = bck;
		while (*start)
		{
			(*start)->y += abs(d->var2) + 25;
			(*start)->x += abs(d->var1) + 25;
			(*start)->x = (*start)->x >= d->wWidth || (*start)->x <= 0 ? d->wWidth - 25 : (*start)->x;
			(*start)->y = (*start)->y >= d->wHeight || (*start)->y <= 0 ? d->wWidth - 25 : (*start)->y;
			start++;
		}
	}
	return (bck);
}

t_point		**iso_view(t_point **start, t_init *d)
{
	t_point	**bck;

	bck = start;
	while (*start)
	{
		d->var1 = (*start)->x;
		d->var2 = (*start)->y;
		(*start)->x = d->var1 + d->var2;
		(*start)->y = (d->var2 - d->var1) / d->pitch;
		if ((*start)->z != 0)
			(*start)->y -= (*start)->z;
		start++;
	}
	return (bck);
}

int			main(int argc, char **argv)
{
	int		fd;
	int		endian;
	t_point	**new;
	t_init	*n;
	int		ret;

	if (!(init_init(&n)))
		return (-1);
	if (argc < 2 || (fd = open(argv[1], O_RDONLY)) < 0)
		return (ft_printf("open error or too few arguments.\n"));
	if ((ret = get_line_and_len(fd, &n->parsed)) < 0)
		return (ft_printf("read error. code = '%d'\n", ret));
	if ((ret = test_valid(n->parsed, n)) < 0)
		return (ft_printf("parse error. code = '%d',\n\n\"%s\"\n\n", ret,  n->parsed));
	apply_args(argc, argv, n);
	if (!(new = make_table(n->parsed, n)))
		return (-1);
	n->init = mlx_init();
	n->window = mlx_new_window(n->init, n->wWidth, n->wHeight, "fdf");
	n->image = mlx_new_image(n->init, n->wWidth, n->wHeight);
	n->imagestr = mlx_get_data_addr(n->image, &(n->bpp), &(n->sl), &endian);
	new = iso_view(new, n);
	new = offset(new, n);
	draw_pixels(n->imagestr, new, n);
	mlx_put_image_to_window(n->init, n->window, n->image, 0, 0);
	mlx_key_hook(n->window, &my_key_func, (void *)n);
	mlx_loop(n->init);
	return (0);
}
