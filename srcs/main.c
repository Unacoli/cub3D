/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:49:09 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/12 15:15:08 by tmoragli         ###   ########.fr       */
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
	game_start(data);
	free_game_data(data);
	ft_printf("game exited\n");
	return (0);
}
