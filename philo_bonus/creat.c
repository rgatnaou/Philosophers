/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:58:56 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/05/27 18:58:21 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_sem(t_data *data)
{
	int	n;

	n = data->nb_philos;
	data->fork = malloc(n * sizeof(sem_t));
	if (!data->fork)
		return (ft_error("error allocation\n", NULL));
	sem_unlink("sem_fork");
	sem_unlink("sem_write");
	sem_unlink("sem_check");
	while (--n >= 0)
		sem_open("sem_fork", O_CREAT, 0600, data->nb_philos);
	sem_open("sem_write", O_CREAT, 0600, 1);
	sem_open("sem_check", O_CREAT, 0600, 1);
	return (1);
}

int	creat_philos(t_data *data)
{
	int	n;

	n = data->nb_philos;
	data->philos = malloc(n * sizeof(t_filos));
	if (!data->philos)
		return (ft_error("error allocation\n", data->fork));
	while (--n >= 0)
	{
		data->philos[n].id = n;
		data->philos[n].id_fork = n;
		data->philos[n].id_next_fork = (n + 1) % data->nb_philos;
		data->philos[n].n_eat = 0;
		data->philos[n].last_meal = 0;
		data->philos[n].data = data;
	}
	return (1);
}

int	ft_creat(t_data *data)
{
	int	i;
	int pid;

	if (!init_mutex(data))
		return (0);
	if (!creat_philos(data))
		return (0);
	i = 0;
	data->first_time = ft_gettime();
	while (i < data->nb_philos )
	{
		pid = fork();
		if (!pid)
		{
			routine(data);
			exit(0);
		}
		data->philos[i].last_meal = ft_gettime();
		i++;
	}
	return (1);
}

void	ft_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		sem_close(&data->fork[i]);
		i++;
	}
	sem_close(&data->write);
	sem_close(&data->check);
	sem_unlink("sem_fork");
	sem_unlink("sem_write");
	sem_unlink("sem_check");
}
