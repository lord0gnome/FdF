/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 13:51:19 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/12 11:17:23 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			ft_atoi_hex(const char *str)
{
	long	result;

	result = 0;
	if (*str == ',')
		str += 3;
	while (*str != '\0' && ((*str >= '0' && *str <= '9') || ft_is_hex(*str)))
	{
		if ((ft_is_hex(*str) == 2))
			result = result * 16 + (*str - (55));
		else if ((ft_is_hex(*str) == 1))
			result = result * 16 + (*str - (87));
		else if (*str >= '0' && *str <= '9')
			result = result * 16 + (*str - '0');
		str++;
	}
	return ((int)(result));
}
