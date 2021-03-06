/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:26:59 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/06/02 20:42:48 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_filos	*filo;
	t_data	*data;

	filo = (t_filos *)arg;
	data = filo->data;
	if (filo->id % 2)
		usleep(1000);
	while (!data->dieded)
	{
		ft_eats(filo);
		if (data->all_eat || data->dieded)
			return (NULL);
		ft_print(data, filo->id, "is sleeping", data->dieded);
		ft_sleep(data->time_sleep, data);
		ft_print(data, filo->id, "is thinking", data->dieded);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!parsing(ac, av, &data))
		return (0);
	if (!ft_creat(&data))
		return (0);
	death(&data, data.philos);
	ft_destroy(&data);
	free(data.fork);
	free(data.philos);
	return (1);
}
