/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end_sim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:33:29 by dchheang          #+#    #+#             */
/*   Updated: 2021/12/17 10:20:11 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		pthread_mutex_lock(&info->eat_mutex);
		if (get_timediff(philo[i].time_last_meal) >= (unsigned long)info->time_to_die)
		{
			info->end_sim = 1;
			pthread_mutex_unlock(&info->eat_mutex);
			print_status(&philo[i], info, "died");
			return (1);
		}
		i++;
		pthread_mutex_unlock(&info->eat_mutex);
		usleep(1000);
	}
	return (0);
}

int	check_eat(t_philo *philo, t_info *info)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (info->n_eat < 0)
		return (0);
	while (i < info->n_philo)
	{
		pthread_mutex_lock(&info->eat_mutex);
		if (philo[i].n_eat >= info->n_eat)
			count++;
		i++;
		pthread_mutex_unlock(&info->eat_mutex);
		usleep(1000);
	}
	if (count >= info->n_philo)
	{
		pthread_mutex_lock(&info->eat_mutex);
		info->end_sim = 1;
		pthread_mutex_unlock(&info->eat_mutex);
		return (1);
	}
	return (0);
}

void	check_end_sim(t_philo *philo, t_info *info)
{
	usleep(100000);
	while (1)
	{
		if (check_death(philo, info))
			break ;
		if (check_eat(philo, info))
			break ;
	}
}
