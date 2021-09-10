/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:14:05 by cabouelw          #+#    #+#             */
/*   Updated: 2021/09/10 18:31:27 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philo(void *data)
{
	t_philo			*ph;
	pthread_t		th_philo;

	ph = data;
	ph->start_eat = get_time();
	pthread_create(&th_philo, NULL, &ft_check_death, ph);
	pthread_detach(th_philo);
	while (1)
	{
		fork_eat(ph);
		if (ph->time_must > 0)
			ph->time_must--;
		if (ph->time_must == 0)
			break ;
		sleep_think(ph);
	}
	ph->v_static->philos--;
	if (!ph->v_static->philos)
		pthread_mutex_unlock(&ph->v_static->prog);
	return (NULL);
}

void	ft_start(t_philo *ph)
{
	int			i;
	int			res;
	pthread_t	th_philo;

	i = 0;
	pthread_mutex_lock(&ph->v_static->prog);
	while (i < (*ph).v_static->nb_philo)
	{
		res = pthread_create(&th_philo, NULL, &ft_philo, (void *)&ph[i]);
		if (res != 0)
			ft_error("Error\n", ph);
		pthread_detach(th_philo);
		i++;
		usleep(100);
	}
	pthread_mutex_lock(&ph->v_static->prog);
}

int	main(int argc, char **argv)
{
	t_philo		*ph;
	t_static	*var;

	if (argc < 5 || argc > 6)
	{
		printf("Error\n");
		return (1);
	}
	var = NULL;
	var = (t_static *)malloc(sizeof(t_static));
	ph = ft_parssing(argc, argv, &var);
	if (!ph)
		return (1);
	ft_start(ph);
	pthread_mutex_destroy(&ph->v_static->prog);
	pthread_mutex_destroy(&ph->v_static->msg);
	pthread_mutex_destroy(&ph->v_static->check_died);
	if (var->forks)
		free(var->forks);
	return (0);
}
