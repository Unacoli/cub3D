/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:23:04 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/23 02:53:18 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_window_size(t_data *data)
{
	data->screen->size.y = data->m_info->size.y * 64 + HEIGHT_3D / 2;
	data->screen->size.x = data->m_info->size.x * 64 + WIDTH_3D;
}

void	assign_text(t_data *data, int nb, char *path)
{
	int	trash;
	int	width;
	int	height;

	data->text[nb].img = mlx_xpm_file_to_image(data->mlx, path,
			&width, &height);
	data->text[nb].size.x = (double)width;
	data->text[nb].size.y = (double)height;
	data->text[nb].addr = mlx_get_data_addr(data->text[nb].img,
			&trash, &trash, &trash);
	data->text[nb].draw = (t_rgb *)data->text[nb].addr;
}

void	init_textures_data(t_data *data)
{
	assign_text(data, 0, data->m_info->no_path);
	assign_text(data, 1, data->m_info->so_path);
	assign_text(data, 2, data->m_info->we_path);
	assign_text(data, 3, data->m_info->ea_path);
}

void	init_mlx_data(t_data *data, int trash)
{
	data->mlx = mlx_init();
	setup_window_size(data);
	data->win = mlx_new_window(data->mlx, data->screen->size.x,
			data->screen->size.y, "cub3D");
	data->screen->img = mlx_new_image(data->mlx, data->screen->size.x, data->screen->size.y);
	data->screen->addr = mlx_get_data_addr(data->screen->img, &trash, &trash, &trash);
	data->screen->draw = (t_rgb *)data->screen->addr;
	init_textures_data(data);
}

void	init_subdata(t_data *data)
{
	ft_memset(data->m_info, 0, sizeof(t_map));
	data->c_palette->red = get_rgb(255, 0, 0, 1);
	data->c_palette->white = get_rgb(255, 255, 255, 1);
	data->c_palette->black = get_rgb(0, 0, 0, 0);
	data->c_palette->blue = get_rgb(30, 144, 255, 0);
}

void	init_game_data(t_data *data, char **av)
{
	ft_memset(data, 0, sizeof(t_data));
	if (allocate_game_data(data, av))
		exit_game(data, "Failed allocation, exiting\n");
	init_subdata(data);
}
