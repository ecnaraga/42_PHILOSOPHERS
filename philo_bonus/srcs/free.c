/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:32:08 by galambey          #+#    #+#             */
/*   Updated: 2023/10/23 11:39:47 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_clean(t_philo *p, short int go)
{
	if (go < 4 && sem_close(p->s_forks) != E_OK)
		write(2, "Error semaphore\n", 18);
	if (go < 3 && sem_close(p->s_print) != E_OK)
		write(2, "Error semaphore\n", 18);
	if (go < 2 && sem_close(p->s_count) != E_OK)
		write(2, "Error semaphore\n", 18);
	if (go < 1 && sem_close(p->s_end) != E_OK)
		write(2, "Error semaphore\n", 18);
	ft_s_unlink();
	if (p->pid)
		free(p->pid);
}

void	ft_s_unlink(void)
{
	sem_unlink("forks_use");
	sem_unlink("print");
	sem_unlink("count");
	sem_unlink("end");
}

void	ft_kill(t_philo *p, int j)
{
	int	i;

	i = -1;
	while (j != -1 && ++i < j)
	{
		if (kill(p->pid[i], 0) == 0)
		{
			if (kill(p->pid[i], SIGKILL) == -1)
				write(2, "Erreur kill\n", 13);
		}
	}
	while (j == -1 && ++i < p->nb_philo)
	{
		if (kill(p->pid[i], 0) == 0)
		{
			if (kill(p->pid[i], SIGKILL) == -1)
				write(2, "Erreur kill\n", 13);
		}
	}
}
