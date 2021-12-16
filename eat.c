/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:36:04 by dchheang          #+#    #+#             */
/*   Updated: 2021/12/14 10:25:12 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->lf);
	print_status(philo, philo->info, "has taken a fork");
	pthread_mutex_lock(philo->rf);
	print_status(philo, philo->info, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->rf);
	pthread_mutex_unlock(philo->lf);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->info->eat_mutex);
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&philo->info->eat_mutex);
	print_status(philo, philo->info, "is eating");
	usleep(philo->info->time_to_eat * 1000);
	drop_forks(philo);
	print_status(philo, philo->info, "is sleeping");
	usleep(philo->info->time_to_sleep * 1000);
	print_status(philo, philo->info, "is thinking");
}
