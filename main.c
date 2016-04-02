/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 11:17:55 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/02 18:11:58 by guiricha         ###   ########.fr       */
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
	if (*start)
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
	ft_printf("xlow%d ylow%d", xlow, ylow);
	while (*start)
	{
		(*start)->y += abs(ylow) + 25;
		(*start)->x += abs(xlow) + 25;
		start++;
		/*	if ((*start)->y < 0)
			(*start)->y = 0;
			if ((*start)->x < 0)
			(*start)->x = 0;
			if ((*start)->y > 1080)
			(*start)->y = 1050;
			if ((*start)->x > 1920)
			(*start)->x = 1870;*/

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
			(*start)->y -= (*start)->z * 2;
		start++;
	}
	return (bck);
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
	index = 0;
	n->spread = 900;
	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			return (-1);
		get_line_and_len(fd, &test);
		retoftest = test_valid(test, n);
		numlines = n->y;
		numinline = n->x;
		ft_putnbr(retoftest);
		if (!(new = make_table(test, n)))
			return (-1);
		mlxinit = mlx_init();
		mlximg1 = mlx_new_image(mlxinit, 1920, 1080);
		window1 = mlx_new_window(mlxinit ,1920, 1080, "fdf");
		new = iso_view(new);
		new = offset(new);
		mlxret = mlx_get_data_addr(mlximg1, &bpp, &sizeline, &endian);
		n->bpp = bpp;
		n->sl = sizeline;
		draw_pixels(mlxret, new, n);
		mlx_put_image_to_window(mlxinit, window1, mlximg1, 0, 0);
		mlx_loop(mlxinit);
	}
}

/*void	handle_ret(char *tab, t_point **begin, int sizeline, int bpp, int numinline)
  {
  t_line new;
  t_line n;
  int	nilbck;
  ft_printf("sizeline : %d, bpp : %d\n", sizeline, bpp);
  nilbck = numinline;
  while (*(begin + 1))
  {
  tab[(((*begin)->y * sizeline) + ((*begin)->x * (bpp / 8)))] = (*begin)->c << 16 >> 16;
  tab[(((*begin)->y * sizeline) + ((*begin)->x * (bpp / 8))) + 1] = (*begin)->c << 8 >> 16;
  tab[(((*begin)->y * sizeline) + ((*begin)->x * (bpp / 8))) + 2] = (*begin)->c >> 16;
  if (*(begin + 1))
  {
  if (numinline != 1)
  {
  new.x1 = (*begin)->x;
  new.x2 = (*(begin + 1))->x;
  new.y1 = (*begin)->y;
  new.y2 = (*(begin + 1))->y;
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
  if ((new.y1 == new.y2 && new.x1 == new.x2) || !new.x2 || !new.y2)
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
  }
  if (*(begin + nilbck))
  {
  n.x1 = (*begin)->x;
  n.x2 = (*(begin + nilbck))->x;
  n.y1 = (*begin)->y;
  n.y2 = (*(begin + nilbck))->y;
  n.dx = abs(n.x2 - n.x1);
  n.sx = n.x1 < n.x2 ? 1 : -1;
  n.dy = abs(n.y2 - n.y1);
  n.sy = n.y1 < n.y2 ? 1 : -1;
  n.err = (n.dx > n.dy ? n.dx : -n.dy) / 2;
  while (42)
  {
  tab[(n.y1 * sizeline) + (n.x1 * (bpp / 8))] = (*begin)->c << 16 >> 16;
  tab[((n.y1 * sizeline) + (n.x1 * (bpp / 8))) + 1] = (*begin)->c << 8 >> 16;
  tab[((n.y1 * sizeline) + (n.x1 * (bpp / 8))) + 2] = (*begin)->c >> 16;
  if ((n.y1 == n.y2 && n.x1 == n.x2) || !n.x2 || !n.y2)
  break;
  n.err2 = n.err;
  if (n.err2 > -n.dx)
  {
  n.err -= n.dy;
  n.x1 += n.sx;
  }
  if (n.err2 < n.dy)
  {
n.err += n.dx;
n.y1 += n.sy;
}
}
}
if (numinline == 0)
	numinline = nilbck;
	numinline--;
	}
begin++;
}
}
*/
