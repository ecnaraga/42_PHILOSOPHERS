/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:59:18 by galambey          #+#    #+#             */
/*   Updated: 2023/10/19 13:45:00 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_take_fork(t_philo_pub *p, int fork, int place)
{
	pthread_mutex_lock(&p->philo[fork].m_fork);
	pthread_mutex_lock(&p->philo[place].m_die);
	if (p->philo[place].die_flag == 0)
	{
		pthread_mutex_unlock(&p->philo[place].m_die);
		pthread_mutex_lock(&p->m_print);
		printf("%ld %d has taken a fork\n", ft_get_timems() - p->start_time,
			place + 1);
		pthread_mutex_unlock(&p->m_print);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&p->philo[place].m_die);
		return (1);
	}
}

static void	ft_count_dinner(t_philo_pub *p, int fork_l)
{
	pthread_mutex_lock(&p->philo[fork_l].m_die);
	p->philo[fork_l].count_dinner += 1;
	pthread_mutex_unlock(&p->philo[fork_l].m_die);
}

int	ft_eat(t_philo_pub *p, int fork_l, int fork_r)
{
	int	i;

	pthread_mutex_lock(&p->philo[fork_l].m_bd);
	p->philo[fork_l].time_bd = ft_get_timems();
	pthread_mutex_unlock(&p->philo[fork_l].m_bd);
	pthread_mutex_lock(&p->philo[fork_l].m_die);
	if (p->philo[fork_l].die_flag == 0)
	{
		pthread_mutex_unlock(&p->philo[fork_l].m_die);
		pthread_mutex_lock(&p->m_print);
		printf("%ld %d is eating\n", p->philo[fork_l].time_bd - p->start_time,
			fork_l + 1);
		pthread_mutex_unlock(&p->m_print);
		i = ft_pass_time(p, p->t_eat, fork_l);
		if (p->nb_dinner > 0)
			ft_count_dinner(p, fork_l);
		pthread_mutex_unlock(&p->philo[fork_l].m_fork);
		pthread_mutex_unlock(&p->philo[fork_r].m_fork);
		return (i);
	}
	else
		return (ft_unlock(p, fork_l, fork_r));
}

int	ft_sleep(t_philo_pub *p, int fork_l)
{
	pthread_mutex_lock(&p->philo[fork_l].m_die);
	if (p->philo[fork_l].die_flag == 0)
	{
		pthread_mutex_unlock(&p->philo[fork_l].m_die);
		pthread_mutex_lock(&p->m_print);
		printf("%ld %d is sleeping\n", ft_get_timems() - p->start_time, fork_l
			+ 1);
		pthread_mutex_unlock(&p->m_print);
		return (ft_pass_time(p, p->t_sleep, fork_l));
	}
	else
	{
		pthread_mutex_unlock(&p->philo[fork_l].m_die);
		return (1);
	}
}

int	ft_think(t_philo_pub *p, int fork_l)
{
	pthread_mutex_lock(&p->philo[fork_l].m_die);
	if (p->philo[fork_l].die_flag == 0)
	{
		pthread_mutex_unlock(&p->philo[fork_l].m_die);
		pthread_mutex_lock(&p->m_print);
		printf("%ld %d is thinking\n", ft_get_timems() - p->start_time, fork_l
			+ 1);
		pthread_mutex_unlock(&p->m_print);
		return (ft_pass_time(p, p->t_think, fork_l));
	}
	else
	{
		pthread_mutex_unlock(&p->philo[fork_l].m_die);
		return (1);
	}
}
