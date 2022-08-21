/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:40:09 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/21 16:19:04 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	allocate_game_data(t_data *data, char **av)
{
	if (!ft_malloc((void **)&(data->m_info), sizeof(t_map)))
		return (1);
	if (!ft_malloc((void **)&data->text, sizeof(t_text) * 4))
		return (1);
	data->map_path = ft_strdup(av[1]);
	if (!data->map_path)
		return (1);
	return (0);
}
