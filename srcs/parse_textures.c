/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:51:10 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/20 13:23:27 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	stock_element(t_data *data, int *elems, char *line)
{
	*elems += 1;
	if (!ft_strncmp(line, "NO ", 3))
		data->m_info->no_path = ft_substr(line, 3, ft_strlen(line) - 3);
	if (!ft_strncmp(line, "EA ", 3))
		data->m_info->ea_path = ft_substr(line, 3, ft_strlen(line) - 3);
	if (!ft_strncmp(line, "SO ", 3))
		data->m_info->so_path = ft_substr(line, 3, ft_strlen(line) - 3);
	if (!ft_strncmp(line, "WE ", 3))
		data->m_info->we_path = ft_substr(line, 3, ft_strlen(line) - 3);
	if (!ft_strncmp(line, "F ", 2))
		fetch_colors(data, 'F', line + 2);
	if (!ft_strncmp(line, "C ", 2))
		fetch_colors(data, 'C', line + 2);
}

void	trim_textures(t_data *data)
{
	if (ft_strchr(data->m_info->no_path, ' '))
		data->m_info->no_path = swap_str(data->m_info->no_path,
				ft_strtrim(data->m_info->no_path, " "));
	if (ft_strchr(data->m_info->ea_path, ' '))
		data->m_info->ea_path = swap_str(data->m_info->ea_path,
				ft_strtrim(data->m_info->ea_path, " "));
	if (ft_strchr(data->m_info->we_path, ' '))
		data->m_info->we_path = swap_str(data->m_info->we_path,
				ft_strtrim(data->m_info->we_path, " "));
	if (ft_strchr(data->m_info->so_path, ' '))
		data->m_info->so_path = swap_str(data->m_info->so_path,
				ft_strtrim(data->m_info->so_path, " "));
}
