/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:43:24 by ahaddad           #+#    #+#             */
/*   Updated: 2021/05/03 04:01:36 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

void get_args(char **av, t_args *args)
{
    args->time_must_eat = -1;
    args->number_of_philosopher = ft_atoi(av[1]);
    args->time_to_die = ft_atoi(av[2]);
    args->time_to_eat = ft_atoi(av[3]);
    args->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        args->time_must_eat = ft_atoi(av[5]);
}

void print(t_args *args)
{
    printf("%d \n", args->number_of_philosopher);
    printf("%d \n", args->time_to_die);
    printf("%d \n", args->time_to_eat);
    printf("%d \n", args->time_to_sleep);
}

void get_fork(t_phl *phl);

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
            exit(1) ;
        }
        pthread_mutex_unlock(&phl->mutex);
        usleep(1000);
    }
    return (NULL);
}

// int    check_count_eat(t_phl *phl)
// {
//     int i;

//     i = 0;
//     while (i < phl->args->number_of_philosopher)
//     {
//         if (phl[i]->)
//         i++;
//     }
//     return (1);
// }

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
        // if (phl->args->eating_count < phl->args->time_must_eat)
            get_fork(phl);
    }
    return (NULL);
}

void init_args(t_args *args, t_phl *phl)
{
    int i;

    i = 0;
    args->fork = malloc(sizeof(pthread_mutex_t) * args->number_of_philosopher);
    pthread_mutex_init(&args->print, NULL);
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
        (*phl)[i].args->eating_count = 0;
        pthread_mutex_init(&(*phl)[i].mutex, NULL);
        i++;
    }
}

void create_threads(t_phl *phl, t_args *args)
{
    int i;

    init_thread(args, &phl);
    init_args(args, phl);
    i = 0;
    gettimeofday(&args->time_to_print, NULL);
    while (i < args->number_of_philosopher)
    {
        pthread_create(&phl[i].thrd, NULL, &action, &phl[i]);
        pthread_detach(phl[i].thrd);
        i++;
        usleep(100);
    }
    while (1);
}

void start_eat(t_phl *phl, int right);
void    print_action(t_phl *phl, int action);

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

void    print_action(t_phl *phl, int action)
{
    struct timeval time_print;
    unsigned int    time = 0;

    gettimeofday(&time_print, NULL);
    time = ((time_print.tv_sec * 1000) + (time_print.tv_usec / 1000)) - ((phl->args->time_to_print.tv_sec * 1000) + (phl->args->time_to_print.tv_usec / 1000));
    pthread_mutex_lock(&phl->args->print);
    if (action == 1)
        printf("%u ==> phl : %d ;  has taken a fork\n",time, phl->num);
    if (action == 2)
    {
        printf("%u ==>phl : %d ;  is eating \n", time,phl->num);
    }
    if (action == 3)
        printf("%u ==>phl : %d ; is sleeping \n",time ,phl->num);
    if (action == 4)
        printf("%u ==>phl : %d ; is thinking\n", time ,phl->num);
    pthread_mutex_unlock(&phl->args->print);
}

void start_eat(t_phl *phl, int right)
{
        // printf("{%d}\n", phl->args->eating_count);
    if (phl->args->eating_count < phl->args->time_must_eat)
        phl->args->eating_count++;
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

void gts(t_phl *phl)
{
}

void time_to_thinhk(t_phl *phl)
{
}

void time_to_die(t_phl *phl)
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