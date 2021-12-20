/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end_sim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:33:29 by dchheang          #+#    #+#             */
/*   Updated: 2021/12/20 10:49:41 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo, t_info *info)
{
	if (get_timediff(philo->time_last_meal) >= (unsigned long)info->time_to_die)
	{
		print_status(philo, philo->info, "died");
		pthread_mutex_lock(&info->death_mutex);
		info->end_sim = 1;
		pthread_mutex_unlock(&info->death_mutex);
		return (1);
	}
	return (0);
}

int	check_eat(t_info *info)
{
	int	ret;

	ret = 0;
	if (info->n_eat > 0)
	{
		pthread_mutex_lock(&info->death_mutex);
		if (info->all_ate >= info->n_philo)
		{
			info->end_sim = 1;
			ret = 1;
		}
		pthread_mutex_unlock(&info->death_mutex);
	}
	return (ret);
}

int	check_end_sim(t_philo *philo, t_info *info)
{
	return (check_death(philo, info) || check_eat(info));
}
