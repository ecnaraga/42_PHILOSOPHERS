/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:56:46 by galambey          #+#    #+#             */
/*   Updated: 2023/10/19 13:39:57 by galambey         ###   ########.fr       */
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
	if (err == E_Jo_Thread)
		return (write(2, "Error joining thread\n", 22), E_Jo_Thread);
	if (err == E_Init_Mutex)
		return (write(2, "Error init_mutex\n", 18), E_Init_Mutex);
	if (err == E_Dtry_Mutex)
		return (write(2, "Error destroy_mutex\n", 21), E_Dtry_Mutex);
	return (0);
}

int	ft_error_cr_thread(t_philo_pub *p, int i)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		pthread_mutex_lock(&p->philo[j].m_die);
		p->philo[j].die_flag = DEAD;
		pthread_mutex_unlock(&p->philo[j].m_die);
	}
	return (ft_error(ft_wait_for_philo(p, i, E_Cr_Thread)));
}
