/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:27:39 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/05/27 18:45:06 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include<unistd.h>
# include<stdio.h>
# include<pthread.h>
# include<stddef.h>
# include<stddef.h>
# include<semaphore.h>
# include<time.h>
# include<stdlib.h>
# include<sys/time.h>

struct	s_philosophers;
typedef struct s_data
{
	int						nb_philos;
	int						time_die;
	int						time_eat;
	int						time_sleep;
	int						nb_eat;
	int						dieded;
	int						all_eat;
	long long				first_time;
	sem_t					*fork;
	sem_t					write;
	sem_t					check;
	struct s_philosophers	*philos;
}t_data;

typedef struct s_philosophers
{
	int				id;
	int				n_eat;
	int				id_fork;
	int				id_next_fork;
	long long		last_meal;
	sem_t			thread;
	t_data			*data;

}t_filos;

void		routine(t_data	*data;);
int			ft_creat(t_data *all);
int			ft_strlen(char *str);
void		ft_print(t_data *data, int id, char *str);
int			parsing(int ac, char **av, t_data *all);
int			ft_atoi(char	*str);
long long	ft_gettime(void);
int			ft_error(char *str, void *ptr);
void		ft_destroy(t_data *data);
void		ft_eats(t_filos *filo);
int			death(t_data *data, t_filos *filo);
void		ft_sleep(long long time, t_data *data);

#endif
