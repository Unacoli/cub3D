/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:57:41 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/12 00:25:24 by tmoragli         ###   ########.fr       */
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
		ft_printf("Error\nNot all elements were disposed, missing %d\n", 6 - elems);
		return (NULL);
	}
	return (file_line);
}

void	fill_map_array(t_data *data, t_list *map)
{
	int		i;
	char	*line;

	i = 0;
	while(map)
	{
		line = (char *)(map->content);
		data->map[i] = ft_strdup(line);
		i++;
		map = map->next;
	}
}

int	is_player(char c)
{
	if (c != 'N' || c != 'S' || c != 'W' || c != 'E')
		return (1);
	return (0);
}

int	is_border(char **map, int x, int y, int map_size)
{
	if (y == 0 || y == map_size || x == 0 || x == (int)ft_strlen(map[y]))
		return (1);
	return (0);
}

int	is_opened(char	**map, int x, int y, int map_size)
{
	if (x != 0)
		if (map[y][x - 1] != '0' && map[y][x - 1] != '1'
			&& is_player(map[y][x - 1]))
			return (1);
	if (x != (int)ft_strlen(map[y]))
		if (map[y][x + 1] != '0' && map[y][x + 1] != '1'
			&& is_player(map[y][x + 1]))
			return (1);
	if (y != map_size)
		if (map[y + 1][x] != '0' && map[y + 1][x] != '1'
			&& is_player(map[y + 1][x]))
			return (1);
	if (y != 0)
		if (map[y - 1][x] != '0' && map[y - 1][x] != '1'
			&& is_player(map[y - 1][x]))
			return (1);
	return (0);
}

int	check_elem(char **map, int x, int y, int map_size)
{
	if (map[y][x] != '1' && map[y][x] != '0'
	&& map[y][x] != ' ' && is_player(map[y][x]))
		return (ft_printf("Error\nNot a valid map element: %c\n", map[y][x]));
	if ((map[y][x] == '0' && is_border(map, x, y, map_size))
	|| (map[y][x] == '0' && is_opened(map, x, y, map_size)))
		return (ft_printf("Error\nMap is not closed at line: %d column: %d\n", y, x));
	return (0);
}

int	scan_map(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map && map[y])
	{
		x = 0;
		while (map && map[y][x])
		{
			if (check_elem(map, x, y, str_arr_size(map)))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	is_valid_map(t_data *data, t_list *map)
{
	int	map_size;

	map_size = ft_lstsize(map);
	data->map = malloc(sizeof(char *) * (map_size + 1));
	if (!data->map)
		return (-1);
	data->map[map_size] = NULL;
	fill_map_array(data, map);
	if (scan_map(data->map))
		return (1);
	return (0);
}

int	is_valid_file(t_data *data)
{
	t_list	*file;
	t_list	*map;

	file = data->m_info->map;
	map = is_valid_id(file);
	if (!map)
		return (1);
	if (is_valid_map(data, map))
		return (1);
	return (0);
}

int	parsing(t_data *data)
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
