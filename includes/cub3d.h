/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:20:51 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/11 00:28:18 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	o;
}	t_color;

typedef struct s_elem
{
	char	elem;
	char	facing;
	char	*texture;
}	t_elem;

typedef struct s_pos
{
	int		x;
	int		y;
	char	facing;
}	t_pos;

typedef struct s_map
{
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*no_path;
	t_pos	size;
	t_color	ceiling_color;
	t_color	floor_color;
	t_list	*map;
}	t_map;

typedef struct s_window
{
	void		*mlx;
	void		*win;
	t_pos		size;
}	t_window;

typedef struct s_data
{
	void		*img;
	char		*err_msg;
	char		*map_path;
	t_color		*draw;
	t_window	*mlx;
	t_map		*m_info;
	t_pos		player;
}	t_data;

//-----PARSING-----//
int		parsing(t_data *data);
//-----------------//
//------UTILS------//
int		allocate_game_data(t_data *data, char **av);
void	init_subdata(t_data *data);
void	init_game_data(t_data *data, char **av);
void	free_game_data(t_data *data);
void	exit_game(t_data *data, char *msg);
//-----------------//

#endif