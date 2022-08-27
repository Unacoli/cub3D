/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:20:51 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/27 20:57:39 by nargouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# define XK_MISCELLANY
# define XK_LATIN1
# include <X11/X.h>
# include <X11/keysymdef.h>
# include "../libft/include/libft.h"

# define SIZE 16
# define SIZE_3D 64
# define PI 3.14159265359
# define FOV 30
# define FACING_UP 0
# define FACING_DOWN 1
# define FACING_LEFT 1
# define FACING_RIGHT 1
# define RAD_1 0.0174533 // 1 degree in radian
# define HEIGHT_3D 640
# define WALL_HEIGHT 640
# define WIDTH_3D 1280
# define NB_RAYS 1280
# define MOVE_SPEED 4
# define ROTATE_SPEED 5

# define NORTH_T 0
# define EAST_T 1
# define WEST_T 2
# define SUD_T 3

typedef struct s_rgb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	o;
}	t_rgb;

typedef struct s_color
{
	t_rgb	red;
	t_rgb	white;
	t_rgb	black;
	t_rgb	blue;
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
	int		nb_player;
	int		nb_f;
	int		nb_c;
	t_pos	size;
	t_list	*map;
	t_rgb	ceiling_color;
	t_rgb	floor_color;
}	t_map;

typedef struct s_keys
{
	int	a;
	int	s;
	int	d;
	int	w;
	int	map;
	int	shift;
	int	l_arr;
	int	r_arr;
}	t_keys;

typedef struct s_ray
{
	double	x;
	double	y;
	double	x_dir;
	double	y_dir;
	double	angle;
	double	length;
	double	angle_diff;
}	t_ray;

typedef struct s_line
{
	char	*line;
	int		len;
}	t_line;

typedef struct s_text
{
	void		*img;
	void		*addr;
	t_pos		size;
	t_rgb		*draw;
}	t_text;

typedef struct s_draw
{
	int		wall;
	double	adj;
	double	angle;
	double	tx;
	double	ty_step;
	double	ty_offset;
	double	ty;
	double	line_height;
	double	line_offset;
	double	angle_diff;
	t_pos	pos;
	t_ray	h_ray;
	t_ray	v_ray;
	t_rgb	wall_color;
}	t_draw;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	double		ray_length;
	int			minimap;
	t_pos		p_3d;
	t_draw		*player_ray;
	t_draw		*ray;
	t_text		*screen;
	t_line		*map;
	char		*map_path;
	t_keys		keys;
	t_text		*text;
	t_map		*m_info;
	t_pos		player;
	t_pos		convert;
	t_color		*c_palette;
}	t_data;

//-----GAME--------//
int		cub_start(t_data *data);
void	start_game(t_data *data);
//-----------------//

//-----INIT--------//
int		allocate_game_data(t_data *data, char **av);
void	init_game_data(t_data *data, char **av);
void	init_subdata(t_data *data);
void	init_mlx_data(t_data *data, int trash);
void	assign_text(t_data *data, int nb, char *path);
//-----------------//

//-----PARSING-----//
int		check_av(int ac, char **av);
int		is_inmap(t_data *data, int x, int y);
int		parse_map(t_data *data, int fd);
int		is_player(char c);
int		check_line(char *str, int elems);
int		check_id(t_data *data, char *line, int *elems, int i);
t_list	*is_valid_id(t_list *file_line, t_data *data, int elems);
void	trim_textures(t_data *data);
void	fill_map_array(t_data *data, t_list *map);
int		scan_map(t_line *map, t_data *data, int x, int y);
int		stock_element(t_data *data, int *elems, char *line);
int		check_elem(t_data *data, int x, int y, int map_size);
int		check_coma(char *rgb);
int		check_format(char *rgb);
int		check_numbers(char *rgb);
int		check_space(char *rgb);
int		fetch_colors(t_data *data, char c, char *rgb);
int		is_border(t_data *data, int x, int y, int map_size);
int		is_valid_map(t_data *data, t_list *map);
int		is_valid_file(t_data *data);
int		is_opened(t_data *data, int x, int y);
//-----------------//

//-----MOVES-------//
void	increment_pos(t_data *data, double x, double y);
void	change_player_pos(double orientation,
			t_data *data, t_pos dir, int speed);
void	turn_player(int keycode, t_data *data);
int		move_player(int keycode, t_data *data);
int		hook_keypress(int keycode, t_data *data);
int		act_keypress(t_data *data);
//-----------------//

//-----DRAW-------//
void	draw_pixel(t_data *d, int x, int y, t_rgb color);
void	draw_ray(t_data *data, t_pos start, t_ray *ray, double ray_angle);
void	draw_texture(t_data *data, t_pos p, t_rgb col, int s);
void	image(t_data *data);
void	minimap(t_data *data, int x, int y);
void	draw_line(t_data *data, int rays, t_text *text, t_draw *ray);
void	draw_player(t_data *data, t_pos pos, t_rgb color);
t_rgb	get_pixel_color(t_text text, int x, int y);
void	set_wall(t_data *data, int i);
//-----------------//

//----RAYCASTING---//
void	raycasting(t_data *data, t_pos start, int nb_rays);
void	set_ray_data(t_data *data, int facing, double precision, double atang);
void	send_rays(t_data *data, t_pos start_point, int nb_rays);
void	setup_h_ray_data(t_ray *ray, t_pos start, int facing);
void	h_ray_set(t_data *data, double ray_angle, t_draw *ray);
void	v_ray_set(t_data *data, double ray_angle, t_draw *ray);
void	reset_ray_data(t_ray *ray, t_pos start, int *dof);
void	setup_v_ray_data(t_ray *ray, t_pos start, int facing);
void	cast_v_ray(t_data *data, t_pos start, double ray_angle, t_draw *ray);
void	cast_h_ray(t_data *data, t_pos start, double ray_angle, t_draw *ray);
//-----------------//

//------UTILS------//
void	free_game_data(t_data *data, int status);
void	free_map_data(t_line *map, int size);
void	exit_game(t_data *data, char *msg, int status);
t_rgb	get_rgb(int r, int g, int b, int o);
//-----------------//

//-----MATHS-------//
t_pos	point(int x, int y, char facing);
double	get_rad(double angle);
double	change_angle(double angle, double iterate, char iterator);
double	change_rad_angle(double angle, double iterate, char iterator);
double	get_angle(double rad);
double	get_dist(t_pos start, t_pos end);
int		check_pos(double pos);
t_pos	point_3d(double x, double y);
t_pos	point_2d(double x, double y);
//-----------------//

#endif
