/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:11:48 by garance           #+#    #+#             */
/*   Updated: 2023/10/17 10:10:19 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo_def.h"

short int	ft_wait_for_philo(t_philo_pub *p, int j, short int ck_err);
void		ft_destroy_mutex(t_philo_pub *p, int go, int j, short int *ck_err);
long int	ft_atol(const char *nptr, short int *err);
void		*routine(void *p);
int			ft_check_time_to_die(t_philo_pub *p);
int			ft_sleep(t_philo_pub *p, int spoon_l);
int			ft_think(t_philo_pub *p, int spoon_l);
int			ft_take_fork(t_philo_pub *p, int spoon_l, int place);
int			ft_eat(t_philo_pub *p, int fork_l, int fork_r);
int			ft_pass_time(t_philo_pub *p, long int time, int place);
long int	ft_get_timems(void);
int			ft_unlock(t_philo_pub *p, int fork_l, int fork_r);
short int	ft_error(short int err);
int			ft_error_cr_thread(t_philo_pub *p, int i);

#endif