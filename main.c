/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 11:17:55 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/05 15:34:25 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "fdf.h"
#include <stdlib.h>
#include <math.h>

t_point	**offset(t_point **start)
{
	t_point **bck;
	int		xlow;
	int		ylow;

	bck = start;
	if (*start && (*start)->x == 0 && (*start)->y == 0)
	{
		xlow = (*start)->x;
		ylow = (*start)->y;
		while (*start)
		{
			if ((*start)->x < xlow)
				xlow = (*start)->x;	
			if ((*start)->y < ylow)
				ylow = (*start)->y;	
			start++;
		}
		start = bck;
		while (*start)
		{
			(*start)->y += abs(ylow) + 25;
			(*start)->x += abs(xlow) + 25;
			start++;
		}
	}
	return (bck);
}

t_point	**iso_view(t_point **start)
{
	int xb;
	int yb;
	t_point	**bck;

	bck = start;
	while (*start)
	{
		xb = (*start)->x;
		yb = (*start)->y;
		(*start)->x = xb - yb;
		(*start)->y = (yb + xb) / 2;
		if ((*start)->z != 0)
			(*start)->y -= (*start)->z;
		start++;
	}
	return (bck);
}


void	modify_init_with_args(int argc, char **argv, t_init *n)
{
	int	i;

	i = 2;
	while (argc > 2)
	{
		if (!strncmp(argv[i], "wHeight:\0", 8))
			n->wHeight = ft_atoi(argv[i] + 8);
		else if (!strncmp(argv[i], "wWidth:\0", 7))
			n->wWidth = ft_atoi(argv[i] + 7);
		else if (!strncmp(argv[i], "spread:\0", 7))
			n->spread = ft_atoi(argv[i] + 7);
		else if (!strncmp(argv[i], "zrate:\0", 6))
			n->zrate = ft_atoi(argv[i] + 6);
		else if (!strncmp(argv[i], "colorzero:\0", 10))
			n->colorz = ft_atoi(argv[i] + 10);
		argc--;
		i++;
	}
	n->wWidth = n->wWidth >= 25 && n->wWidth < 1920 ? n->wWidth : 500;
	n->wHeight = n->wHeight >= 25 && n->wHeight < 1080 ? n->wHeight : 500;
	n->zrate = n->zrate > 0 && n->zrate <= 9 ? n->zrate : 1;
	n->spread = n->spread >= 1 && n->spread < 1920 ? n->spread : 50;
	n->colorz = n->colorz == 0 || n->colorz == 1 ? n->colorz : 1;
}

void	init_init(t_init **n)
{
	(*n)->i      = 0;
	(*n)->x      = 0;
	(*n)->y      = 0;
	(*n)->xbck   = 0;
	(*n)->ybck   = 0;
	(*n)->pitch  = 0;
	(*n)->spread = 0;
	(*n)->wWidth = 1024;
	(*n)->wHeight= 768;
	(*n)->zmax   = 0;
	(*n)->zmin   = 0;
	(*n)->colorz = -1;
	(*n)->bpp    = 0;
	(*n)->sl     = 0;
	(*n)->pxdst  = 0;
}

int	main(int argc, char **argv)
{
	void	*mlxinit;
	void	*window1;
	void	*mlximg1;
	char	*mlxret;
	char	*test;
	int		fd;
	int		bpp;
	int		sizeline;
	int		endian;
	int		numinline;
	int		numlines;
	int		retoftest;
	t_point	**new;
	int		index;
	t_init	*n;


	if (!(n = (t_init *)malloc(sizeof(t_init))))
		return (-1);
		init_init(&n);
	index = 0;
	if (argc >= 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			return (-1);
		get_line_and_len(fd, &test);
		ft_putnbr(++index);
		retoftest = test_valid(test, n);
		ft_putnbr(retoftest);
		ft_putnbr(++index);
		modify_init_with_args(argc, argv, n);
		ft_putnbr(++index);
		ft_putnbr(n->colorz);
		numlines = n->y;
		numinline = n->x;
		if (!(new = make_table(test, n)))
			return (-1);
		ft_putnbr(++index);
		mlxinit = mlx_init();
		ft_putnbr(++index);
		mlximg1 = mlx_new_image(mlxinit, n->wWidth, n->wHeight);
		ft_putnbr(++index);
		window1 = mlx_new_window(mlxinit ,n->wWidth, n->wHeight, "fdf");
		//ft_putnbr(++index);
		new = iso_view(new);
		//ft_putnbr(++index);
		new = offset(new);
		ft_putnbr(++index);
		mlxret = mlx_get_data_addr(mlximg1, &bpp, &sizeline, &endian);
		ft_putnbr(++index);
		n->bpp = bpp;
		n->sl = sizeline;
		draw_pixels(mlxret, new, n);
		ft_putnbr(++index);
		mlx_put_image_to_window(mlxinit, window1, mlximg1, 0, 0);
		ft_putnbr(++index);
		mlx_loop(mlxinit);
	}
}
