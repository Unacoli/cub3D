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

	if (check_av(ac, av) == 1)
		return (EXIT_FAILURE);
	if (!ft_malloc((void **)&(data), sizeof(t_data)))
		return (EXIT_FAILURE);
	init_game_data(data, av);
	cub_start(data);
	free_game_data(data);
	return (EXIT_SUCCESS);
}
