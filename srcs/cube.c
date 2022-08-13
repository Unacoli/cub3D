/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:12:39 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/13 21:05:16 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(int keycode, t_data *data)
{
	if (keycode == LEFT_ARR)
	{
		if (data->player.o == 360)
			data->player.o = 0;
		data->player.o++;
	}
	if (keycode == RIGHT_ARR)
	{
		if (data->player.o == 0)
			data->player.o = 360;
		data->player.o--;
	}
}

int	hook_keypress(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		printf("You pressed escape key\nGame closed\n");
		mlx_loop_end(data->mlx);
		return (0);
	}
	move_player(keycode, data);
	return (0);
}

void	setup_window_size(t_data *data)
{
	data->w_size.y = (data->screen.y / 100) * 60;
	data->w_size.x = (data->screen.x / 100) * 60;
}

void	init_mlx_data(t_data *data, int trash)
{
	data->mlx = mlx_init();
	mlx_get_screen_size(data->mlx, &data->screen.x, &data->screen.y);
	setup_window_size(data);
	data->win = mlx_new_window(data->mlx, data->w_size.x, data->w_size.y,
				"The room");
	data->img = mlx_new_image(data->mlx, data->w_size.x, data->w_size.y);
	data->addr = mlx_get_data_addr(data->img, &trash, &trash, &trash);
	data->draw = (t_color *)data->addr;
}

void	draw_pixel(t_data *d, int x, int y, t_color color)
{
	if (x >= 0 && x < d->w_size.x && y >= 0 && y < d->w_size.y)
		d->draw[y * d->w_size.x + x] = color;
}

void	draw_ceiling(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->w_size.y)
	{
		x = 0;
		while (x < data->w_size.x)
		{
			draw_pixel(data, x, y, data->ceiling_color);
			x++;
		}
		y++;
	}
}

/*void	send_ray(t_data *data, t_ray ray)
{
	ray.length = data->m_info->size.
	while (!data->found_wall)
	{
		
	}
}*/

void	start_game(t_data *data)
{
	init_mlx_data(data, 0);
	if (data->player.facing == 'N')
		data->player.o = 360;
	if (data->player.facing == 'E')
		data->player.o = 90;
	if (data->player.facing == 'S')
		data->player.o = 180;
	if (data->player.facing == 'W')
		data->player.o = 270;
	//draw_ceiling(data);
	//send_ray(data, data->ray);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_hook(data->win, 33, 1L << 17, mlx_loop_end, data->mlx);
	mlx_hook(data->win, 2, 1L << 0, hook_keypress, data);
	mlx_loop(data->mlx);
}

int	cube_start(t_data *data)
{
	if (parse_map(data, 0))
		return (ft_error("File error, check description above"));
	else
		start_game(data);
	return (0);
}
