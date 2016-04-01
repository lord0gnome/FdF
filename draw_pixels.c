/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 10:54:33 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/01 15:34:42 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	draw_line_color(t_point *p1, t_point *p2, t_init *d)
{
	int		c1;
	int		c2;
	int		retcolor;
	unsigned char	red;
	unsigned char	grn;
	unsigned char	blu;
	int		pxdst;

	pxdst = d->pxdst;
	c1 = p1->c;
	c2 = p2->c;
	retcolor = 0;
	red = abs((c1 >> 16) - (c2 >> 16));
	c1 = p1->c;
	c2 = p2->c;
	grn = abs(((c1 <<  8) >> 16) - ((c2 << 8) >> 16));
	c1 = p1->c;
	c2 = p2->c;
	blu = abs(((c1 << 16) >> 16) - ((c2 << 16) >> 16));
	ft_printf("red : %hhu green : %hhu blue : %hhu\n", red, grn, blu);
	ft_printf("original colors as ints 1[%d] 2[%d]\n", p1->c, p2->c);
	return (42);

}

void	draw_pixels(char *tab, t_point **begin, t_init *d)
{
	t_line	new;
	t_line	n;
	int		tmpcolor;

	d->x = d->xbck;
	while (*(begin))
	{
		/*tab[(((*begin)->y * d->sl) + ((*begin)->x * (d->bpp / 8)))] = (*begin)->c << 16 >> 16;
		  tab[(((*begin)->y * d->sl) + ((*begin)->x * (d->bpp / 8))) + 1] = (*begin)->c << 8 >> 16;
		  tab[(((*begin)->y * d->sl) + ((*begin)->x * (d->bpp / 8))) + 2] = (*begin)->c >> 16;*/
		if ((*(begin + 1)) && d->x != 1)
		{
				new.x1 = (*begin)->x;
				new.x2 = (*(begin + 1))->x;
				new.y1 = (*begin)->y;
				new.y2 = (*(begin + 1))->y;
				new.dx = abs(new.x2 - new.x1);
				new.sx = new.x1 < new.x2 ? 1 : -1;
				new.dy = abs(new.y2 - new.y1);
				d->pxdst = sqrt((new.dx * new.dx) + (new.dy * new.dy));
				new.sy = new.y1 < new.y2 ? 1 : -1;
				new.err = (new.dx > new.dy ? new.dx : -new.dy) / 2;
				while (42)
				{
					tmpcolor = draw_line_color((*begin), *(begin + 1), d);
					tab[(new.y1 * d->sl) + (new.x1 * (d->bpp / 8))] = (*begin)->c << 16 >> 16;
					tab[((new.y1 * d->sl) + (new.x1 * (d->bpp / 8))) + 1] = (*begin)->c << 8 >> 16;
					tab[((new.y1 * d->sl) + (new.x1 * (d->bpp / 8))) + 2] = (*begin)->c >> 16;
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
				if (*(begin - 1) && d->x != d->xbck && (*(begin - 1))->ld != 1)
				{
					new.x1 = (*begin)->x;
					new.x2 = (*(begin - 1))->x;
					new.y1 = (*begin)->y;
					new.y2 = (*(begin - 1))->y;
					new.dx = abs(new.x2 - new.x1);
					new.sx = new.x1 < new.x2 ? 1 : -1;
					new.dy = abs(new.y2 - new.y1);
					new.sy = new.y1 < new.y2 ? 1 : -1;
					new.err = (new.dx > new.dy ? new.dx : -new.dy) / 2;
					while (42)
					{
						tab[(new.y1 * d->sl) + (new.x1 * (d->bpp / 8))] = (*begin)->c << 16 >> 16;
						tab[((new.y1 * d->sl) + (new.x1 * (d->bpp / 8))) + 1] = (*begin)->c << 8 >> 16;
						tab[((new.y1 * d->sl) + (new.x1 * (d->bpp / 8))) + 2] = (*begin)->c >> 16;
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
				if (*(begin - d->xbck) && (*(begin - d->xbck))->ld != 1)
				{
					n.x1 = (*begin)->x;
					n.x2 = (*(begin - d->xbck))->x;
					n.y1 = (*begin)->y;
					n.y2 = (*(begin - d->xbck))->y;
					n.dx = abs(n.x2 - n.x1);
					n.sx = n.x1 < n.x2 ? 1 : -1;
					n.dy = abs(n.y2 - n.y1);
					n.sy = n.y1 < n.y2 ? 1 : -1;
					n.err = (n.dx > n.dy ? n.dx : -n.dy) / 2;
					while (42)
					{
						tab[(n.y1 * d->sl) + (n.x1 * (d->bpp / 8))] = (*begin)->c << 16 >> 16;
						tab[((n.y1 * d->sl) + (n.x1 * (d->bpp / 8))) + 1] = (*begin)->c << 8 >> 16;
						tab[((n.y1 * d->sl) + (n.x1 * (d->bpp / 8))) + 2] = (*begin)->c >> 16;
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
				if (*(begin + d->xbck))
				{
					n.x1 = (*begin)->x;
					n.x2 = (*(begin + d->xbck))->x;
					n.y1 = (*begin)->y;
					n.y2 = (*(begin + d->xbck))->y;
					n.dx = abs(n.x2 - n.x1);
					n.sx = n.x1 < n.x2 ? 1 : -1;
					n.dy = abs(n.y2 - n.y1);
					n.sy = n.y1 < n.y2 ? 1 : -1;
					n.err = (n.dx > n.dy ? n.dx : -n.dy) / 2;
					while (42)
					{
						tab[(n.y1 * d->sl) + (n.x1 * (d->bpp / 8))] = (*begin)->c << 16 >> 16;
						tab[((n.y1 * d->sl) + (n.x1 * (d->bpp / 8))) + 1] = (*begin)->c << 8 >> 16;
						tab[((n.y1 * d->sl) + (n.x1 * (d->bpp / 8))) + 2] = (*begin)->c >> 16;
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
				d->x--;
				if (d->x == 0)
					d->x = d->xbck;
			(*begin)->ld = 1;	
			begin++;
		}
	}
