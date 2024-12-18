/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_def.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:51:29 by garance           #+#    #+#             */
/*   Updated: 2023/10/19 13:50:12 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DEF_H
# define PHILO_DEF_H

# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philo
{
	pid_t		*pid;
	long int	nb_philo;
	int			place;
	sem_t		*s_forks;
	long int	t_eat;
	long int	t_die;
	long int	t_sleep;
	long int	t_think;
	int			nb_dinner;
	long int	start_time;
	long int	time_bd;
	int			count_dinner;
	sem_t		*s_count;
	int			finish;
	sem_t		*s_print;
	sem_t		*s_end;
}				t_philo;

enum			e_die_status
{
	ALIVE,
	DEAD,
};

enum			e_err
{
	E_OK,
	E_NB_INPUT,
	E_INV_INPUT,
	E_MALLOC,
	E_Cr_Thread,
	E_Jo_Thread,
	E_FORK,
	E_SEMAPHORE,
};

#endif