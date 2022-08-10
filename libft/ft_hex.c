/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 23:55:45 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/09 18:55:39 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hex(t_parse *parse, unsigned int nb)
{
	if (nb == 0)
	{
		write(1, "0", 1);
		parse->count++;
		return ;
	}
	parse->count++;
	if (parse->type == 'x' && nb > 0)
	{
		ft_putnbr_base_2(nb, "0123456789abcdef", parse);
		return ;
	}
	if (parse->type == 'X' && nb > 0)
	{
		ft_putnbr_base_2(nb, "0123456789ABCDEF", parse);
		return ;
	}
}
