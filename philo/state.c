/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:14:42 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/06/02 18:24:06 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eats(t_filos *filo)
{
	t_data	*data;

	data = filo->data;
	pthread_mutex_lock(&data->fork[filo->id_fork]);
	ft_print(data, filo->id, "has taken a fork left", data->dieded);
	pthread_mutex_lock(&data->fork[filo->id_next_fork]);
	ft_print(data, filo->id, "has taken a fork right", data->dieded);
	ft_print(data, filo->id, "is eating", data->dieded);
	filo->last_meal = ft_gettime();
	ft_sleep(data->time_eat, data);
	filo->n_eat++;
	pthread_mutex_unlock(&data->fork[filo->id_fork]);
	pthread_mutex_unlock(&data->fork[filo->id_next_fork]);
}

int	finish_meals(t_data *data, t_filos *filo)
{
	int	i;

	i = 0;
	while (data->nb_eat != -1 && filo[i].n_eat >= data->nb_eat
		&& i < data->nb_philos)
		i++;
	if (i == data->nb_philos)
	{
		data->all_eat = 1;
		data->dieded = 1;
		return (0);
	}
	return (1);
}

int	death(t_data *data, t_filos *filo)
{
	int	i;

	while (!data->all_eat)
	{
		i = 0;
		while (i < data->nb_philos && !data->dieded)
		{
			if ((ft_gettime() - filo[i].last_meal) >= data->time_die)
			{
				data->dieded = 1;
				pthread_mutex_lock(&data->write);
				printf("%lld %d died.\n", ft_gettime() - data->first_time,
					filo->id + 1);
				return (0);
			}
			i++;
		}
		if (data->nb_eat != -1)
		{
			if (!finish_meals(data, filo))
				return (0);
		}
	}
	return (1);
}
