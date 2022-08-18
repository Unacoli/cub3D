/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:49:09 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/13 02:58:49 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	main(int ac, char **av)
{
	t_data	*data;

	if (ac > 2 || ac < 2)
		return (ft_error("Too many arguments, try ./cub3D \"map_path.cub\""));
	if (!ft_malloc((void **)&(data), sizeof(t_data)))
		return (1);
	init_game_data(data, av);
	cube_start(data);
	mlx_key_hook(data->win, move_player, &data);
	mlx_hook(data->win, DestroyNotify, 1L << 0, win_close, &data);
	mlx_loop(data->mlx);
	free_game_data(data);
	return (0);
}
