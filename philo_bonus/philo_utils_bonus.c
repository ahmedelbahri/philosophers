/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:46:58 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/02 11:20:34 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned long long int	ft_atoi(char	*str)
{
	unsigned long long int	res;
	int						sign;
	int						i;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	if (str[i] != 0)
		return (0);
	return (res * sign);
}

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

void	ft_patrol(t_data *data)
{
	while (1)
	{
		waitpid(-1, &data->status, 0);
		if (data->status == 0 || data->status == 1)
		{
			killall(data);
			break ;
		}
	}
}

void	killall(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->size)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
	free(data->pids);
}

void	*killer(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	while (1)
	{
		usleep(500);
		if ((the_time() - data->last_eat) > (data->time_to_die))
		{
			sem_wait(data->print);
			printf("%lld %d died\n", the_time(), data->number);
			exit(1);
		}
	}
	return (NULL);
}
