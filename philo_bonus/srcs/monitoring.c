/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:14:53 by galambey          #+#    #+#             */
/*   Updated: 2023/10/19 13:20:31 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_monitoring_1(void *p)
{
	int	i;

	i = -1;
	if (waitpid(-1, NULL, 0))
	{
		if (sem_wait(((t_philo *)p)->s_end) == -1)
			write(2, "Error sem_wait\n", 16);
		if (((t_philo *)p)->finish == 1)
			return (NULL);
		((t_philo *)p)->finish = 1;
		if (sem_post(((t_philo *)p)->s_end) == -1)
			write(2, "Error sem_post\n", 16);
		ft_kill((t_philo *)p, -1);
		if (sem_post(((t_philo *)p)->s_count) == -1)
			write(2, "Error sem_post\n", 16);
	}
	return (NULL);
}

void	ft_monitoring_2(t_philo *p)
{
	int	i;

	i = -1;
	while (++i < p->nb_philo)
	{
		if (sem_wait(p->s_count) == -1)
			write(2, "Error sem_wait\n", 16);
		if (sem_wait(p->s_end) == -1)
			write(2, "Error sem_wait\n", 16);
		if (p->finish == 1)
			return ;
		if (sem_post(p->s_end) == -1)
			write(2, "Error sem_wait\n", 16);
	}
	if (sem_wait(p->s_end) == -1)
		write(2, "Error sem_wait\n", 16);
	p->finish = 1;
	if (sem_post(p->s_end) == -1)
		write(2, "Error sem_wait\n", 16);
	i = -1;
	ft_kill(p, -1);
	return ;
}
