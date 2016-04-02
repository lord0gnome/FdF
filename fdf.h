/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:14:51 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/02 18:51:43 by guiricha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H
# include "libft/libft.h"
# include "GNL/get_next_line.h"
# include <mlx.h>
# include <stdlib.h>
# include "ft_printf/ft_printf.h"
# include <fcntl.h>
# include <math.h>
# include "minilibx_macos/mlx.h"

typedef struct	s_grade
{
	int			colortodraw;
	unsigned char		r;	
	unsigned char		g;
	unsigned char		b;
	unsigned char	red;
	unsigned char	grn;
	unsigned char	blu;
	int			count;

}				t_grade;

typedef struct	s_init
{
	int			i;
	int			x;
	int			y;
	int			xbck;
	int			ybck;
	int			pitch;
	int			spread;
	int			wWidth;
	int			wHeight;
	int			zmax;
	int			zmin;
	int			bpp;
	int			sl;
	int			pxdst;
}				t_init;

typedef struct	s_line
{
	int	sx;
	int	sy;
	int	dx;
	int	dy;
	int x1;
	int x2;
	int y1;
	int y2;
	int	err;
	int	err2;
}				t_line;

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int			c;
	int			ld;
}				t_point;

void			draw_pixels(char *tab, t_point **begin, t_init *n);
int				ft_is_hex(char c);
int				ft_atoi_hex(const char *str);
t_point			*test_points(char *points);
t_point			*init_point(int x, int y, int z);
int				get_line_and_len(int fd, char **into);
int				test_valid(char *points, t_init *n);
t_point			**make_table(char *s, t_init *d);

#endif
