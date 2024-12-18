/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:21:15 by galambey          #+#    #+#             */
/*   Updated: 2023/10/19 13:39:16 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_pass_time(t_philo_pub *p, long int time, int place)
{
	long int	temp;

	temp = ft_get_timems();
	while (ft_get_timems() - temp + 9 <= time)
	{
		usleep(9000);
		pthread_mutex_lock(&p->philo[place].m_die);
		if (p->philo[place].die_flag == DEAD)
			return (pthread_mutex_unlock(&p->philo[place].m_die), 1);
		pthread_mutex_unlock(&p->philo[place].m_die);
	}
	while (ft_get_timems() - temp < time)
	{
		usleep(1000);
		pthread_mutex_lock(&p->philo[place].m_die);
		if (p->philo[place].die_flag == DEAD)
			return (pthread_mutex_unlock(&p->philo[place].m_die), 1);
		pthread_mutex_unlock(&p->philo[place].m_die);
	}
	return (0);
}

long int	ft_get_timems(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	ft_unlock(t_philo_pub *p, int fork_l, int fork_r)
{
	pthread_mutex_unlock(&p->philo[fork_l].m_die);
	pthread_mutex_unlock(&p->philo[fork_l].m_fork);
	pthread_mutex_unlock(&p->philo[fork_r].m_fork);
	return (1);
}
