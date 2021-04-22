/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:22:34 by ahaddad           #+#    #+#             */
/*   Updated: 2021/04/22 16:36:40 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_phl
{
    pthread_t   *philos;
    int         number_of_philosopher;
    int         time_to_die;
    int         time_to_eat;
    int         time_to_sleep;
    int         time_must_eat;
}           t_phl;

int         check_args(char **av, int ac);
long long   ft_atoi_loong(char *str);
int         ft_atoi(const char *str);
#endif