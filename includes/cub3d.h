/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:20:51 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/13 21:06:39 by tmoragli         ###   ########.fr       */
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

#define SIZE 64
# define ESC 65307
# define RIGHT_ARR 65363
# define LEFT_ARR 65361
# define W 119 // QWERTY
# define A 97
# define S 115
# define D 100
# define Z 112
# define Q 113

typedef struct s_ray
{
	int		found_wall;
	double	grad;
	double	x;
	double	y;
	int		i_x;
	int		i_y;
	double	s_x;
	double	s_y;
	int		o;
	double	length;
}	t_ray;

typedef struct s_color
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	o;
}	t_color;

typedef struct s_player_pos
{
	double	x;
	double	y;
	
}	t_player_pos;

typedef struct s_pos
{
	int		x;
	int		y;
	int		o;
	char	facing;
}	t_pos;

typedef struct s_map
{
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*no_path;
	t_pos	size;
	t_list	*map;
}	t_map;

typedef struct s_data
{
	char		*err_msg;
	char		**map;
	int			nb_player;
	char		*map_path;
	void		*mlx;
	void		*img;
	void		*addr;
	void		*win;
	t_color		ceiling_color;
	t_color		floor_color;
	t_pos		w_size;
	t_pos		screen;
	t_color		*draw;
	t_map		*m_info;
	t_pos		player;
	t_ray		ray;
	t_player_pos	player_2d;
}	t_data;

//-----GAME--------//
int		cube_start(t_data *data);
void	setup_game(t_data *data);
//-----------------//

//-----PARSING-----//
int		parse_map(t_data *data, int fd);
int		is_player(char c);
int		check_id(char *str);
t_list	*is_valid_id(t_list *file_line, t_data *data);
void	trim_textures(t_data *data);
void	fill_map_array(t_data *data, t_list *map);
int		scan_map(char **map, t_data *data);
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
t_pos	point(int x, int y, char facing);
void	draw_pixel(t_data *d, int x, int y, t_color color);
//-----------------//

#endif