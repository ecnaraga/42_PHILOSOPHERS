/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:13:04 by galambey          #+#    #+#             */
/*   Updated: 2023/10/23 11:04:54 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_child(t_philo *p)
{
	while (1)
	{
		if (ft_take_fork(p) == 1)
		{
			ft_clean(p, 0);
			exit(0);
		}
		else if (ft_eat(p) == 1)
		{
			ft_clean(p, 0);
			exit(0);
		}
		else if (ft_sleep(p) == 1)
		{
			ft_clean(p, 0);
			exit(0);
		}
		else if (ft_think(p) == 1)
		{
			ft_clean(p, 0);
			exit(0);
		}
	}
}

void	ft_child_alone(t_philo *p)
{
	sem_wait(p->s_forks);
	printf("%ld %d has taken a fork\n", ft_get_timems() - p->start_time,
		p->place + 1);
	usleep(p->t_die * 1000);
	printf("%ld %d died\n", ft_get_timems() - p->start_time, p->place + 1);
	ft_clean(p, 0);
	exit(0);
}
