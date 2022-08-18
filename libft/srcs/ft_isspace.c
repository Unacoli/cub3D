/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 19:18:15 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/12 00:28:13 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

int	only_isspace(char *str)
{
	int	i;

	i = 0;
	if (!str || !ft_strlen(str))
		return (1);
	while (str && str[i])
	{
		if (!ft_isspace((int)str[i]))
			return (0);
		i++;
	}
	return (1);
}
