/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:12:39 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/12 16:17:20 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_game(t_data *data)
{
	(void)data;
	return ;
}

void	game_loop(t_data *data)
{
	(void)data;
	while (1)
	{
		printf("game started\n");
		return ;
	}
}

int	game_start(t_data *data)
{
	if (parse_map(data, 0))
		return (ft_error("File error, check description above"));
	else
		game_loop(data);
	return (0);
}
