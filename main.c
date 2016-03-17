/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 11:17:55 by guiricha          #+#    #+#             */
/*   Updated: 2016/03/17 16:12:21 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "fdf.h"
#include <fcntl.h>
#include <stdlib.h>

void	handle_ret(char *tab, int sizeline, int bpp, t_point c)
{
	int n;

	n = 750;

	while (n--)
	{
		tab[(c.y * sizeline) + (c.x * 4)] = (char)c.c;
		tab[(c.y * sizeline) + (c.x * 4) + 1] = (char)c.c >> 8;
		tab[(c.y * sizeline) + (c.x * 4) + 2] = (char)c.c >> 16;
	}
	n = bpp;
}




int	main(int argc, char **argv)
{
	void	*mlxinit;
	void	*window1;
	void	*mlximg1;
	char	*mlxret;
	int		fd;
	t_point *new;
	int		bpp;
	int		sizeline;
	int		endian;



	if (argc > 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (-1);
		new = test_points(fd);
		mlxinit = mlx_init();
		mlximg1 = mlx_new_image(mlxinit, 1024, 768);
		window1 = mlx_new_window(mlxinit ,1024, 768, "fdf");
		mlxret = mlx_get_data_addr(mlximg1, &bpp, &sizeline, &endian);
		handle_ret(mlxret, sizeline, bpp);
		mlx_put_image_to_window(mlxinit, window1, mlximg1, 0, 0);
		mlx_loop(mlxinit);
	}
}
