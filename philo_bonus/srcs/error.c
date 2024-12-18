/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:56:46 by galambey          #+#    #+#             */
/*   Updated: 2023/10/19 12:17:35 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

short int	ft_error(short int err)
{
	if (err == E_INV_INPUT)
		return (write(2, "Invalid input\n", 15), E_INV_INPUT);
	if (err == E_MALLOC)
		return (write(2, "Malloc failure\n", 16), E_MALLOC);
	if (err == E_Cr_Thread)
		return (write(2, "Error creating thread\n", 23), E_Cr_Thread);
	if (err == E_SEMAPHORE)
		return (write(2, "Error semaphore\n", 18), E_SEMAPHORE);
	return (0);
}
