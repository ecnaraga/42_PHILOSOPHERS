/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:11:56 by galambey          #+#    #+#             */
/*   Updated: 2023/10/19 12:05:53 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

long int	ft_atol(const char *nptr, short int *err)
{
	int			i;
	long int	r;
	int			c_digit;

	i = 0;
	r = 0;
	c_digit = 0;
	if (!nptr || *nptr == '\0')
		return (*err = E_INV_INPUT, 0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		r = r * 10 + nptr[i] - '0';
		i++;
		c_digit++;
	}
	if (r > 2147483647 || c_digit > 10 || (nptr[i]
			&& ft_is_digit(nptr[i]) == 1))
		*err = E_INV_INPUT;
	return (r);
}
