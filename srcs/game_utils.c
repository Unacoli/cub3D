/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:34:15 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/14 21:43:08 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	allocate_game_data(t_data *data, char **av)
{
	if (!ft_malloc((void **)&(data->m_info), sizeof(t_map)))
		return (1);
	data->map_path = ft_strdup(av[1]);
	if (!data->map_path)
		return (1);
	return (0);
}

t_color	get_rgb(int r, int g, int b, int o)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.o = o;
	return(color);
}

void	init_subdata(t_data *data)
{
	ft_memset(data->m_info, 0, sizeof(t_map));
	data->player_color = get_rgb(255, 0, 0, 1);
	data->white = get_rgb(255, 255, 255, 1);
}

void	init_game_data(t_data *data, char **av)
{
	ft_memset(data, 0, sizeof(t_data));
	if (allocate_game_data(data, av))
		exit_game(data, "Failed allocation, exiting\n");
	init_subdata(data);
}

void	free_game_data(t_data *data)
{
	free(data->m_info->ea_path);
	free(data->m_info->no_path);
	free(data->m_info->we_path);
	free(data->m_info->so_path);
	free(data->m_info);
	str_arr_free(data->map);
	free(data->map_path);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->mlx)
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	free(data);
}

void	exit_game(t_data *data, char *msg)
{
	ft_printf("%s\n", msg);
	free_game_data(data);
	exit(1);
}
