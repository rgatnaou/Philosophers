/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:14:42 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/06/02 18:31:18 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eats(t_filos *filo)
{
	t_data	*data;

	data = filo->data;
	sem_wait(data->fork);
	ft_print(data, filo->id, "has taken a fork", data->dieded);
	sem_wait(data->fork);
	ft_print(data, filo->id, "has taken a fork", data->dieded);
	sem_wait(data->meal);
	ft_print(data, filo->id, "is eating", data->dieded);
	ft_sleep(data->time_eat, data);
	filo->last_meal = ft_gettime();
	sem_post(data->meal);
	if (data->dieded)
		return ;
	filo->n_eat++;
	sem_post(data->fork);
	sem_post(data->fork);
}

void	*death(void *philo)
{
	int		i;
	t_filos	*filo;

	filo = (t_filos *)philo;
	while (1)
	{
		i = 0;
		sem_wait(filo->data->meal);
		while (i < filo->data->nb_philos && !filo->data->dieded)
		{
			if ((ft_gettime() - filo->last_meal) >= filo->data->time_die)
			{
				filo->data->dieded = 1;
				sem_wait(filo->data->write);
				printf("%lld %d died.\n", ft_gettime() - filo->data->first_time,
					filo->id + 1);
				exit (1);
			}
			i++;
		}
		sem_post(filo->data->meal);
		if (filo->data->nb_eat != -1 && filo->n_eat >= filo->data->nb_eat)
			return (NULL);
	}
	return (NULL);
}
