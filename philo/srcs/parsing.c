/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:57:33 by galambey          #+#    #+#             */
/*   Updated: 2023/10/23 10:44:32 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static short int	ft_init_mutex(t_philo_pub *p)
{
	int			i;
	short int	err;

	if (pthread_mutex_init(&p->m_place, NULL) != 0)
		return (ft_error(E_Init_Mutex));
	if (pthread_mutex_init(&p->m_print, NULL) != 0)
		return (pthread_mutex_destroy(&p->m_place), ft_error(E_Init_Mutex));
	i = -1;
	while (++i < p->nb_philo)
	{
		if (pthread_mutex_init(&p->philo[i].m_die, NULL) != 0)
			return (ft_destroy_mutex(p, 1, i, &err), ft_error(E_Init_Mutex));
		if (pthread_mutex_init(&p->philo[i].m_fork, NULL) != 0)
			return (ft_destroy_mutex(p, 2, i, &err), ft_error(E_Init_Mutex));
		if (pthread_mutex_init(&p->philo[i].m_bd, NULL) != 0)
			return (ft_destroy_mutex(p, 3, i, &err), ft_error(E_Init_Mutex));
		if (pthread_mutex_init(&p->philo[i].m_count, NULL) != 0)
			return (ft_destroy_mutex(p, 4, i, &err), ft_error(E_Init_Mutex));
	}
	return (E_OK);
}

static short int	ft_create_philo(t_philo_pub *p)
{
	int			i;
	short int	err;

	err = ft_init_mutex(p);
	if (err != E_OK)
		return (err);
	i = -1;
	p->place = 0;
	p->start_time = ft_get_timems();
	while (++i < p->nb_philo)
	{
		if (pthread_create(&p->philo[i].id, NULL, &routine, p) != 0)
			return (ft_error_cr_thread(p, i));
	}
	return (E_OK);
}

static void	ft_parse(t_philo_pub *p, char **av, int ac, short int *err)
{
	int	i;

	i = -1;
	p->t_die = ft_atol(av[2], err);
	p->t_eat = ft_atol(av[3], err);
	p->t_sleep = ft_atol(av[4], err);
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
	while (++i < p->nb_philo)
	{
		p->philo[i].die_flag = ALIVE;
		p->philo[i].time_bd = 0;
		p->philo[i].count_dinner = 0;
	}
}

static void	ft_build_struct(t_philo_pub *p, char **av, short int *err, int ac)
{
	p->philo = NULL;
	p->nb_philo = ft_atol(av[1], err);
	if (p->nb_philo == 0 || p->nb_philo > 200)
	{
		*err = E_INV_INPUT;
		return ;
	}
	p->philo = (t_philo *)malloc(sizeof(t_philo) * p->nb_philo);
	if (!p->philo)
	{
		*err = E_MALLOC;
		return ;
	}
	ft_parse(p, av, ac, err);
}

int	main(int ac, char **av)
{
	t_philo_pub	p;
	short int	err;

	if (ac < 5 || ac > 6)
	{
		printf("Give me 5 to 6 arguments, no more, no less\n");
		return (1);
	}
	err = 0;
	ft_build_struct(&p, av, &err, ac);
	if (err != 0)
	{
		if (p.philo)
			free(p.philo);
		return (ft_error(err));
	}
	err = ft_create_philo(&p);
	if (err == E_OK)
	{
		if (p.nb_dinner != 0)
			ft_check_time_to_die(&p);
		err = ft_wait_for_philo(&p, -1, E_OK);
	}
	free(p.philo);
	return (err);
}
