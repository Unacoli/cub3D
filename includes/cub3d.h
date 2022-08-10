/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:20:51 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/10 02:09:04 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <libft.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "mlx.h"

typedef struct s_pos
{
	int		x;
	int		y;
	char	facing;
}	t_pos;

typedef struct s_parsing
{
	t_list	*map;
}	t_parsing;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	o;
}	t_color;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			height;
	int			width;
	void		*img;
	t_pos		player;
	t_pos		map_size;
	t_color		*draw;
	t_parsing	*pars;
}	t_data;

#endif