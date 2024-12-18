/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:21:15 by galambey          #+#    #+#             */
/*   Updated: 2023/10/19 12:38:16 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_pass_time(t_philo *p, long int time)
{
	long int	temp;

	temp = ft_get_timems();
	while (ft_get_timems() - temp + 9 <= time)
	{
		usleep(9000);
		if (ft_check_death(p, 1) == 1)
			return (1);
	}
	while (ft_get_timems() - temp < time)
	{
		usleep(1000);
		if (ft_check_death(p, 1) == 1)
			return (1);
	}
	return (0);
}

long int	ft_get_timems(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}
