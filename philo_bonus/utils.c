/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:27:41 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/06/02 14:20:50 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_error(char *str, void *ptr)
{
	write(2, str, ft_strlen(str));
	if (ptr)
		free(ptr);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_print(t_data *data, int id, char *str, int dieded)
{
	sem_wait(data->write);
	if (!dieded)
	{
		printf("%lld ", ft_gettime() - data->first_time);
		printf("%d ", id + 1);
		printf("%s.\n", str);
	}
	sem_post(data->write);
}

long long	ft_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(long long time, t_data *data)
{
	long long	t;

	t = ft_gettime();
	while (!data->dieded)
	{
		if ((ft_gettime() - t) >= time)
			break ;
		usleep(100);
	}
}
