/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 10:55:48 by guiricha          #+#    #+#             */
/*   Updated: 2016/09/08 18:16:12 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

int			better_key_func(int keycode, t_init *param)
{
	t_init *n;

	n = param;
	if ((keycode) == 126)
		n->zrate += 0.3;
	if (keycode == 125)
		n->zrate -= 0.3;
	if (keycode == 123)
		n->spread-= 2;
	if (keycode == 124)
		n->spread += 2;
	if (keycode == 27)
		n->pitch = n->pitch - 1 == 0 ? n->pitch - 2 : n->pitch - 1;
	if (keycode == 24)
		n->pitch = n->pitch + 1 == 0 ? n->pitch + 2 : n->pitch + 1;
	n->npoint = NULL;
	n->npoint = make_table(n->parsed, n);
	calc_z(n->npoint, n);
	n->npoint = n->left ? iso_view_left(n->npoint, n) : iso_view(n->npoint, n);
	n->npoint = offset(n->npoint, n);
	bzero(n->imagestr, n->sl * n->wheight);
	draw_pixels(n->imagestr, n->npoint, n);
	mlx_put_image_to_window(n->init, n->window, n->image, 0, 0);
	if ((keycode) == 53)
		exit(EXIT_SUCCESS);
	draw_pixels(n->imagestr, n->npoint, n);
	return (0);
}
