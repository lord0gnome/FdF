/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/08 14:38:34 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/09 10:35:54 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_args_ext(char *current, t_init *n)
{
	if (!strncmp(current, "colorzero:\0", 10))
		n->colorz = ft_atoi_hex(current + 10);
	else if (!strncmp(current, "rand:\0", 5))
		n->rand = ft_atoi_hex(current + 5);
	else if (!strncmp(current, "thick:\0", 6))
		n->thick = ft_atoi_hex(current + 6);
	else if (!strncmp(current, "pitch:\0", 6))
		n->pitch = ft_atoi_hex(current + 6);
	else if (!strncmp(current, "forcecolor:\0", 11))
		n->force = ft_atoi_hex(current + 11);
}

void	apply_args(int argc, char **argv, t_init *n)
{
	int	i;

	i = 2;
	while (argc > 2)
	{
		if (!strncmp(argv[i], "wHeight:\0", 8))
			n->wHeight = ft_atoi(argv[i] + 8);
		else if (!strncmp(argv[i], "wWidth:\0", 7))
			n->wWidth = ft_atoi(argv[i] + 7);
		else if (!strncmp(argv[i], "spread:\0", 7))
			n->spread = ft_atoi(argv[i] + 7);
		else if (!strncmp(argv[i], "zrate:\0", 6))
			n->zrate = ft_atoi(argv[i] + 6);
		apply_args_ext(argv[i], n);
		argc--;
		i++;
	}
	n->pitch = n->pitch <= 6 && n->pitch > 1 ? n->pitch + 1 : 2;
	n->wWidth = n->wWidth >= 25 && n->wWidth <= 1920 ? n->wWidth : 500;
	n->wHeight = n->wHeight >= 25 && n->wHeight <= 1080 ? n->wHeight : 500;
	n->zrate = n->zrate != 0 && n->zrate <= 9 && n->zrate >= -9 ? n->zrate : 1;
	n->spread = n->spread >= 1 && n->spread < 1920 ? n->spread : 50;
	n->colorz = n->colorz >= 0 || n->colorz <= 0xffffff ? n->colorz : 0x888888;
}
