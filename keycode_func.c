/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 10:55:48 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/12 10:56:17 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int			my_key_func(int keycode, void *param)
{
	param = &keycode;
	if ((keycode) == 53)
		exit(EXIT_SUCCESS);
	return (0);
}
