/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:36:04 by dchheang          #+#    #+#             */
/*   Updated: 2021/12/16 08:53:24 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_info *info, int t)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i >= t)
			break ;
		pthread_mutex_lock(&info->eat_mutex);
		if (info->end_sim)
		{
			pthread_mutex_unlock(&info->eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(&info->eat_mutex);
		i++;
		usleep(1000);
	}
	return (1);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->rf);
	print_status(philo, philo->info, "has taken a fork");
	pthread_mutex_lock(philo->lf);
	print_status(philo, philo->info, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->lf);
	pthread_mutex_unlock(philo->rf);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->info->eat_mutex);
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&philo->info->eat_mutex);
	print_status(philo, philo->info, "is eating");
	if (ft_sleep(philo->info, philo->info->time_to_eat))
		print_status(philo, philo->info, "is sleeping");
	drop_forks(philo);
	if (ft_sleep(philo->info, philo->info->time_to_sleep))
		print_status(philo, philo->info, "is thinking");
}
