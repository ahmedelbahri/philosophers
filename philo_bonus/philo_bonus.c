/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:46:53 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/02 11:19:37 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_print(t_data *data, int id)
{
	sem_wait(data->print);
	if (id == 1)
		printf("%lld %d has taken a fork\n", the_time(), data->number);
	else if (id == 2)
		printf("%lld %d is eating\n", the_time(), data->number);
	else if (id == 3)
		printf("%lld %d is sleeping\n", the_time(), data->number);
	else if (id == 4)
		printf("%lld %d is thinking\n", the_time(), data->number);
	sem_post(data->print);
}

void	ft_routine(t_data *data)
{
	while (1)
	{
		sem_wait(data->forks);
		ft_print(data, 1);
		sem_wait(data->forks);
		ft_print(data, 1);
		data->last_eat = the_time();
		ft_print(data, 2);
		usleep(data->time_to_eat * 1000);
		sem_post(data->forks);
		sem_post(data->forks);
		if (data->num_of_times)
			data->n_meals++;
		if (data->num_of_times && data->num_of_times <= data->n_meals)
			exit(0);
		ft_print(data, 3);
		usleep(data->time_to_sleep * 1000);
		ft_print(data, 4);
	}
}

void	data_fill(t_data *data, char *argv[], int argc)
{
	data->i = 0;
	data->time = the_time();
	data->number = 0;
	data->last_eat = 0;
	data->size = ft_atoi(argv[1]);
	data->pid = 1;
	data->pids = malloc(data->size * sizeof(int));
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_of_times = ft_atoi(argv[5]);
	sem_unlink("forks");
	data->forks = sem_open("forks", O_CREAT, 666, data->size);
	sem_unlink("print");
	data->print = sem_open("print", O_CREAT, 666, 1);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (args_checker(argc, argv))
		return (0);
	data_fill(&data, argv, argc);
	while (data.i < data.size && data.pid != 0)
	{
		usleep(100);
		data.pid = fork();
		data.pids[data.i] = data.pid;
		data.number = (data.i++) + 1;
		if (data.pid == 0)
			pthread_create(&data.health, NULL, &killer, &data);
	}
	if (data.pid == 0)
		ft_routine(&data);
	else
		ft_patrol(&data);
	sem_close(data.forks);
	sem_unlink("forks");
	sem_close(data.print);
	sem_unlink("print");
	return (0);
}
