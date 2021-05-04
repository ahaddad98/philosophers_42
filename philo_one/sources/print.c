/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:05:22 by amine             #+#    #+#             */
/*   Updated: 2021/05/04 03:14:52 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

void print_action(t_phl *phl, int action)
{
    struct timeval time_print;
    unsigned int time = 0;

    gettimeofday(&time_print, NULL);
    time = ((time_print.tv_sec * 1000) + (time_print.tv_usec / 1000)) - ((phl->args->time_to_print.tv_sec * 1000) + (phl->args->time_to_print.tv_usec / 1000));
    pthread_mutex_lock(&phl->args->print);
    if (action == 1)
        printf("%u ==> phl : %d ;  has taken a fork\n", time, phl->num);
    if (action == 2)
    {
        printf("%u ==>phl : %d ;  is eating \n", time, phl->num);
        phl[0].eating_count[phl->num] = phl[0].eating_count[phl->num] + 1;
    }
    if (action == 3)
        printf("%u ==>phl : %d ; is sleeping \n", time, phl->num);
    if (action == 4)
        printf("%u ==>phl : %d ; is thinking\n", time, phl->num);
    if (action == 5)
        printf("DONE\n");
    pthread_mutex_unlock(&phl->args->print);
}

int check_num_must_eat(t_phl *phl)
{
    int i;
    i = 0;
    while (i < phl->args->number_of_philosopher)
    {
        if (phl[0].eating_count[i] < phl->args->time_must_eat)
            return (0);
        i++;
    }
    return (1);
}

void *check_die(void *data)
{
    t_phl *phl;
    int time_count;

    phl = (t_phl *)data; 
    while (1)
    {
        pthread_mutex_lock(&phl->mutex);
        time_count = 0;
        gettimeofday(&phl->end_time, NULL);
        time_count = ((phl->end_time.tv_sec * 1000) + (phl->end_time.tv_usec / 1000)) - ((phl->start_time.tv_sec * 1000) + (phl->start_time.tv_usec / 1000));
        if (time_count > phl->args->time_to_die)
        {
            pthread_mutex_lock(&phl->args->print);
            printf("the phl : %d died\n", phl->num);
            exit(1);
        }
        pthread_mutex_unlock(&phl->mutex);
        usleep(1000);
    }
    return (NULL);
}


void *action(void *data)
{
    t_phl *phl;

    phl = (t_phl *)data;
    int i = 0;
    gettimeofday(&phl->start_time, NULL);
    pthread_create(&phl->thrd, NULL, &check_die, phl);
    pthread_detach(phl->thrd);
    while (1)
    {
        if (!check_num_must_eat(phl))
            get_fork(phl);
        else
        {
            print_action(phl, 5);
            exit(0);
        }
    }
    return (NULL);
}

