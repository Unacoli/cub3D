/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_i.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:32:58 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/09 18:55:39 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_d(t_parse *parse, int nb)
{
	(void)parse;
	if (nb == -2147483648)
	{
		ft_s(parse, "-2147483648");
		return ;
	}
	if (nb == 0)
	{
		write(1, "0", 1);
		parse->count++;
		return ;
	}
	if (nb < 0)
		parse->count++;
	parse->count++;
	ft_putnbr_base(nb, "0123456789", parse);
}
