/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:47:13 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/02 11:11:25 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_data
{
	int						i;
	int						size;
	int						number;
	int						status;
	pid_t					pid;
	pid_t					*pids;
	sem_t					*forks;
	sem_t					*print;
	pthread_t				health;
	unsigned long long int	time;
	unsigned long long int	last_eat;
	unsigned long long int	n_meals;
	unsigned long long int	time_to_die;
	unsigned long long int	time_to_eat;
	unsigned long long int	time_to_sleep;
	unsigned long long int	num_of_times;
}				t_data;

unsigned long long int	the_time(void);
unsigned long long int	ft_atoi(char	*str);
void					ft_patrol(t_data *data);
void					*killer(void *param);
void					killall(t_data *data);

#endif