/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:19:23 by cabouelw          #+#    #+#             */
/*   Updated: 2021/09/09 17:39:35 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_static
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	msg;
	pthread_mutex_t	prog;
	pthread_mutex_t	check_died;
	struct timeval	current_time;
	long			start;
	long			time_eat;
	long			time_death;
	long			time_sleep;
	long			time_must_eat;
	int				nb_philo;
	int				philos;
}					t_static;

typedef struct s_philo
{
	t_static		*v_static;
	struct timeval	time;
	unsigned int	pos;
	int				*pid;
	long			tmp_time;
	long			start_eat;
	long			time_must;
	long			start;
}					t_philo;

t_philo		*ft_parssing(int argc, char **argv, t_static **var);
long		get_time(void);
void		msgs(t_philo *ph, char *msg);
void		*ft_check_death(void *data);
void		fork_eat(t_philo *ph);
void		sleep_think(t_philo *ph);
void		ft_error(char *msg, t_philo *ph);
int			ft_atoi(const char *s);
int			ft_isdigit(int c);

#endif