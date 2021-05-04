/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 02:57:45 by amine             #+#    #+#             */
/*   Updated: 2021/05/04 03:01:32 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

void start_eat(t_phl *phl, int right)
{
    pthread_mutex_lock(&phl->args->fork[right]);
    print_action(phl, 1);
    pthread_mutex_lock(&phl->args->fork[phl->num]);
    print_action(phl, 1);
    pthread_mutex_lock(&phl->mutex);
    print_action(phl, 2);
    gettimeofday(&phl->start_time, NULL);
    usleep(phl->args->time_to_eat * 1000);
    pthread_mutex_unlock(&phl->mutex);
    pthread_mutex_unlock(&phl->args->fork[right]);
    pthread_mutex_unlock(&phl->args->fork[phl->num]);
}

void get_fork(t_phl *phl)
{
    int time = 0;
    int right = phl->num - 1;

    if (right < 0)
        right = phl->args->number_of_philosopher - 1;
    start_eat(phl, right);
    print_action(phl, 3);
    usleep(phl->args->time_to_sleep * 1000);
    print_action(phl, 4);
}