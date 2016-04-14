/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/08 14:38:34 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/12 15:14:52 by guiricha         ###   ########.fr       */
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
	else if (!strncmp(current, "force:\0", 6))
		n->force = ft_atoi_hex(current + 6);
	else if (!strncmp(current, "iso:1\0", 5))
		n->left = 1;
	else if (!strncmp(current, "help\0", 4))
	{
		ft_putstr("LIST OF COMMANDS:\ncolorzero:hex\nrand:hex\nforce:hex\n");
		ft_putstr("thick:0-1\npitch:2to6\nspread:dec\nwHeight:dec\nwWidth:dec");
		ft_putstr("\nzrate:-9to9\n");
		ft_putstr("iso:1 == left -> right\n");
		ft_putstr("iso:0 == bottom -> top\n");
	}
}

void	apply_args(int argc, char **argv, t_init *n)
{
	int	i;

	i = 2;
	while (argc > 2)
	{
		if (!strncmp(argv[i], "wHeight:\0", 8))
			n->wheight = ft_atoi(argv[i] + 8);
		else if (!strncmp(argv[i], "wWidth:\0", 7))
			n->wwidth = ft_atoi(argv[i] + 7);
		else if (!strncmp(argv[i], "spread:\0", 7))
			n->spread = ft_atoi(argv[i] + 7);
		else if (!strncmp(argv[i], "zrate:\0", 6))
			n->zrate = ft_atoi(argv[i] + 6);
		apply_args_ext(argv[i], n);
		argc--;
		i++;
	}
	n->pitch = n->pitch <= 6 && n->pitch > 1 ? n->pitch + 1 : 2;
	n->wwidth = n->wwidth >= 25 && n->wwidth <= 1920 ? n->wwidth : 500;
	n->wheight = n->wheight >= 25 && n->wheight <= 1080 ? n->wheight : 500;
	n->zrate = n->zrate != 0 && n->zrate <= 9 && n->zrate >= -9 ? n->zrate : 1;
	n->spread = n->spread >= 1 && n->spread < 1920 ? n->spread : 50;
	n->colorz = n->colorz >= 0 || n->colorz <= 0xffffff ? n->colorz : 0x888888;
}
