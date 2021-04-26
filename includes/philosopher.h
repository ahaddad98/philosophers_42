/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:22:34 by ahaddad           #+#    #+#             */
/*   Updated: 2021/04/25 02:58:51 by amine            ###   ########.fr       */
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

typedef struct s_args
{
    int         number_of_philosopher;
    int         time_to_die;
    int         time_to_eat;
    int         time_to_sleep;
    int         time_must_eat;
    int         check_if_dead;
    int			count_eat_all;
	int			starting_time;
    pthread_mutex_t *fork;
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
}           t_phl;

int         check_args(char **av, int ac);
long long   ft_atoi_loong(char *str);
int         ft_atoi(const char *str);

#endif