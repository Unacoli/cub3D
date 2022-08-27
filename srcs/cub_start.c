/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:37:36 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/27 22:06:18 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_map(t_line *map, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("[%s]\n", map[i].line);
		i++;
	}
}

int	cub_start(t_data *data)
{
	if (parse_map(data, 0))
		return (1);
	else
		start_game(data);
	return (0);
}
