/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:51:10 by nargouse          #+#    #+#             */
/*   Updated: 2022/08/27 21:52:54 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_text_path(char **texture, char *line, int cut)
{
	if (*texture)
		return (1);
	*texture = ft_substr(line, 3, ft_strlen(line) - cut);
	if (!*texture)
		return (1);
	return (0);
}

int	stock_compass_path(t_data *data, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		if (set_text_path(&data->m_info->no_path, line, 3))
			return (printf("Error\nDuplicate elements were given: %s\n",
					line));
	if (!ft_strncmp(line, "SO ", 3))
		if (set_text_path(&data->m_info->so_path, line, 3))
			return (printf("Error\nDuplicate elements were given: %s\n",
					line));
	if (!ft_strncmp(line, "WE ", 3))
		if (set_text_path(&data->m_info->we_path, line, 3))
			return (printf("Error\nDuplicate elements were given: %s\n",
					line));
	if (!ft_strncmp(line, "EA ", 3))
		if (set_text_path(&data->m_info->ea_path, line, 3))
			return (printf("Error\nDuplicate elements were given: %s\n",
					line));
	return (0);
}

int	stock_element(t_data *data, int *elems, char *line)
{
	*elems += 1;
	if (stock_compass_path(data, line))
		return (1);
	if (!ft_strncmp(line, "F ", 2))
		if (fetch_colors(data, 'F', line + 2))
			return (printf("Error\nFetching colors failed\n"));
	if (!ft_strncmp(line, "C ", 2))
		if (fetch_colors(data, 'C', line + 2))
			return (printf("Error\nFetching colors failed\n"));
	return (0);
}

int	trim_textures(t_data *data)
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
	if (!data->m_info->so_path || !data->m_info->no_path
		|| !data->m_info->ea_path || !data->m_info->we_path)
		return (1);
	return (0);
}
