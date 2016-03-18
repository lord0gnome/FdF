/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 11:17:55 by guiricha          #+#    #+#             */
/*   Updated: 2016/03/18 18:57:07 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "fdf.h"
#include <fcntl.h>
#include <stdlib.h>
/*
void	handle_ret(char *tab, int sizeline, int bpp, t_point c)
{
		tab[(c.y * sizeline) + (c.x * (bpp / 8))] = 0xff;
		tab[(c.y * sizeline) + (c.x * (bpp / 8)) + 1] = 0xff;
		tab[(c.y * sizeline) + (c.x * (bpp / 8)) + 2] = 0xff;
}
*/



int	main(int argc, char **argv)
{
	void	*mlxinit;
	void	*window1;
	void	*mlximg1;
	char	*mlxret;
	int		fd;
	int		bpp;
	int		sizeline;
	int		endian;



	if (argc > 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (-1);
		mlxinit = mlx_init();
		mlximg1 = mlx_new_image(mlxinit, 1024, 768);
		window1 = mlx_new_window(mlxinit ,1024, 768, "fdf");
		mlxret = mlx_get_data_addr(mlximg1, &bpp, &sizeline, &endian);
		mlx_put_image_to_window(mlxinit, window1, mlximg1, 0, 0);
		mlx_loop(mlxinit);
	}
}
