/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/08 14:25:05 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/08 16:46:37 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int		init_init(t_init **n)
{
	(*n) = (t_init *)malloc(sizeof(t_init));
	if ((*n) == NULL)
		return (0);
	(*n)->i = 0;
	(*n)->x = 0;
	(*n)->y = 0;
	(*n)->xbck = 0;
	(*n)->ybck = 0;
	(*n)->spread = 80;
	(*n)->wWidth = 1920;
	(*n)->wHeight = 1080;
	(*n)->var1 = 0;
	(*n)->var2 = 0;
	(*n)->colorz = -1;
	(*n)->bpp = 0;
	(*n)->sl = 0;
	(*n)->pxdst = 0;
	(*n)->zrate = 1;
	(*n)->rand = 0;
	(*n)->thick = 0;
	(*n)->xoffset = 0;
	(*n)->yoffset = 0;
	return (1);
}

void	init_start_object(t_point **object)
{
	((*object) = (t_point *)malloc(sizeof(t_point)));
	(*object)->x = 0;
	(*object)->y = 0;
	(*object)->z = 0;
	(*object)->c = 0;
	(*object)->ldx = 0;
	(*object)->ldy = 0;
}
