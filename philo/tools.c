/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 12:32:46 by cabouelw          #+#    #+#             */
/*   Updated: 2021/09/10 12:21:04 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_error(char *msg, t_philo *ph)
{
	printf("%s", msg);
	free(ph->v_static->forks);
	free(ph);
}

void	msgs(t_philo *ph, char *msg)
{
	pthread_mutex_lock(&ph->v_static->msg);
	ph->tmp_time = get_time() - ph->v_static->start;
	printf("%ld %d %s\n", ph->tmp_time, ph->pos + 1, msg);
	pthread_mutex_unlock(&ph->v_static->msg);
}

void	*ft_check_death(void *data)
{
	t_philo	*philo;
	long	check;
	long	time;

	philo = data;
	while (1)
	{
		if (!philo->time_must)
			break ;
		usleep(100);
		check = get_time() - philo->start_eat;
		time = get_time() - philo->start;
		if (philo->v_static->time_death < check)
		{
			pthread_mutex_lock(&philo->v_static->msg);
			pthread_mutex_lock(&philo->v_static->check_died);
			pthread_mutex_unlock(&philo->v_static->prog);
			printf("%ld %d \033[0;31mis died\033[0m\n", time, philo->pos + 1);
			break ;
		}
	}
	return (NULL);
}

void	fork_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->v_static->forks[ph->pos]);
	msgs(ph, "has taken a fork");
	pthread_mutex_lock(&ph->v_static->forks[(ph->pos + 1) \
		% ph->v_static->nb_philo]);
	msgs(ph, "has taken a fork");
	msgs(ph, "\033[0;32mis eating\033[0m");
	ph->start_eat = get_time();
	usleep(ph->v_static->time_eat * 1000);
	pthread_mutex_unlock(&ph->v_static->forks[ph->pos]);
	pthread_mutex_unlock(&ph->v_static->forks[(ph->pos + 1) \
		% ph->v_static->nb_philo]);
}

void	sleep_think(t_philo *ph)
{
	msgs(ph, "is sleeping");
	usleep(ph->v_static->time_sleep * 1000);
	msgs(ph, "is thinking");
}
