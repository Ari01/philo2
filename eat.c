/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:36:04 by dchheang          #+#    #+#             */
/*   Updated: 2021/12/22 16:16:44 by dchheang         ###   ########.fr       */
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

int		take_fork(t_philo *philo, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	if (check_end_sim(philo, philo->info))
	{
		pthread_mutex_unlock(mutex);
		return (0);
	}
	return (1);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		if (take_fork(philo, philo->lf))
		{
			print_status(philo, philo->info, "has taken a fork");
			if (philo->info->n_philo == 1)
				ft_sleep(philo, philo->info->time_to_die);
			else if (take_fork(philo, philo->rf))
				print_status(philo, philo->info, "has taken a fork");
		}
	}
	else
	{
		if (take_fork(philo, philo->rf))
		{
			print_status(philo, philo->info, "has taken a fork");
			if (take_fork(philo, philo->lf))
				print_status(philo, philo->info, "has taken a fork");
		}
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_unlock(philo->rf);
		pthread_mutex_unlock(philo->lf);
	}
	else
	{
		pthread_mutex_unlock(philo->rf);
		pthread_mutex_unlock(philo->lf);
	}
}

void	eat(t_philo *philo)
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
		}
	}
	ft_sleep(philo, philo->info->time_to_eat);
	drop_forks(philo);
}
