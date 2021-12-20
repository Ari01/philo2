/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:36:04 by dchheang          #+#    #+#             */
/*   Updated: 2021/12/20 14:06:12 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philo, unsigned long t)
{
	unsigned long	start;

	start = get_time();
	while (get_timediff(start) < t)
	{
		if (check_end_sim(philo, philo->info))
			break ;
		usleep(1);
	}
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->lf);
		print_status(philo, philo->info, "has taken a fork");
		if (philo->info->n_philo == 1)
			return (0);
		pthread_mutex_lock(philo->rf);
		print_status(philo, philo->info, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->rf);
		print_status(philo, philo->info, "has taken a fork");
		pthread_mutex_lock(philo->lf);
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
		philo->time_last_meal = get_time();
		print_status(philo, philo->info, "is eating");
		if (philo->info->n_eat >= 0)
		{
			philo->n_eat++;
			if (philo->n_eat >= philo->info->n_eat)
			{
				pthread_mutex_lock(&philo->info->death_mutex);
				philo->info->all_ate++;
				pthread_mutex_unlock(&philo->info->death_mutex);
				drop_forks(philo);
				return (0);
			}
		}
		ft_sleep(philo, philo->info->time_to_eat);
		drop_forks(philo);
		print_status(philo, philo->info, "is sleeping");
		ft_sleep(philo, philo->info->time_to_sleep);
		print_status(philo, philo->info, "is thinking");
		return (1);
	}
	return (0);
}
