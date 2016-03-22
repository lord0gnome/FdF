/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 11:17:55 by guiricha          #+#    #+#             */
/*   Updated: 2016/03/22 15:14:58 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "fdf.h"
#include <stdlib.h>

static void	handle_ret(char *tab, t_point **begin, int sizeline, int bpp)
{
	ft_printf("sizeline : %d, bpp : %d\n", sizeline, bpp);
	while (*begin)
	{
		tab[((*begin)->y * sizeline) + ((*begin)->x * (bpp / 8))] = (char)(*begin)->c;
		tab[(((*begin)->y * sizeline) + ((*begin)->x * (bpp / 8))) + 1] = (char)(*begin)->c;
		tab[(((*begin)->y * sizeline) + ((*begin)->x * (bpp / 8))) + 2] = (char)(*begin)->c;

		tab[(((*begin)->y + 1) * sizeline) + (((*begin)->x + 1) * (bpp / 8))] = (char)(*begin)->c;
		tab[(((*begin)->y + 1) * sizeline) + (((*begin)->x + 1) * (bpp / 8)) + 1] = (char)(*begin)->c;
		tab[(((*begin)->y + 1) * sizeline) + (((*begin)->x + 1) * (bpp / 8)) + 2] = (char)(*begin)->c;

		tab[(((*begin)->y + 1) * sizeline) + ((*begin)->x * (bpp / 8))] = (char)(*begin)->c;
		tab[(((*begin)->y + 1) * sizeline) + ((*begin)->x * (bpp / 8)) + 1] = (char)(*begin)->c;
		tab[(((*begin)->y + 1) * sizeline) + ((*begin)->x * (bpp / 8)) + 2] = (char)(*begin)->c;

		tab[((*begin)->y * sizeline) + (((*begin)->x + 1) * (bpp / 8))] = (char)(*begin)->c;
		tab[((*begin)->y * sizeline) + (((*begin)->x + 1) * (bpp / 8)) + 1] = (char)(*begin)->c;
		tab[((*begin)->y * sizeline) + (((*begin)->x + 1) * (bpp / 8)) + 2] = (char)(*begin)->c;
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
		mlxret = mlx_get_data_addr(mlximg1, &bpp, &sizeline, &endian);
		handle_ret(mlxret, new, sizeline, bpp);
		mlx_put_image_to_window(mlxinit, window1, mlximg1, 0, 0);
		mlx_loop(mlxinit);
	}
}
