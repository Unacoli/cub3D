/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:15:17 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/25 17:41:34 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*error_ret(char *str)
{
	ft_printf("%s\n", str);
	return (NULL);
}

int	ft_error(char *error)
{
	ft_printf("%s\n", error);
	return (1);
}
