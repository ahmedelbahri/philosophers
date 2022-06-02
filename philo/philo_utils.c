/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:04:16 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/05/27 10:33:53 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long int	the_time(void)
{
	struct timeval					time;
	unsigned long long int			time_spent;
	static unsigned long long int	start;

	gettimeofday(&time, NULL);
	time_spent = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (start == 0)
		start = time_spent;
	return (time_spent - start);
}

int	args_checker(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc > 6)
		return (write(2, "Error:\n too many args.\n", 24));
	if (argc < 5)
		return (write(2, "Error:\n too few args.\n", 23));
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (write(1, "Error:\n wrong args value\n", 26));
		i++;
	}
	return (0);
}

t_list	*create_philos(int argc, char **argv)
{
	int		philo_count;
	int		i;
	t_list	*head;
	t_list	*ret;

	philo_count = ft_atoi(argv[1]);
	i = 0;
	while (i < philo_count)
	{
		if (i == 0)
		{
			head = ft_lstnew(argc, argv);
			ret = head;
		}
		else
		{
			head->next = ft_lstnew(argc, argv);
			head = head->next;
		}
		head->number = i + 1;
		i++;
	}
	return (ret);
}

void	ft_join(t_list *philo, int philo_size)
{
	int	i;

	i = 0;
	while (i < philo_size)
	{
		pthread_join(philo->philo_thread, NULL);
		philo = philo->next;
		i++;
	}
}

void	ft_free(t_list *philo, int philo_size)
{
	int	i;

	i = 0;
	while (i < philo_size)
	{
		free(philo);
		philo = philo->next;
		i++;
	}
}
