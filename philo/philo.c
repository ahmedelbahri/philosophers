/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:10:04 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/01 10:23:56 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *param)
{
	t_list	*philo;

	philo = (t_list *)param;
	while (philo)
	{
		if (the_time() == 0 && philo->number % 2 == 0)
			usleep(philo->time_to_eat * 1000);
		pthread_mutex_lock(&philo->fork);
		printf("%lld %d has taken a fork\n", the_time(), philo->number);
		pthread_mutex_lock(&philo->next->fork);
		printf("%lld %d has teken a fork\n", the_time(), philo->number);
		philo->last_eat = the_time();
		printf("%lld %d is eating\n", the_time(), philo->number);
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		if (philo->num_of_times)
			philo->n_meals++;
		if (philo->num_of_times && philo->num_of_times <= philo->n_meals)
			break ;
		printf("%lld %d is sleeping\n", the_time(), philo->number);
		usleep(philo->time_to_sleep * 1000);
		printf("%lld %d is thinking\n", the_time(), philo->number);
	}
	return (NULL);
}

int	all_ate(t_list *philo, int philo_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < philo_size)
	{
		if (philo->n_meals >= philo->num_of_times)
			j++;
		philo = philo->next;
		i++;
	}
	if (j == philo_size)
		return (1);
	return (0);
}

void	killer(t_list *philo, int philo_size, t_list *philo_head)
{
	while (1)
	{
		usleep(500);
		if ((the_time() - philo->last_eat) > philo->time_to_die)
		{
			printf("%lld %d died\n", the_time(), philo->number);
			ft_free(philo_head, philo_size);
			break ;
		}
		if ((philo->num_of_times > 0) && all_ate(philo_head, philo_size))
		{
			ft_free(philo_head, philo_size);
			break ;
		}
		philo = philo->next;
	}
}

int	main(int argc, char *argv[])
{
	int		i;
	t_list	*philo;
	t_list	*philo_head;
	int		philo_size;

	i = 0;
	if (args_checker(argc, argv))
		return (0);
	philo = create_philos(argc, argv);
	philo_size = ft_atoi(argv[1]);
	ft_lstlast(philo)->next = philo;
	philo_head = philo;
	while (i < philo_size)
	{
		pthread_mutex_init(&philo->fork, NULL);
		philo->last_eat = 0;
		pthread_create(&philo->philo_thread, NULL, &routine, philo);
		philo = philo->next;
		i++;
	}
	killer(philo, philo_size, philo_head);
	return (0);
}
