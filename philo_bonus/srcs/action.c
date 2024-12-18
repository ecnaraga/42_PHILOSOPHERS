/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:59:18 by galambey          #+#    #+#             */
/*   Updated: 2023/10/19 13:50:20 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_check_death(t_philo *p, int wait)
{
	if (ft_get_timems() - p->time_bd > p->t_die)
	{
		if (wait == 1 && sem_wait(p->s_print) == -1)
			printf("%ld %d died\n", ft_get_timems() - p->start_time, p->place
				+ 1);
		else
			printf("%ld %d died\n", ft_get_timems() - p->start_time, p->place
				+ 1);
		return (1);
	}
	return (0);
}

int	ft_take_fork(t_philo *p)
{
	if (sem_wait(p->s_forks) == -1)
		return (write(2, "Error sem_wait\n", 16), 1);
	if (sem_wait(p->s_print) == -1)
		return (write(2, "Error sem_wait\n", 16), 1);
	if (ft_check_death(p, 0) == 1)
		return (1);
	printf("%ld %d has taken a fork\n", ft_get_timems() - p->start_time,
		p->place + 1);
	if (sem_post(p->s_print) == -1)
		return (write(2, "Error sem_post\n", 16), 1);
	if (sem_wait(p->s_forks) == -1)
		return (write(2, "Error sem_wait\n", 16), 1);
	if (sem_wait(p->s_print) == -1)
		return (write(2, "Error sem_wait\n", 16), 1);
	if (ft_check_death(p, 0) == 1)
		return (1);
	printf("%ld %d has taken a fork\n", ft_get_timems() - p->start_time,
		p->place + 1);
	if (sem_post(p->s_print) == -1)
		return (write(2, "Error sem_post\n", 16), 1);
	return (0);
}

int	ft_eat(t_philo *p)
{
	int	i;

	if (sem_wait(p->s_print) == -1)
		return (write(2, "Error sem_wait\n", 16), 1);
	p->time_bd = ft_get_timems();
	if (ft_check_death(p, 0) == 1)
		return (1);
	printf("%ld %d is eating\n", p->time_bd - p->start_time, p->place + 1);
	if (sem_post(p->s_print) == -1)
		return (write(2, "Error sem_post\n", 16), 1);
	i = ft_pass_time(p, p->t_eat);
	if (i == 1)
		return (i);
	p->count_dinner += 1;
	if (p->count_dinner == p->nb_dinner)
	{
		if (sem_post(p->s_count) == -1)
			return (write(2, "Error sem_post\n", 16), 1);
	}
	if (sem_post(p->s_forks) == -1)
		return (write(2, "Error sem_post\n", 16), 1);
	if (sem_post(p->s_forks) == -1)
		return (write(2, "Error sem_post\n", 16), 1);
	return (i);
}

int	ft_sleep(t_philo *p)
{
	if (sem_wait(p->s_print) == -1)
		return (write(2, "Error sem_wait\n", 16), 1);
	if (ft_check_death(p, 0) == 1)
		return (1);
	printf("%ld %d is sleeping\n", ft_get_timems() - p->start_time, p->place
		+ 1);
	if (sem_post(p->s_print) == -1)
		return (write(2, "Error sem_post\n", 16), 1);
	return (ft_pass_time(p, p->t_sleep));
}

int	ft_think(t_philo *p)
{
	if (sem_wait(p->s_print) == -1)
		return (write(2, "Error sem_wait\n", 16), 1);
	if (ft_check_death(p, 0) == 1)
		return (1);
	printf("%ld %d is thinking\n", ft_get_timems() - p->start_time, p->place
		+ 1);
	if (sem_post(p->s_print) == -1)
		return (write(2, "Error sem_post\n", 16), 1);
	return (ft_pass_time(p, p->t_think));
}
