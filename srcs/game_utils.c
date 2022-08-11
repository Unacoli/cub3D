/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:34:15 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/12 00:24:09 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	allocate_game_data(t_data *data, char **av)
{
	if (!ft_malloc((void **)&(data->mlx), sizeof(t_window)))
		return (1);
	if (!ft_malloc((void **)&(data->m_info), sizeof(t_map)))
		return (1);
	data->map_path = ft_strdup(av[1]);
	if (!data->map_path)
		return (1);
	return (0);
}

void	init_subdata(t_data *data)
{
	ft_memset(data->mlx, 0, sizeof(t_window));
	ft_memset(data->m_info, 0, sizeof(t_map));
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
	free(data->mlx);
	free(data->m_info);
	str_arr_free(data->map);
	free(data->map_path);
	free(data);
}

void	exit_game(t_data *data, char *msg)
{
	ft_printf("%s\n", msg);
	free_game_data(data);
	exit(1);
}
