/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:43:24 by ahaddad           #+#    #+#             */
/*   Updated: 2021/05/04 16:54:20 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

void init_args(t_args *args, t_phl *phl)
{
    int i;

    i = 0;
    args->fork = malloc(sizeof(pthread_mutex_t) * args->number_of_philosopher);
    pthread_mutex_init(&args->print, NULL);
    pthread_mutex_init(&phl->mutex1, NULL);
    pthread_mutex_init(&phl->mutex2, NULL);
    while (i < args->number_of_philosopher)
    {
        pthread_mutex_init(&args->fork[i], NULL);
        i++;
    }
}

void init_thread(t_args *args, t_phl **phl)
{
    int i;

    i = 0;
    *phl = malloc(sizeof(t_phl) * args->number_of_philosopher);
    while (i < args->number_of_philosopher)
    {
        (*phl)[i].args = args;
        (*phl)[i].num = i;
        pthread_mutex_init(&(*phl)[i].mutex, NULL);
        i++;
    }
}

void create_threads(t_phl *phl, t_args *args)
{
    int i;
    int k = 1;

    init_thread(args, &phl);
    init_args(args, phl);
    i = 0;
    pthread_mutex_lock(&phl->mutex1);
    phl->eating_count = malloc(sizeof(int) * (phl->args->number_of_philosopher));
    while (i < phl->args->number_of_philosopher)
    {
        phl->eating_count[i] = 0;
        i++;
    }
    while (k < phl->args->number_of_philosopher)
    {
        phl[k].eating_count = phl[0].eating_count;
        k++;
    }
    i = 0;
    gettimeofday(&args->time_to_print, NULL);
    while (i < args->number_of_philosopher)
    {
        pthread_create(&phl[i].thrd, NULL, &action, &phl[i]);
        pthread_detach(phl[i].thrd);
        i++;
        usleep(100);
    }
    pthread_mutex_lock(&phl->mutex1);
    // while (1);
}

int main(int ac, char **av)
{
    int i;
    int j;
    t_phl phl;
    t_args args;

    if (ac >= 5 && !check_args(av, ac) && ac < 7)
    {
        get_args(av, &args);
        create_threads(&phl, &args);
    }
    else
        printf("ERROR IN PARAMETRES\n");
    return (0);
}