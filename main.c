/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 11:17:55 by guiricha          #+#    #+#             */
/*   Updated: 2016/03/29 14:48:21 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "fdf.h"
#include <stdlib.h>
#include <math.h>

t_point	**iso_view(t_point **start, int numinline, int numlines)
{
	int nilbck;
	int	x;
	int	y;
	t_point	**bck;

	bck = start;
	nilbck = numinline;
	ft_printf("%d and %d\n", numinline, numlines);
	y = 0;
	while (numlines)
	{
		numinline = nilbck;
		x = 0;
		while (numinline)
		{
			(*start)->x = (*start)->x + y / 2;
			(*start)->y = (*start)->y + x / 2;
			numinline--;
			x++;
			start++;
		}
		numlines--;
		y++;
	}
	return (bck);
}

void	handle_ret(char *tab, t_point **begin, int sizeline, int bpp)
{
	t_line new;
	ft_printf("sizeline : %d, bpp : %d\n", sizeline, bpp);
	while (*begin)
	{
		ft_putstr("in here");
		tab[(((*begin)->y * sizeline) + ((*begin)->x * (bpp / 8)))] = (*begin)->c << 16 >> 16;
		tab[(((*begin)->y * sizeline) + ((*begin)->x * (bpp / 8))) + 1] = (*begin)->c << 8 >> 16;
		tab[(((*begin)->y * sizeline) + ((*begin)->x * (bpp / 8))) + 2] = (*begin)->c >> 16;
		new.x1 = (*begin)->x;
		new.x2 = (*begin + 1)->x;
		new.y1 = (*begin)->y;
		new.y2 = (*begin + 1)->y;
		new.dx = abs(new.x2 - new.x1);
		new.sx = new.x1 < new.x2 ? 1 : -1;
		new.dy = abs(new.y2 - new.y1);
		new.sy = new.y1 < new.y2 ? 1 : -1;
		new.err = (new.dx > new.dy ? new.dx : -new.dy) / 2;
		while (42)
		{
			tab[(new.y1 * sizeline) + (new.x1 * (bpp / 8))] = (*begin)->c << 16 >> 16;
			tab[((new.y1 * sizeline) + (new.x1 * (bpp / 8))) + 1] = (*begin)->c << 8 >> 16;
			tab[((new.y1 * sizeline) + (new.x1 * (bpp / 8))) + 2] = (*begin)->c >> 16;
			if (new.y1 == new.y2 && new.x1 == new.x2)
				break;
			new.err2 = new.err;
			if (new.err2 > -new.dx)
			{
				new.err -= new.dy;
				new.x1 += new.sx;
			}
			if (new.err2 < new.dy)
			{
				new.err += new.dx;
				new.y1 += new.sy;
			}
		}
		


		tab[(((*begin)->y + 1) * sizeline) + (((*begin)->x + 1) * (bpp / 8))] = (*begin)->c << 16 >> 16;
		tab[(((*begin)->y + 1) * sizeline) + (((*begin)->x + 1) * (bpp / 8)) + 1] = (*begin)->c << 8 >> 16;
		tab[(((*begin)->y + 1) * sizeline) + (((*begin)->x + 1) * (bpp / 8)) + 2] = (*begin)->c >> 16;

		tab[(((*begin)->y + 1) * sizeline) + ((*begin)->x * (bpp / 8))] = (*begin)->c << 16 >> 16;
		tab[(((*begin)->y + 1) * sizeline) + ((*begin)->x * (bpp / 8)) + 1] = (*begin)->c << 8 >> 16;
		tab[(((*begin)->y + 1) * sizeline) + ((*begin)->x * (bpp / 8)) + 2] = (*begin)->c >> 16;

		tab[((*begin)->y * sizeline) + (((*begin)->x + 1) * (bpp / 8))] = (*begin)->c << 16 >> 16;
		tab[((*begin)->y * sizeline) + (((*begin)->x + 1) * (bpp / 8)) + 1] = (*begin)->c << 8 >> 16;
		tab[((*begin)->y * sizeline) + (((*begin)->x + 1) * (bpp / 8)) + 2] = (*begin)->c >> 16;
		begin++;
	}
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

	index = 0;
	if (argc > 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (-1);
		get_line_and_len(fd, &test);
		retoftest = test_valid(&numlines, &numinline, test);
		ft_putnbr(retoftest);
		new = make_table(test, numlines, numinline);
		mlxinit = mlx_init();
		mlximg1 = mlx_new_image(mlxinit, 1920, 1080);
		window1 = mlx_new_window(mlxinit ,1920, 1080, "fdf");
		ft_printf("up tpo here ok?");
		mlxret = mlx_get_data_addr(mlximg1, &bpp, &sizeline, &endian);
		new = iso_view(new, numinline, numlines);
		handle_ret(mlxret, new, sizeline, bpp);
		mlx_put_image_to_window(mlxinit, window1, mlximg1, 0, 0);
		mlx_loop(mlxinit);
	}
}
