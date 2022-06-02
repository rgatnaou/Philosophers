/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:58:56 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/06/02 18:27:35 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_semaphore(t_data *data)
{
	int	n;

	n = data->nb_philos;
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/meal");
	data->fork = sem_open("/forks", O_CREAT, 0700, data->nb_philos);
	data->write = sem_open("/write", O_CREAT, 0700, 1);
	data->meal = sem_open("/meal", O_CREAT, 0700, 1);
	if (data->fork < 0 || data->write < 0 || data->meal < 0)
		return (ft_error("error open semaphore\n", NULL));
	return (1);
}

int	creat_philos(t_data *data)
{
	int	n;

	n = data->nb_philos;
	data->philos = malloc(n * sizeof(t_filos));
	if (!data->philos)
		return (ft_error("error allocation\n", NULL));
	while (--n >= 0)
	{
		data->philos[n].id = n;
		data->philos[n].n_eat = 0;
		data->philos[n].last_meal = 0;
		data->philos[n].data = data;
	}
	return (1);
}

int	ft_creat(t_data *data)
{
	int	i;

	if (!init_semaphore(data))
		return (0);
	if (!creat_philos(data))
		return (0);
	i = 0;
	data->first_time = ft_gettime();
	while (i < data->nb_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
			routine(&data->philos[i]);
		else
			usleep(100);
		i++;
	}
	ft_destroy(data);
	return (1);
}

void	ft_destroy(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->nb_philos)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < data->nb_philos)
				kill(data->philos[i].pid, SIGKILL);
		}
		i++;
	}
	sem_close(data->fork);
	sem_close(data->write);
	sem_close(data->meal);
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/meal");
}
