/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:49:09 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/10 17:07:45 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_loop(t_data *data)
{
	(void)data;
	while (1)
	{
		printf("game started\n");
		return ;
	}
}

int	cube_3d(t_data *data)
{
	if (parsing(data))
		return (ft_error(data->err_msg));
	else
		game_loop(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac > 2)
		return (ft_error("Too many arguments, try ./cub3D \"map_path.cub\"\n"));
	if (!ft_malloc((void **)&(data), sizeof(t_data)))
		return (1);
	init_game_data(data, av);
	cube_3d(data);
	free_game_data(data);
	return (0);
}
