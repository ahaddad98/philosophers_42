/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:05:22 by amine             #+#    #+#             */
/*   Updated: 2021/05/05 15:48:13 by ahaddad          ###   ########.fr       */
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
            pthread_mutex_lock(&phl->args->die);
            pthread_mutex_lock(&phl->args->print);
            pthread_mutex_unlock(&phl->args->ss);
            printf("the phl : %d died\n", phl->num);
        }
        pthread_mutex_unlock(&phl->mutex);
        usleep(1000);
    }
    return (NULL);
}

void *amine(char *msg, t_phl *phl)
{
    pthread_mutex_lock(&phl->args->die);
    printf("amine haddad gooo\n");
    // pthread_mutex_lock(&phl->args->print);
    pthread_mutex_unlock(&phl->args->ss);
    return (NULL);
}

void *action(void *data)
{
    t_phl *phl;
    int k;
    pthread_mutex_t test;

    phl = (t_phl *)data;
    int i = 0;
    gettimeofday(&phl->start_time, NULL);
    pthread_mutex_init(&test, NULL);
    pthread_create(&phl->thrd, NULL, &check_die, phl);
    pthread_detach(phl->thrd);
    while (1)
    {
        k = get_fork(phl);
        if (k == 2)
            break;
        if (k == 1)
            return (amine(NULL, phl));
    }
    return (NULL);
}
