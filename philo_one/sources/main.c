/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:43:24 by ahaddad           #+#    #+#             */
/*   Updated: 2021/04/26 04:23:42 by amine            ###   ########.fr       */
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
    {
        puts("amine");
        args->time_must_eat = ft_atoi(av[5]);
    }
}

void    print(t_args *args)
{
    printf("%d \n", args->number_of_philosopher);
    printf("%d \n", args->time_to_die);
    printf("%d \n", args->time_to_eat);
    printf("%d \n", args->time_to_sleep);
    printf("%d \n", args->time_must_eat);
}

void    *action(void *phl)
{
    t_phl *phl1;

    phl1 = (t_phl *)phl;
    while (1)
    {
        puts("rani ragued");
        sleep(1);
    }
    return (NULL);
}     

void    init_args(t_args *args, t_phl *phl)
{
    int i;
    
    i = 0;
    args->fork = malloc(sizeof(pthread_mutex_t) * args->number_of_philosopher);
    while (i < args->number_of_philosopher)
    {
        pthread_mutex_init(args->fork, NULL);
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
        i++;
    }
}



void    create_threads(t_phl *phl, t_args *args)
{
    int i;

    init_thread(args, &phl);
    i = 0;
    while (i < args->number_of_philosopher)
    {
        pthread_create(&phl[i].thrd, NULL, &action, &phl[i]);
        i++;
    }
    i = 0;
    while (i < args->number_of_philosopher)
    {
        pthread_join(phl[i].thrd, NULL);
        i++;
    }
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