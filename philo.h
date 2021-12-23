/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 04:51:39 by dchheang          #+#    #+#             */
/*   Updated: 2021/12/23 03:30:40 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>

/************* CONSTS ***************/

# define THINKING	0
# define FORK		1
# define EATING		2
# define SLEEPING	3

/************* STRUCTS **************/

typedef struct s_info
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_eat;
	int				all_ate;
	int				end_sim;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	unsigned long	time_start;
}	t_info;

typedef struct s_fork
{
	int				available;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				n_eat;
	int				status;
	unsigned long	time_last_meal;
	t_info			*info;
	t_fork			*lf;
	t_fork			*rf;
}	t_philo;

/************* FUNCS **************/

/*	UTILS	*/
int				check_limit(int n, int sign, int x);
int				ft_atoi(char *s);
unsigned long	get_time(void);
unsigned long	get_timediff(unsigned long start);
void			print_status(t_philo *philo, t_info *info, char *msg);

/*	PARSER	*/
int				check_info(char **av, t_info info);
int				init_info(char **av, t_info *info);
t_fork			*init_forks(int n_philo);
t_philo			*init_philo(t_info *info, t_fork *forks);

/*	THREADS	*/
void			run_threads(t_info *info, t_philo *philo);

/*	END SIM	*/
int				check_end_sim(t_philo *philo, t_info *info);

/*	EAT	*/
void			take_forks(t_philo *philo, t_fork *first, t_fork *second);
void			eat(t_philo *philo);
void			ft_sleep(t_philo *philo, unsigned long t);

#endif
