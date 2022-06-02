/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:04:48 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/02 10:07:10 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_list
{
	pthread_t				philo_thread;
	pthread_mutex_t			fork;
	int						number;
	unsigned long long int	time_alive;
	unsigned long long int	time_to_die;
	unsigned long long int	time_to_eat;
	unsigned long long int	time_to_sleep;
	unsigned long long int	last_eat;
	unsigned long long int	n_meals;
	unsigned long long int	num_of_times;
	struct s_list			*next;
}				t_list;

unsigned long long int	ft_atoi(char	*str);
size_t					ft_strlen(const char *s);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **lst, t_list *new);
t_list					*ft_lstnew(int argc, char **argv);
void					ft_free(t_list *philo, int philo_size);
t_list					*create_philos(int argc, char **argv);
int						args_checker(int argc, char **argv);
unsigned long long int	the_time(void);

#endif