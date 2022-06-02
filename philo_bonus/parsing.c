/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:27:15 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/06/02 16:09:42 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str)
{
	long	atoi;
	int		i;

	i = 0;
	atoi = 0;
	while (str[i] == ' ' && str[i] == '\n' && str[i] == '\t' && str[i] == '\v'
		&& str[i] == '\r' && str[i] == '\f')
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (ft_error("error invalid number\n", NULL));
	while (str[i] <= '9' && str[i] >= '0')
	{
		atoi = (atoi * 10) + (str[i] - '0');
		i++;
	}
	if (atoi == 0 || str[i] || atoi > 2147483647)
		return (ft_error("error invalid number\n", NULL));
	return (atoi);
}

int	parsing(int ac, char **av, t_data *data)
{
	if (ac != 5 && ac != 6)
		return (ft_error("error invalid argument\n", NULL));
	if (ac <= 6)
	{
		data->nb_philos = ft_atoi(av[1]);
		data->time_die = ft_atoi(av[2]);
		data->time_eat = ft_atoi(av[3]);
		data->time_sleep = ft_atoi(av[4]);
		data->dieded = 0;
		data->nb_eat = -1;
	}
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5]);
	if (!data->nb_philos || !data->time_die || !data->time_eat
		|| !data->time_sleep || !data->nb_eat)
		return (0);
	return (1);
}
