/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:36:04 by dchheang          #+#    #+#             */
/*   Updated: 2021/12/23 03:59:49 by dchheang         ###   ########.fr       */
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

void	take_forks(t_philo *philo, t_fork *first, t_fork *second)
{
	pthread_mutex_lock(&first->mutex);
	if (first->available)
	{
		pthread_mutex_lock(&second->mutex);
		if (second->available)
		{
			print_status(philo, philo->info, "has taken a fork");
			print_status(philo, philo->info, "has taken a fork");
			first->available = 0;
			second->available = 0;
			philo->status++;
		}
		pthread_mutex_unlock(&second->mutex);
	}
	pthread_mutex_unlock(&first->mutex);
}

void	drop_forks(t_fork *first, t_fork *second)
{
	pthread_mutex_lock(&first->mutex);
	pthread_mutex_lock(&second->mutex);
	first->available = 1;
	second->available = 1;
	pthread_mutex_unlock(&second->mutex);
	pthread_mutex_unlock(&first->mutex);
}

void	eat(t_philo *philo)
{
	philo->time_last_meal = get_time();
	print_status(philo, philo->info, "is eating");
	philo->status++;
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
	philo->id % 2 ?
		drop_forks(philo->lf, philo->rf) :
		drop_forks(philo->rf, philo->lf);
}
