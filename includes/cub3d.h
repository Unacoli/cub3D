/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:20:51 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/16 22:06:53 by tmoragli         ###   ########.fr       */
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

# define SIZE 64
# define ESC 65307
# define RIGHT_ARR 65363
# define LEFT_ARR 65361
# define W 119 // QWERTY
# define A 97
# define S 115
# define D 100
# define Z 122 // AZERTY
# define Q 113
# define PI 3.14159265359
# define P2 PI / 2
# define P3 (3 * PI) / 2
# define FOV 60
# define FACING_UP 0
# define FACING_DOWN 1
# define FACING_LEFT 1
# define FACING_RIGHT 1

typedef struct s_color
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	o;
}	t_color;

typedef struct s_pos
{
	double	x;
	double	y;
	double	o;
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

typedef struct s_keys
{
	int	z;
	int	s;
	int q;
	int d;
	int a;
	int w;
	int	l_arr;
	int	r_arr;
}	t_keys;

typedef struct s_ray
{
	t_pos	goal;
	double	x;
	double	y;
	double	x_dir;
	double	y_dir;
	double	angle;
	double	length;
	int		wall;
}	t_ray;

typedef struct s_data
{
	char		*err_msg;
	double		rad;
	int			s_width;
	int			s_height;
	int			w_width;
	int			w_height;
	char		**map;
	int			nb_player;
	char		*map_path;
	void		*mlx;
	void		*img;
	void		*addr;
	void		*win;
	t_keys		keys;
	t_color		ceiling_color;
	t_color		floor_color;
	t_color		player_color;
	t_color		*draw;
	t_map		*m_info;
	t_pos		player;
	t_ray		ray;
	t_ray		h_ray;
	t_ray		v_ray;
	t_color		white;
}	t_data;

//-----GAME--------//
int		cube_start(t_data *data);
void	start_game(t_data *data);
//-----------------//
//-----INIT--------//
int		allocate_game_data(t_data *data, char **av);
void	init_game_data(t_data *data, char **av);
void	init_subdata(t_data *data);
void	setup_window_size(t_data *data);
void	init_mlx_data(t_data *data, int trash);
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

//-----MOVES-------//
void	turn_player(int keycode, t_data *data);
void	move_player(int keycode, t_data *data);
int		hook_keypress(int keycode, t_data *data);
int		act_keypress(t_data *data);
//-----------------//

//-----DRAW-------//
void	draw_pixel(t_data *d, int x, int y, t_color color);
void	draw_ray(t_data *data, t_pos start, t_ray ray);
void	image(t_data *data);
void	map_fill(t_data *data);
void	draw_player(t_data *data, t_pos pos, t_color color);
//-----------------//

//----RAYCASTING---//
void	raycasting(t_data *data, t_pos start, int nb_rays);
void	set_ray_data(t_data *data, int facing, double precision, double atang);
void	send_rays(t_data *data, t_pos start_point, int nb_rays);
//-----------------//

//------UTILS------//
void	free_game_data(t_data *data);
void	exit_game(t_data *data, char *msg);
t_color	get_rgb(int r, int g, int b, int o);
//-----------------//

//-----MATHS-------//
t_pos	point(int x, int y, char facing);
double	get_rad(double	angle);
double	change_angle(double angle, double iterate, char iterator);
double	get_angle(double rad);
double	get_dist(t_pos start, t_pos end);
//-----------------//


#endif