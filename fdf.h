/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiricha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:14:51 by guiricha          #+#    #+#             */
/*   Updated: 2016/04/09 11:44:45 by guiricha         ###   ########.fr       */
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
	int	red;
	int	grn;
	int	blu;
	int			count;

}				t_grade;

typedef struct	s_init
{
	void		*init;
	void		*window;
	void		*image;
	char		*imagestr;
	int			i;
	int			x;
	int			y;
	int			xbck;
	int			ybck;
	int			pitch;
	int			spread;
	int			wWidth;
	int			wHeight;
	int			var1;
	int			var2;
	int			colorz;
	int			bpp;
	int			sl;
	int			pxdst;
	int			zrate;
	int			zlow;
	int			zhigh;
	int			rand;
	char		thick;
	char		*parsed;
	int			force;

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
	int			ldx;
	int			ldy;
	char		dnd;
}				t_point;

int				calc_z(t_point **s, t_init *d);
void			apply_args(int argc, char **argv, t_init *n);
void			apply_args_ext(char *current, t_init *n);
void			init_new(t_line *new, t_point **begin, t_point *end);
int				init_init(t_init **n);
void			draw_pixels(char *tab, t_point **begin, t_init *n);
int				ft_is_hex(char c);
int				ft_atoi_hex(const char *str);
t_point			*test_points(char *points);
t_point			*init_point(int x, int y, int z);
int				get_line_and_len(int fd, char **into);
int				test_valid(char *points, t_init *n);
t_point			**make_table(char *s, t_init *d);
int				init_start_object(t_point **object);

#endif
