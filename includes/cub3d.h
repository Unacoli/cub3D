/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:20:51 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/12 01:00:47 by tmoragli         ###   ########.fr       */
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
	char		**map;
	int			nb_player;
	char		*map_path;
	t_color		*draw;
	t_window	*mlx;
	t_map		*m_info;
	t_pos		player;
}	t_data;

//-----PARSING-----//
int		parse_map(t_data *data);
int		is_player(char c);
int		check_id(char *str);
t_list	*is_valid_id(t_list *file_line);
void	fill_map_array(t_data *data, t_list *map);
int		scan_map(char **map, t_data *data);
int		parse_map(t_data *data);
int		check_elem(char **map, int x, int y, int map_size);
int		is_border(char **map, int x, int y, int map_size);
int		is_valid_map(t_data *data, t_list *map);
int		is_valid_file(t_data *data);
int		is_opened(char	**map, int x, int y, int map_size);
//-----------------//
//------UTILS------//
int		allocate_game_data(t_data *data, char **av);
void	init_subdata(t_data *data);
void	init_game_data(t_data *data, char **av);
void	free_game_data(t_data *data);
void	exit_game(t_data *data, char *msg);
//-----------------//

#endif