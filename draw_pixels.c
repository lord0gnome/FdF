/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 10:54:33 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/03 20:59:54 by guiricha         ###   ########.fr       */
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
//	ft_printf("%d %d %d\n", m.red, m.grn, m.blu);
	m.r = (unsigned char)(c1 >> 16);
	m.b = (unsigned char)(c1);
	m.g = ((unsigned char)(c1 >> 8));
	return (m);
}

int		try_line_x(char *tab, t_init *d, t_point **begin, t_point *end)
{
	t_grade	m;
	t_grade mt;
	t_line	new;

	if ((*begin) && end)
	{
		new.x1 = (*(begin))->x;
		new.x2 = ((end))->x;
		new.y1 = (*(begin))->y;
		new.y2 = (end)->y;
		new.dx = abs(new.x2 - new.x1);
		new.sx = new.x1 < new.x2 ? 1 : -1;
		new.dy = abs(new.y2 - new.y1);
		new.sy = new.y1 < new.y2 ? 1 : -1;
		new.err = (new.dx > new.dy ? new.dx : -new.dy) / 2;
		d->pxdst = new.dx > new.dy ? new.dx : new.dy;
		m = draw_line_color((*begin), (end));
		m.count = 0;
		while (42)
		{
			if (d->pxdst != 0)
			{
				mt.g = m.g - m.grn * m.count / d->pxdst; // color to draw = c1 - (colordiff) * current pixel / totalpixels
				mt.r = m.r - m.red * m.count / d->pxdst; // color to draw = c1 - (colordiff) * current pixel / totalpixels
				mt.b = m.b - m.blu * m.count / d->pxdst; // color to draw = c1 - (colordiff) * current pixel / totalpixels
			}
			tab[(new.y1 * d->sl) + (new.x1 * (d->bpp / 8)) + 2] = mt.r;
			tab[((new.y1 * d->sl) + (new.x1 * (d->bpp / 8))) + 1] = mt.g;
			tab[((new.y1 * d->sl) + (new.x1 * (d->bpp / 8))) + 0] = mt.b;
			tab[((new.y1 + 1) * d->sl) + (new.x1 * (d->bpp / 8)) + 2] = mt.r;
			tab[((new.y1 + 1) * d->sl) + (new.x1 * (d->bpp / 8)) + 1] = mt.g;
			tab[(((new.y1 + 1) * d->sl) + (new.x1 * (d->bpp / 8))) + 0] = mt.b;
			tab[((new.y1 + 1) * d->sl) + ((new.x1 + 1) * (d->bpp / 8)) + 2] = mt.r;
			tab[((new.y1 + 1) * d->sl) + ((new.x1 + 1) * (d->bpp / 8)) + 1] = mt.g;
			tab[(((new.y1 + 1) * d->sl) + ((new.x1 + 1) * (d->bpp / 8))) + 0] = mt.b;
			tab[((new.y1) * d->sl) + ((new.x1 + 1) * (d->bpp / 8)) + 2] = mt.r;
			tab[((new.y1) * d->sl) + ((new.x1 + 1) * (d->bpp / 8)) + 1] = mt.g;
			tab[(((new.y1) * d->sl) + ((new.x1 + 1) * (d->bpp / 8))) + 0] = mt.b;
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
	ft_printf("xbck%d ybck%d\n", d->xbck, d->ybck);
	while (d->y < d->ybck)
	{
		d->x = 0;
		while (d->x < d->xbck)
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


	/*tab[(((*begin)->y * d->sl) + ((*begin)->x * (d->bpp / 8)))] = (*begin)->c << 16 >> 16;
	  tab[(((*begin)->y * d->sl) + ((*begin)->x * (d->bpp / 8))) + 1] = (*begin)->c << 8 >> 16;
	  tab[(((*begin)->y * d->sl) + ((*begin)->x * (d->bpp / 8))) + 2] = (*begin)->c >> 16;*/
	/*if ((*(begin + 1)) && d->x != 1)
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
	  d->pxdst = new.dx > new.dy ? new.dx : new.dy;
	  m = draw_line_color((*begin), *(begin + 1));
	  m.count = 0;
	  while (42)
	  {
	  if (d->pxdst != 0)
	  {
	  mt.g = m.g - m.grn * m.count / d->pxdst;
	//ft_printf("m.g :[%d] m.grn :[%d], calculation of - :[%d]\n", m.g, m.grn, (m.grn * m.count) / d->pxdst);
	mt.r = m.r - m.red * m.count / d->pxdst;
	//ft_printf("m.r :[%d] m.red :[%d], calculation of - :[%d]\n", m.r, m.red, (m.red * m.count) / d->pxdst);
	mt.b = m.b - m.blu * m.count / d->pxdst;
	//ft_printf("m.b :[%d] m.blu :[%d], calculation of - :[%d]\n", m.b, m.blu, (m.blu * m.count) / d->pxdst);
	ft_printf("%hhu %hhu %hhu\n", mt.r, mt.g, mt.b);
	}
	tmpcolor = m.r << 16;
	tmpcolor |= (m.g << 8);
	tmpcolor |= m.b;
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
	}*/
	/*	if (*(begin - 1) && d->x != d->xbck && (*(begin - 1))->ld != 1)
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
		}*/
	/*		else if (*(begin - d->xbck) && (*(begin - d->xbck))->ld != 1)
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
			}*/
	/*	if (*(begin + d->xbck))
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
		}*/
