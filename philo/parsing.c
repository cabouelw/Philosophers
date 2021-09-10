/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:22:00 by cabouelw          #+#    #+#             */
/*   Updated: 2021/09/09 16:27:15 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_numbrs(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	get_values(int argc, char **argv, t_static *var)
{
	var->nb_philo = ft_atoi(argv[1]);
	var->time_death = ft_atoi(argv[2]);
	var->time_eat = ft_atoi(argv[3]);
	var->time_sleep = ft_atoi(argv[4]);
	var->time_must_eat = -1;
	if (argc == 6)
		var->time_must_eat = ft_atoi(argv[5]);
	if (var->nb_philo < 1 || var->time_death < 60
		|| var->time_eat < 60 || var->time_sleep < 60
		|| (var->time_must_eat < 0 && argc == 6))
		return (1);
	var->start = get_time();
	var->philos = var->nb_philo;
	return (0);
}

void	pth_mutex_init(t_static *var)
{
	int	res;

	res = -1;
	while (++res < var->nb_philo)
		pthread_mutex_init(&var->forks[res], NULL);
	pthread_mutex_init(&var->msg, NULL);
	pthread_mutex_init(&var->prog, NULL);
	pthread_mutex_init(&var->check_died, NULL);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}

t_philo	*ft_parssing(int argc, char **argv, t_static **var)
{
	int		i;
	t_philo	*philo;

	if (check_numbrs(argc, argv) || get_values(argc, argv, *var))
	{
		printf("Error!\n");
		return (NULL);
	}
	philo = NULL;
	(*var)->forks = NULL;
	philo = (t_philo *)malloc(sizeof(t_philo) * (*var)->nb_philo);
	(*var)->forks = (pthread_mutex_t *) \
		malloc(sizeof(pthread_mutex_t) * (*var)->nb_philo);
	pth_mutex_init((*var));
	i = -1;
	while (++i < (*var)->nb_philo)
	{
		philo[i].pos = i;
		philo[i].time_must = (*var)->time_must_eat;
		philo[i].start_eat = 0;
		philo[i].tmp_time = 0;
		philo[i].start = (*var)->start;
		philo[i].v_static = (*var);
	}
	return (philo);
}
