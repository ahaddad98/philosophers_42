/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 02:57:45 by amine             #+#    #+#             */
/*   Updated: 2021/05/05 15:33:34 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

int start_eat(t_phl *phl, int right)
{
    pthread_mutex_lock(&phl->args->fork[right]);
    print_action(phl, 1);
    pthread_mutex_lock(&phl->args->fork[phl->num]);
    print_action(phl, 1);
    pthread_mutex_lock(&phl->mutex);
    print_action(phl, 2);
    gettimeofday(&phl->start_time, NULL);
    usleep(phl->args->time_to_eat * 1000);
    if (check_num_must_eat(phl))
        return (1);
    pthread_mutex_unlock(&phl->mutex);
    pthread_mutex_unlock(&phl->args->fork[right]);
    pthread_mutex_unlock(&phl->args->fork[phl->num]);
    if (phl[0].eating_count[phl->num] == phl->args->time_must_eat)
    {
        return (2);
    }
    // if (check_num_must_eat(phl))
    // {
    //     return (1);
    //     //     print_action(phl, 5);
    //     //     // pthread_mutex_lock(&phl->args->print);
    //     //     // return (amine(NULL, phl));
    //     //     // printf("amine DONE\n");
    //     //     // pthread_mutex_unlock(&phl->args->print);
    //     //     // break ;
    //     //     pthread_mutex_unlock(&phl->mutex1);
    //     //     // return (NULL);
    //     //     // exit(0);
    // }
    return (0);
}

int get_fork(t_phl *phl)
{
    int k;
    int time = 0;
    int right = phl->num - 1;

    if (right < 0)
        right = phl->args->number_of_philosopher - 1;
    // if (check_num_must_eat(phl))
    // {
    //     print_action(phl, 5);
    //     // pthread_mutex_lock(&phl->args->print);
    //     // return (amine(NULL, phl));
    //     // printf("amine DONE\n");
    //     // pthread_mutex_unlock(&phl->args->print);
    //     // break ;
    //     pthread_mutex_unlock(&phl->mutex1);
    //     // return (NULL);
    //     // exit(0);
    // }
    // else if (phl[0].eating_count[phl->num] < phl->args->time_must_eat)
    // {
    k = start_eat(phl, right);
    if (k == 1)
        return (1);
    if (k == 2)
        return (2);
    print_action(phl, 3);
    usleep(phl->args->time_to_sleep * 1000);
    print_action(phl, 4);
    // }
    return (0);
}