/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:44:03 by cabouelw          #+#    #+#             */
/*   Updated: 2021/09/09 18:25:12 by cabouelw         ###   ########.fr       */
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

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}

int	get_values_bns(int argc, char **argv, t_static_bns *var)
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

void	sem_opn(t_static_bns *var)
{
	sem_unlink("forks");
	sem_unlink("msg");
	sem_unlink("died");
	sem_unlink("prog");
	var->forks = sem_open("forks", O_CREAT, 0666, var->nb_philo);
	var->msg = sem_open("msg", O_CREAT, 0666, 1);
	var->prog = sem_open("prog", O_CREAT, 0666, 1);
	var->died = sem_open("died", O_CREAT, 0666, 0);
}

t_philo	*ft_parssing_bns(int argc, char **argv, t_static_bns **var)
{
	t_philo	*philo;

	if (check_numbrs(argc, argv) || get_values_bns(argc, argv, *var))
	{
		printf("Error!\n");
		return (NULL);
	}
	philo = NULL;
	(*var)->forks = NULL;
	philo = (t_philo *)malloc(sizeof(t_philo));
	philo->pid = (int *)malloc(sizeof(int) * (*var)->nb_philo);
	sem_opn((*var));
	philo->time_must = (*var)->time_must_eat;
	philo->start_eat = 0;
	philo->cnt = 0;
	philo->tmp_time = 0;
	philo->start = (*var)->start;
	philo->v_static_bns = (*var);
	return (philo);
}
