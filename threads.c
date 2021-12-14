/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:00:52 by dchheang          #+#    #+#             */
/*   Updated: 2021/12/14 09:21:19 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*run_sim(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo.info->eat_mutex);
		if (philo.info->end_sim)
		{
			pthread_mutex_unlock(&philo.info->eat_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo.info->eat_mutex);
	}
	return (NULL);
}

pthread_t	*init_threads(t_philo *philo, t_info *info)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(sizeof(*threads) * info->n_philo);
	if (threads == NULL)
		return (NULL);
	i = 0;
	info->time_start = get_time();
	while (i < info->n_philo)
	{
		philo[i].time_last_meal = info->time_start;
		if (pthread_create(&threads[i], NULL, run_sim, &philo[i]))
		{
			free(threads);
			return (NULL);
		}
		i++;
	}
	return (threads);
}

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
			print_status(philo, info, "died");
			pthread_mutex_unlock(&info->eat_mutex);
			return (1);
		}
		i++;
		pthread_mutex_unlock(&info->eat_mutex);
		usleep(100);
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
		if (philo[i].n_eat > info->n_eat)
			count++;
		i++;
		pthread_mutex_unlock(&info->eat_mutex);
		usleep(100);
	}
	if (count >= info->n_philo)
	{
		pthread_mutex_lock(&info->eat_mutex);
		info->end_sim = 1;
		pthread_mutex_unlock(&info->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&info->eat_mutex);
	return (0);
}

void	check_end_sim(t_philo *philo, t_info *info)
{
	while (1)
	{
		if (check_death(philo, info))
			break ;
		if (check_eat(philo, info))
			break ;
	}
}

void	run_threads(t_info *info, t_philo *philo)
{
	pthread_t	*threads;
	int			i;

	threads = init_threads(philo, info);
	if (!threads)
		printf("error creating threads\n");
	else
	{
		check_end_sim(philo, info);
		i = 0;
		while (i < info->n_philo)
		{
			if (pthread_join(threads[i], NULL))
			{
				printf("error waiting threads\n");
				break ;
			}
			i++;
		}
		free(threads);
	}
}
