/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:31:41 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/09 18:55:39 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printchar(char c, t_parse *parse)
{	
	write(1, &c, 1);
	parse->count++;
}

void	ft_printarray(char *str, t_parse *parse)
{
	while (str && *str)
	{
		write(1, str, 1);
		str++;
		parse->count++;
	}
}
