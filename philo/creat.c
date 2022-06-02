/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:58:56 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/06/02 16:29:38 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(t_data *data)
{
	int	n;

	n = data->nb_philos;
	data->fork = malloc(n * sizeof(pthread_mutex_t));
	if (!data->fork)
		return (ft_error("error allocation\n", NULL));
	while (--n >= 0)
	{
		if (pthread_mutex_init(&data->fork[n], NULL))
			return (ft_error("error mutex\n", data->fork));
	}
	if (pthread_mutex_init(&data->write, NULL))
		return (ft_error("error mutex\n", data->fork));
	if (pthread_mutex_init(&data->meal, NULL))
		return (ft_error("error mutex\n", data->fork));
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

	if (!init_mutex(data))
		return (0);
	if (!creat_philos(data))
		return (0);
	i = 0;
	data->first_time = ft_gettime();
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine,
				&data->philos[i]))
		{
			free(data->philos);
			return (ft_error("error create thread\n", data->fork));
		}
		if (pthread_detach(data->philos[i].thread))
		{
			free(data->philos);
			return (ft_error("error detach thread\n", data->fork));
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
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->meal);
}
