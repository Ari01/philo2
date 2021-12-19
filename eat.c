/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:36:04 by dchheang          #+#    #+#             */
/*   Updated: 2021/12/18 16:04:13 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_info *info, unsigned long t)
{
	unsigned long	start;

	start = get_time();
	while (get_timediff(start) < t)
	{
		pthread_mutex_lock(&info->eat_mutex);
		if (info->end_sim)
		{
			pthread_mutex_unlock(&info->eat_mutex);
			break ;
		}
		pthread_mutex_unlock(&info->eat_mutex);
	}
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->rf);
		print_status(philo, philo->info, "has taken a fork");
		if (philo->info->n_philo == 1)
			return (0);
		pthread_mutex_lock(philo->lf);
		print_status(philo, philo->info, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->lf);
		print_status(philo, philo->info, "has taken a fork");
		pthread_mutex_lock(philo->rf);
		print_status(philo, philo->info, "has taken a fork");
	}
	return (1);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->rf);
	pthread_mutex_unlock(philo->lf);
}

int	eat(t_philo *philo)
{
	if (take_forks(philo))
	{
		pthread_mutex_lock(&philo->info->eat_mutex);
		philo->time_last_meal = get_time();
		philo->n_eat++;
		pthread_mutex_unlock(&philo->info->eat_mutex);
		print_status(philo, philo->info, "is eating");
		ft_sleep(philo->info, philo->info->time_to_eat);
		drop_forks(philo);
		print_status(philo, philo->info, "is sleeping");
		ft_sleep(philo->info, philo->info->time_to_sleep);
		print_status(philo, philo->info, "is thinking");
		return (1);
	}
	return (0);
}
