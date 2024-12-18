/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:32:08 by galambey          #+#    #+#             */
/*   Updated: 2023/10/19 13:44:51 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_destroy_mutex(t_philo_pub *p, int go, int j, short int *err)
{
	int	i;

	i = -1;
	if (pthread_mutex_destroy(&p->m_place) != 0)
		*err = ft_error(E_Dtry_Mutex);
	if (pthread_mutex_destroy(&p->m_print) != 0)
		*err = ft_error(E_Dtry_Mutex);
	while (++i < p->nb_philo)
	{
		if ((go > 1 || (go == 1 && i < j))
			&& pthread_mutex_destroy(&p->philo[i].m_die) != 0)
			*err = ft_error(E_Dtry_Mutex);
		if ((go > 2 || (go == 2 && i < j))
			&& pthread_mutex_destroy(&p->philo[i].m_fork) != 0)
			*err = ft_error(E_Dtry_Mutex);
		if ((go > 3 || (go == 3 && i < j))
			&& pthread_mutex_destroy(&p->philo[i].m_bd) != 0)
			*err = ft_error(E_Dtry_Mutex);
		if ((go > 4 || (go == 4 && i < j))
			&& pthread_mutex_destroy(&p->philo[i].m_count) != 0)
			*err = ft_error(E_Dtry_Mutex);
	}
}

short int	ft_wait_for_philo(t_philo_pub *p, int j, short int err)
{
	int	i;

	i = -1;
	while (j > -1 && ++i < j)
	{
		if (pthread_join(p->philo[i].id, NULL) != 0)
			err = ft_error(E_Jo_Thread);
	}
	while (j == -1 && ++i < p->nb_philo)
	{
		if (pthread_join(p->philo[i].id, NULL) != 0)
			err = ft_error(E_Jo_Thread);
	}
	ft_destroy_mutex(p, 5, 0, &err);
	return (err);
}
