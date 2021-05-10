/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:22:34 by ahaddad           #+#    #+#             */
/*   Updated: 2021/05/10 14:03:28 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h> 
# include <signal.h>
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEID 4

typedef struct s_args
{
	int				number_of_philosopher;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_must_eat;
	int				count_eat_all;
	int				time_start;
	int				time_count;
	struct timeval	time_to_print;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	sem_t			*print_sem;
	pthread_mutex_t	die;
	sem_t			*die_sem;
	pthread_mutex_t	ss;
	sem_t			*ss_sem;
	sem_t			*fork_sem;
	sem_t			*sem;
	pid_t			*pid_to_kill;
}				t_args;

typedef struct s_phl
{
	sem_t			*fork_sem;
	int				*eating_count;
	pthread_mutex_t	mutex;
	sem_t			*mutex_sem;
	pthread_mutex_t	mutex1;
	sem_t			*mutex1_sem;
	t_args			*args;
	pthread_t		thrd;
	pthread_t		thrd1;
	int				num;
	int				index;
	pid_t			pid;
	struct timeval	current_time;
	struct timeval	start_time;
	struct timeval	end_time;
}				t_phl;

int				check_args(char **av);
long long		ft_atoi_loong(char *str);
int				ft_atoi(const char *str);
int				start_eat(t_phl *phl, int right);
int				get_fork(t_phl *phl);
void			print_action(t_phl *phl, int action);
void			get_args(char **av, t_args *args);
int				check_num_must_eat(t_phl *phl);
void			*action_philo_3(t_phl *data);
void			*action(void *data);
char			*ft_itoa(int n);
void			*check_count_eat(void *data);
void			init_args(t_args *args, t_phl *phl);
int				init_args1(t_args *args, t_phl *phl);
int				init_args2(t_phl *phl);
void			cree_thread(t_phl *phl, t_args *args);

#endif
