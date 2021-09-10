/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:24:59 by cabouelw          #+#    #+#             */
/*   Updated: 2021/09/09 18:27:58 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_philo(t_philo *ph)
{
	pthread_t	th_philo;

	ph->start_eat = get_time();
	th_philo = NULL;
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
	sem_post(ph->v_static_bns->died);
}

void	ft_start(t_philo *ph)
{
	int	i;

	i = 0;
	sem_wait(ph->v_static_bns->prog);
	while (i < (*ph).v_static_bns->nb_philo)
	{
		ph->pid[i] = fork();
		if (ph->pid[i] == 0)
		{
			ph->pos = i;
			ft_philo(ph);
			exit(0);
		}
		i++;
		usleep(100);
	}
	sem_wait(ph->v_static_bns->prog);
	while (i--)
		kill(ph->pid[i], SIGKILL);
}

void	*check_eat(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	ph->cnt = 0;
	while (1)
	{
		sem_wait(ph->v_static_bns->died);
		ph->cnt++;
		if (ph->cnt == ph->v_static_bns->nb_philo)
		{
			sem_post(ph->v_static_bns->prog);
			break ;
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo			*ph;
	t_static_bns	*var;
	pthread_t		died;
	int				cnt;

	if (argc < 5 || argc > 6)
	{
		printf("Error\n");
		return (1);
	}
	var = (t_static_bns *)malloc(sizeof(t_static_bns));
	ph = ft_parssing_bns(argc, argv, &var);
	if (!ph)
		return (1);
	pthread_create(&died, NULL, &check_eat, (void *)ph);
	pthread_detach(died);
	ft_start(ph);
	cnt = ph->cnt;
	if (!cnt || cnt == ph->v_static_bns->nb_philo * \
		ph->v_static_bns->time_must_eat)
		cnt = 0;
	free(ph->pid);
	free(var);
	free(ph);
	return (cnt);
}
