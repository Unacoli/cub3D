/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 00:35:46 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/12 01:02:27 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_id(char *str)
{
	if (str && (ft_strncmp(str, "NO ", 3) && ft_strncmp(str, "WE ", 3)
			&& ft_strncmp(str, "EA ", 3) && ft_strncmp(str, "SO ", 3)
			&& ft_strncmp(str, "C ", 2) && ft_strncmp(str, "F ", 2)))
		return (ft_printf("Error\nNot a valid identifier: %s\n", str));
	return (0);
}

t_list	*is_valid_id(t_list *file_line)
{
	int		elems;
	char	*line;

	elems = 0;
	while (file_line && elems < 6)
	{
		line = file_line->content;
		if (line && ft_isspace(line[0]))
			swap_str(line, ft_strtrim(line, " \t\r\v\f\n"));
		if (check_id(line))
			return (NULL);
		else
			elems++;
		file_line = file_line->next;
	}
	if (elems != 6)
	{
		ft_printf("Error\nNot all elements were disposed, missing %d\n",
			6 - elems);
		return (NULL);
	}
	return (file_line);
}

void	fill_map_array(t_data *data, t_list *map)
{
	int		i;
	char	*line;

	i = 0;
	while (map)
	{
		line = (char *)(map->content);
		data->map[i] = ft_strdup(line);
		i++;
		map = map->next;
	}
}

int	scan_map(char **map, t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (map && map[y])
	{
		x = 0;
		while (map && map[y][x])
		{
			if (!is_player(map[y][x]))
				data->nb_player++;
			if (data->nb_player > 1)
				return (ft_printf("Too many player elements, line: %d column: %d\n",
						y, x));
			if (check_elem(map, x, y, str_arr_size(map)))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	parse_map(t_data *data)
{
	int		ret;
	int		fd;
	char	*line;

	ret = 0;
	fd = open(data->map_path, O_RDONLY);
	if (fd == -1)
		return (ft_error("No map given, couldn't open file"));
	while (get_next_line(fd, &line))
	{
		if (!only_isspace(line))
		{
			ft_lstadd_back(&(data->m_info->map), ft_lstnew(line));
			ft_printf("%s\n", line);
		}
		else
			free(line);
	}
	ft_lstadd_back(&(data->m_info->map), ft_lstnew(line));
	ft_printf("%s\n", line);
	if (is_valid_file(data))
		ret++;
	ft_lstclear(&data->m_info->map, &free);
	return (ret);
}
