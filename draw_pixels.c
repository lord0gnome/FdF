/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 10:54:33 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/05 15:07:00 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_grade	draw_line_color(t_point *p1, t_point *p2)
{
	int		c1;
	int		c2;
	t_grade	m;

	c1 = p1->c;
	c2 = p2->c;
	m.red = (((c1 & 0xff0000) - ((c2) & 0xff0000)) >> 16);
	m.grn = (((c1 & 0x00ff00) - ((c2) & 0x00ff00)) >> 8);
	m.blu = (((c1 & 0x0000ff) - ((c2) & 0x0000ff)));
	m.r = (unsigned char)(c1 >> 16);
	m.b = (unsigned char)(c1);
	m.g = ((unsigned char)(c1 >> 8));
	return (m);
}

void	init_new(t_line *new, t_point **begin, t_point *end)
{
		new->x1 = (*(begin))->x;
		new->x2 = ((end))->x;
		new->y1 = (*(begin))->y;
		new->y2 = (end)->y;
		new->dx = abs(new->x2 - new->x1);
		new->sx = new->x1 < new->x2 ? 1 : -1;
		new->dy = abs(new->y2 - new->y1);
		new->sy = new->y1 < new->y2 ? 1 : -1;
		new->err = (new->dx > new->dy ? new->dx : -new->dy) / 2;
}

int		try_line_x(char *tab, t_init *d, t_point **begin, t_point *end)
{
	t_grade	m;
	t_grade mt;
	t_line	new;

	if ((*begin) && end)
	{
		init_new(&new, begin, end);
/*		new.x1 = (*(begin))->x;
		new.x2 = ((end))->x;
		new.y1 = (*(begin))->y;
		new.y2 = (end)->y;
		new.dx = abs(new.x2 - new.x1);
		new.sx = new.x1 < new.x2 ? 1 : -1;
		new.dy = abs(new.y2 - new.y1);
		new.sy = new.y1 < new.y2 ? 1 : -1;
		new.err = (new.dx > new.dy ? new.dx : -new.dy) / 2;*/
		d->pxdst = new.dx > new.dy ? new.dx : new.dy;
		m = draw_line_color((*begin), (end));
		m.count = 0;
		while (42)
		{
			if (d->pxdst != 0)
			{
				mt.g = m.g - m.grn * m.count / d->pxdst;
				mt.r = m.r - m.red * m.count / d->pxdst;
				mt.b = m.b - m.blu * m.count / d->pxdst;
			}
			tab[(new.y1 * d->sl) + (new.x1 * (d->bpp / 8)) + 2] = mt.r;
			tab[((new.y1 * d->sl) + (new.x1 * (d->bpp / 8))) + 1] = mt.g;
			tab[((new.y1 * d->sl) + (new.x1 * (d->bpp / 8))) + 0] = mt.b;
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
			m.count++;
		}
	}
	else
		return (0);
	return (1);
}
void	draw_pixels(char *tab, t_point **begin, t_init *d)
{
	d->x = 0;
	d->y = 0;
	//	ft_printf("xbck%d ybck%d\n", d->xbck, d->ybck);
	while (d->y < d->ybck)
	{
		d->x = 0;
		while ((*begin) && d->x < d->xbck)
		{
			if (d->x < d->xbck - 1 && d->x != d->xbck)
				try_line_x(tab, d, begin, (*(begin + 1)));
			else if (d->x != 0)
				try_line_x(tab, d, begin, (*(begin - 1)));
			if (d->y < d->ybck - 1 && d->y != d->ybck)
				try_line_x(tab, d, begin, (*(begin + d->xbck)));
			else if (d->y != 0)
				try_line_x(tab, d, begin, (*(begin - d->xbck)));
			d->x++;
			begin++;
		}
		d->y++;
	}
}
/*
   tab[((new.y1 + 1) * d->sl) + (new.x1 * (d->bpp / 8)) + 2] = mt.r;
   tab[((new.y1 + 1) * d->sl) + (new.x1 * (d->bpp / 8)) + 1] = mt.g;
   tab[(((new.y1 + 1) * d->sl) + (new.x1 * (d->bpp / 8))) + 0] = mt.b;
   tab[((new.y1 + 1) * d->sl) + ((new.x1 + 1) * (d->bpp / 8)) + 2] = mt.r;
   tab[((new.y1 + 1) * d->sl) + ((new.x1 + 1) * (d->bpp / 8)) + 1] = mt.g;
   tab[(((new.y1 + 1) * d->sl) + ((new.x1 + 1) * (d->bpp / 8))) + 0] = mt.b;
   tab[((new.y1) * d->sl) + ((new.x1 + 1) * (d->bpp / 8)) + 2] = mt.r;
   tab[((new.y1) * d->sl) + ((new.x1 + 1) * (d->bpp / 8)) + 1] = mt.g;
   tab[(((new.y1) * d->sl) + ((new.x1 + 1) * (d->bpp / 8))) + 0] = mt.b;*/
