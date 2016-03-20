/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 11:17:55 by guiricha          #+#    #+#             */
/*   Updated: 2016/03/20 21:12:14 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "fdf.h"
#include <stdlib.h>

static void	handle_ret(char *tab, t_point **begin, int sizeline, int bpp)
{
	while (*begin)
	{
		tab[((*begin)->y * sizeline) + ((*begin)->x * (bpp / 8))] = 0xff;
		tab[((*begin)->y * sizeline) + ((*begin)->x * (bpp / 8)) + 1] = 0xff;
		tab[((*begin)->y * sizeline) + ((*begin)->x * (bpp / 8)) + 2] = 0xff;
		tab += 4;
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


	if (argc > 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (-1);
		ft_putnbr(get_line_and_len(fd, &test));
		retoftest = test_valid(&numlines, &numinline, test);
		new = make_table(test, numlines, numinline);
		ft_printf("X,Y,Z = (%d|%d|%d)\n", (*new)->x, (*new)->y, (*new)->z);
		mlxinit = mlx_init();
		mlximg1 = mlx_new_image(mlxinit, 1024, 768);
		window1 = mlx_new_window(mlxinit ,1024, 768, "fdf");
		mlxret = mlx_get_data_addr(mlximg1, &bpp, &sizeline, &endian);
		handle_ret(mlxret, new, sizeline, bpp);
		mlx_put_image_to_window(mlxinit, window1, mlximg1, 0, 0);
		mlx_loop(mlxinit);
	}
}
