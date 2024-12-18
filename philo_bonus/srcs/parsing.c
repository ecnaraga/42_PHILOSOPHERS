/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:57:33 by galambey          #+#    #+#             */
/*   Updated: 2023/10/23 11:41:20 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_parse(t_philo *p, char **av, int ac, short int *err)
{
	p->t_die = ft_atol(av[2], err) - 1;
	p->t_eat = ft_atol(av[3], err);
	p->t_sleep = ft_atol(av[4], err);
	p->time_bd = 0;
	p->count_dinner = 0;
	p->finish = 0;
	if (p->t_sleep <= p->t_eat && p->nb_philo % 2 == 1)
		p->t_think = p->t_eat + p->t_eat - p->t_sleep;
	else if (p->t_sleep <= p->t_eat)
		p->t_think = p->t_eat - p->t_sleep;
	else
		p->t_think = 0;
	if (ac == 6)
		p->nb_dinner = ft_atol(av[5], err);
	else
		p->nb_dinner = -1;
}

short int	ft_sem_create(t_philo *p)
{
	ft_s_unlink();
	p->s_forks = sem_open("forks_use", O_CREAT, 0644, p->nb_philo);
	if (p->s_forks == SEM_FAILED)
		return (ft_clean(p, 4), ft_error(E_SEMAPHORE));
	p->s_print = sem_open("print", O_CREAT, 0644, 1);
	if (p->s_print == SEM_FAILED)
		return (ft_clean(p, 3), ft_error(E_SEMAPHORE));
	p->s_count = sem_open("count", O_CREAT, 0644, 0);
	if (p->s_count == SEM_FAILED)
		return (ft_clean(p, 2), ft_error(E_SEMAPHORE));
	p->s_end = sem_open("end", O_CREAT, 0644, 1);
	if (p->s_end == SEM_FAILED)
		return (ft_clean(p, 1), ft_error(E_SEMAPHORE));
	return (E_OK);
}

void	ft_build_struct(t_philo *p, char **av, short int *err, int ac)
{
	p->pid = NULL;
	p->nb_philo = ft_atol(av[1], err);
	if (p->nb_philo == 0 || p->nb_philo > 200)
	{
		*err = E_INV_INPUT;
		ft_error(*err);
		return ;
	}
	p->pid = (pid_t *)malloc(sizeof(pid_t) * p->nb_philo);
	if (!p->pid)
	{
		*err = E_MALLOC;
		ft_error(*err);
		return ;
	}
	if (ft_sem_create(p) != E_OK)
	{
		*err = E_SEMAPHORE;
		return ;
	}
	ft_parse(p, av, ac, err);
	if (*err != E_OK)
		(ft_clean(p, 0), ft_error(*err));
}

short int	ft_create_philo(t_philo *p)
{
	pid_t	pid;

	p->place = 0;
	p->start_time = ft_get_timems();
	p->time_bd = p->start_time;
	while (p->place < p->nb_philo)
	{
		pid = fork();
		if (pid == -1)
			return (ft_kill(p, p->place), E_FORK);
		if (pid == 0 && p->place % 2 == 0)
		{
			if (p->nb_philo == 1)
				ft_child_alone(p);
			else
				ft_child(p);
		}
		else if (pid == 0 && p->place % 2 == 1)
			(usleep(p->t_eat * 1000), ft_child(p));
		if (p->pid != 0)
			p->pid[p->place] = pid;
		p->place += 1;
	}
	return (E_OK);
}

int	main(int ac, char **av)
{
	t_philo		p;
	short int	err;
	pthread_t	monitor;

	if (ac < 5 || ac > 6)
	{
		printf("Give me 5 to 6 arguments, no more, no less\n");
		return (1);
	}
	err = E_OK;
	ft_build_struct(&p, av, &err, ac);
	if (err != E_OK)
		return (err);
	err = ft_create_philo(&p);
	if (err != E_OK)
		return (ft_clean(&p, 0), ft_error(err));
	if (pthread_create(&monitor, NULL, ft_monitoring_1, &p) != 0)
		return (ft_kill(&p, -1), ft_clean(&p, 0), ft_error(err));
	if (ac == 6)
		ft_monitoring_2(&p);
	if (pthread_join(monitor, NULL) != 0)
		write(2, "Error joining thread\n", 22);
	ft_clean(&p, 0);
	return (err);
}
