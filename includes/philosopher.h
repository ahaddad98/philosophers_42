/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:22:34 by ahaddad           #+#    #+#             */
/*   Updated: 2021/05/01 15:29:42 by ahaddad          ###   ########.fr       */
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

# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEID 4
 
typedef struct s_args
{
    int         number_of_philosopher;
    int         time_to_die;
    int         time_to_eat;
    int         time_to_sleep;
    int         time_must_eat;
    int         check_if_dead;
    int			count_eat_all;
	int			time_start;
	int			time_count;

    pthread_mutex_t *fork; 
    pthread_mutex_t print; 
}   t_args;

typedef struct s_phl
{
    pthread_mutex_t mutex;
    pthread_t		thrd;
    t_args          *args;
    int             go_to;
    int             num;
	int				left_fork;
	int				right_fork;
	int				eating_count;
    struct timeval  current_time;
    struct timeval  start_time;
    struct timeval  end_time;
}           t_phl;

int         check_args(char **av, int ac);
long long   ft_atoi_loong(char *str);
int         ft_atoi(const char *str);

#endif