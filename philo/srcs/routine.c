/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:13:04 by galambey          #+#    #+#             */
/*   Updated: 2023/10/19 13:44:38 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_philo_special_case(t_philo_pub *p, int fork_l)
{
	if (p->nb_dinner == 0)
		return ;
	if (p->t_die == 0)
	{
		usleep(1000);
		return ;
	}
	ft_take_fork(p, fork_l, fork_l);
	pthread_mutex_unlock(&p->philo[fork_l].m_fork);
	return ;
}

static void	ft_philo_pair(t_philo_pub *p, int fork_l, int fork_r)
{
	while (1)
	{
		ft_take_fork(p, fork_l, fork_l);
		ft_take_fork(p, fork_r, fork_l);
		if (ft_eat(p, fork_l, fork_r) == 1)
			return ;
		if (ft_sleep(p, fork_l) == 1)
			return ;
		if (ft_think(p, fork_l) == 1)
			return ;
	}
}

static void	ft_philo_impair(t_philo_pub *p, int fork_l, int fork_r)
{
	while (1)
	{
		ft_take_fork(p, fork_r, fork_l);
		ft_take_fork(p, fork_l, fork_l);
		if (ft_eat(p, fork_l, fork_r) == 1)
			return ;
		if (ft_sleep(p, fork_l) == 1)
			return ;
		if (ft_think(p, fork_l) == 1)
			return ;
	}
}

static void	ft_choice_routine(t_philo_pub *p, int fork_l, int fork_r)
{
	long int	curr_time;

	curr_time = 0;
	if (p->nb_philo == 1 || p->t_die == 0 || p->nb_dinner == 0)
		ft_philo_special_case(p, fork_l);
	else
	{
		if (fork_l % 2 == 0)
			ft_philo_pair(p, fork_l, fork_r);
		else
		{
			usleep((p->t_eat - 1) * 1000);
			ft_philo_impair(p, fork_l, fork_r);
		}
	}
}

void	*routine(void *p)
{
	int	fork_r;
	int	fork_l;

	pthread_mutex_lock(&((t_philo_pub *)p)->m_place);
	fork_l = ((t_philo_pub *)p)->place;
	if (fork_l == 0)
		fork_r = ((t_philo_pub *)p)->nb_philo - 1;
	else
		fork_r = fork_l - 1;
	((t_philo_pub *)p)->place += 1;
	pthread_mutex_unlock(&((t_philo_pub *)p)->m_place);
	pthread_mutex_lock(&(((t_philo_pub *)p)->philo[fork_l]).m_bd);
	((t_philo_pub *)p)->philo[fork_l].time_bd = ((t_philo_pub *)p)->start_time;
	pthread_mutex_unlock(&(((t_philo_pub *)p)->philo[fork_l]).m_bd);
	ft_choice_routine((t_philo_pub *)p, fork_l, fork_r);
	return (NULL);
}
