/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:14:53 by galambey          #+#    #+#             */
/*   Updated: 2023/10/19 13:44:32 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_activate_death(t_philo_pub *p, int i)
{
	int			j;
	long int	tms;

	j = 0;
	while (j < p->nb_philo)
	{
		pthread_mutex_lock(&(p->philo[j]).m_die);
		p->philo[j].die_flag = 1;
		pthread_mutex_unlock(&(p->philo[j]).m_die);
		j++;
	}
	tms = ft_get_timems() - p->start_time;
	usleep(1000);
	pthread_mutex_lock(&p->m_print);
	printf("%ld %d died\n", tms, i + 1);
	pthread_mutex_unlock(&p->m_print);
	return (1);
}

static int	ft_monitoring(t_philo_pub *p, int *finish)
{
	long int	diff;
	int			i;

	i = 0;
	while (i < p->nb_philo)
	{
		pthread_mutex_lock(&(p->philo[i]).m_bd);
		diff = ft_get_timems() - p->philo[i].time_bd;
		pthread_mutex_unlock(&(p->philo[i]).m_bd);
		if (diff >= p->t_die)
			return (ft_activate_death(p, i));
		if (p->nb_dinner > 0)
		{
			pthread_mutex_lock(&p->philo[i].m_die);
			if (p->philo[i].count_dinner >= p->nb_dinner)
				*finish += 1;
			pthread_mutex_unlock(&p->philo[i].m_die);
		}
		i += 1;
	}
	return (0);
}

int	ft_check_time_to_die(t_philo_pub *p)
{
	int			i;
	int			finish;

	i = 0;
	if (p->t_die == 0)
		return (printf("%d %d died\n", 0, i + 1), 0);
	usleep((p->t_die - 10) * 1000);
	while (1)
	{
		finish = 0;
		if (ft_monitoring(p, &finish) == 1)
			return (0);
		if (finish == p->nb_philo)
		{
			while (i < p->nb_philo)
			{
				pthread_mutex_lock(&(p->philo[i]).m_die);
				p->philo[i].die_flag = 1;
				pthread_mutex_unlock(&(p->philo[i]).m_die);
				i++;
			}
			return (0);
		}
		usleep(1000);
	}
}
