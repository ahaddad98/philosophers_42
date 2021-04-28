/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:22:34 by ahaddad           #+#    #+#             */
/*   Updated: 2021/04/28 17:27:59 by ahaddad          ###   ########.fr       */
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
    pthread_mutex_t *fork; 
    pthread_mutex_t mutex; 
}   t_args;

typedef struct s_phl
{
    pthread_t		thrd;
    t_args          *args;
    int             go_to;
    int             num;
	int				left_fork;
	int				right_fork;
	int				eating_count;
    struct timeval  current_time;
}           t_phl;

int         check_args(char **av, int ac);
long long   ft_atoi_loong(char *str);
int         ft_atoi(const char *str);

#endif