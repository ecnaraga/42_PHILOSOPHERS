/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_def.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:51:29 by garance           #+#    #+#             */
/*   Updated: 2023/10/19 13:42:45 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DEF_H
# define PHILO_DEF_H

# include <errno.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		id;
	pthread_mutex_t	m_fork;
	long int		time_bd;
	pthread_mutex_t	m_bd;
	int				count_dinner;
	pthread_mutex_t	m_count;
	short int		die_flag;
	pthread_mutex_t	m_die;
}					t_philo;

typedef struct s_philo_pub
{
	t_philo			*philo;
	long int		nb_philo;
	int				place;
	pthread_mutex_t	m_place;
	pthread_mutex_t	m_print;
	long int		t_eat;
	long int		t_die;
	long int		t_sleep;
	long int		t_think;
	int				nb_dinner;
	long int		start_time;
}					t_philo_pub;

enum				e_die_status
{
	ALIVE,
	DEAD,
};

enum				e_err
{
	E_OK,
	E_NB_INPUT,
	E_INV_INPUT,
	E_MALLOC,
	E_Cr_Thread,
	E_Jo_Thread,
	E_Init_Mutex,
	E_Dtry_Mutex,
};

#endif
