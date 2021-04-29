/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:43:24 by ahaddad           #+#    #+#             */
/*   Updated: 2021/04/29 12:40:05 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

void    get_args(char **av, t_args  *args)
{
    args->time_must_eat = -1;
    args->number_of_philosopher = ft_atoi(av[1]);
    args->time_to_die = ft_atoi(av[2]);
    args->time_to_eat = ft_atoi(av[3]);
    args->time_to_sleep = ft_atoi(av[4]);
    if(av[5])
        args->time_must_eat = ft_atoi(av[5]);
}

void    print(t_args *args)
{
    printf("%d \n", args->number_of_philosopher);
    printf("%d \n", args->time_to_die);
    printf("%d \n", args->time_to_eat);
    printf("%d \n", args->time_to_sleep);
    printf("%d \n", args->time_must_eat);
}

void    get_fork(t_phl *phl);

void    *action(void *phl)
{
    t_phl *phl1;

    phl1 = (t_phl *)phl;
    int i = 0;
    
    while (1)
    {
        get_fork(phl);
    }
    return (NULL);
}     

void    init_args(t_args *args, t_phl *phl)
{
    int i;
    
    i = 0;
    args->fork = malloc(sizeof(pthread_mutex_t) * args->number_of_philosopher);
    pthread_mutex_init(&args->mutex, NULL);
    while (i < args->number_of_philosopher)
    {
        pthread_mutex_init(&args->fork[i], NULL);
        i++;
    }
}

void    init_thread(t_args *args, t_phl **phl)
{
    int i;

    i = 0;
    *phl = malloc(sizeof(phl) * args->number_of_philosopher);
    while (i < args->number_of_philosopher)
    {
        (*phl)[i].args = args;
        (*phl)[i].num = i;
        i++;
    }
}

void    create_threads(t_phl *phl, t_args *args)
{
    int i;

    init_thread(args, &phl);
    init_args(args, phl);
    // puts("amine");
    // args->time_start = gettimeofday(&phl->current_time, NULL);
    // printf("===>{%ld}", phl->current_time.tv_sec);
    i = 0;
    while (i < args->number_of_philosopher)
    {
        pthread_create(&phl[i].thrd, NULL, &action, &phl[i]);
        pthread_detach(phl[i].thrd);
        i++;
        usleep(100);
    }
    while (1);
}

void    get_fork(t_phl *phl)
{
    int time = 0;
    int right = phl->num - 1;

    if (right < 0)
        right = phl->args->number_of_philosopher - 1;
    pthread_mutex_lock(&phl->args->fork[right]);
    printf("phl : %d ; fork  : %d \n", phl->num , phl->num);
    pthread_mutex_lock(&phl->args->fork[phl->num]);
    printf("phl : %d ; fork  : %d \n", phl->num , right);
    printf("phl : %d start eating\n", phl->num);
    usleep(phl->args->time_to_eat * 1000);
    // printf("put forks \n");
    pthread_mutex_unlock(&phl->args->fork[phl->num]);
    pthread_mutex_unlock(&phl->args->fork[right]);
    printf("phl : %d start sleeping\n", phl->num);
    usleep(phl->args->time_to_sleep * 1000);
    printf("phl : %d start thinking\n", phl->num);

    // time = gettimeofday(&phl->current_time, NULL) - phl->args->time_start;
}

void    start_eat(t_phl *phl)
{
    
}

void    gts(t_phl *phl)
{
    
}

void    time_to_thinhk(t_phl *phl)
{
    
}

void    time_to_die(t_phl *phl)
{
    
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