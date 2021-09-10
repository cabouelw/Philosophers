/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:19:23 by cabouelw          #+#    #+#             */
/*   Updated: 2021/09/09 17:39:16 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_static_bns
{
	sem_t			*forks;
	sem_t			*msg;
	sem_t			*prog;
	sem_t			*died;
	sem_t			*check_died;
	struct timeval	current_time;
	long			start;
	long			time_eat;
	long			time_death;
	long			time_sleep;
	long			time_must_eat;
	int				nb_philo;
	int				philos;
}					t_static_bns;

typedef struct s_philo
{
	t_static_bns	*v_static_bns;
	struct timeval	time;
	unsigned int	pos;
	int				*pid;
	int				cnt;
	long			tmp_time;
	long			start_eat;
	long			time_must;
	long			start;
}					t_philo;

t_philo		*ft_parssing_bns(int argc, char **argv, t_static_bns **var);
int			get_values_bns(int argc, char **argv, t_static_bns *var);
int			check_numbrs(int argc, char **argv);
void		*ft_check_death(void *data);
void		fork_eat(t_philo *ph);
void		sleep_think(t_philo *ph);
long		get_time(void);
int			ft_atoi(const char *s);
int			ft_isdigit(int c);

#endif