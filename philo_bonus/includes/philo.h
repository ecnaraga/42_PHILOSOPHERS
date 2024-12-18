/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:11:48 by garance           #+#    #+#             */
/*   Updated: 2023/10/23 11:02:13 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo_def.h"

long int	ft_atol(const char *nptr, short int *err);
short int	ft_error(short int err);
int			ft_pass_time(t_philo *p, long int time);
long int	ft_get_timems(void);
void		ft_child(t_philo *p);
void		ft_child_alone(t_philo *p);
int			ft_take_fork(t_philo *p);
int			ft_eat(t_philo *p);
int			ft_sleep(t_philo *p);
int			ft_think(t_philo *p);
void		*ft_monitoring_1(void *p);
void		ft_monitoring_2(t_philo *p);
void		ft_clean(t_philo *p, short int go);
void		ft_kill(t_philo *p, int j);
short int	ft_sem_create(t_philo *p);
void		ft_s_unlink(void);
int			ft_check_death(t_philo *p, int wait);

#endif