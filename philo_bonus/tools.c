/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 12:32:46 by cabouelw          #+#    #+#             */
/*   Updated: 2021/09/09 18:29:35 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_error(char *msg, t_philo *ph)
{
	printf("%s", msg);
	free(ph->v_static_bns->forks);
	free(ph);
}

void	msgs(t_philo *ph, char *msg)
{
	sem_wait(ph->v_static_bns->msg);
	ph->tmp_time = get_time() - ph->v_static_bns->start;
	printf("%ld %d %s\n", ph->tmp_time, ph->pos + 1, msg);
	sem_post(ph->v_static_bns->msg);
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
		check = get_time() - philo->start_eat;
		time = get_time() - philo->start;
		if (philo->v_static_bns->time_death < check)
		{
			sem_wait(philo->v_static_bns->msg);
			sem_wait(philo->v_static_bns->check_died);
			printf("%ld %d \033[0;31mis died\033[0m\n", time, philo->pos + 1);
			sem_post(philo->v_static_bns->prog);
		}
	}
	return (NULL);
}

void	fork_eat(t_philo *ph)
{
	sem_wait(ph->v_static_bns->forks);
	msgs(ph, "has taken a fork");
	sem_wait(ph->v_static_bns->forks);
	msgs(ph, "has taken a fork");
	msgs(ph, "\033[0;32mis eating\033[0m");
	ph->start_eat = get_time();
	usleep(ph->v_static_bns->time_eat * 1000);
	sem_post(ph->v_static_bns->forks);
	sem_post(ph->v_static_bns->forks);
}

void	sleep_think(t_philo *ph)
{
	msgs(ph, "is sleeping");
	usleep(ph->v_static_bns->time_sleep * 1000);
	msgs(ph, "is thinking");
}
