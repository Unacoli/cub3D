/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 23:55:50 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/09 18:55:39 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_p(t_parse *parse, long unsigned int p)
{
	write(1, "0", 1);
	write(1, "x", 1);
	if (p == 0)
	{
		write(1, "0", 1);
		parse->count += 3;
		return ;
	}
	parse->count += 3;
	ft_putnbr_base_2(p, "0123456789abcdef", parse);
	parse->type = 0;
}
