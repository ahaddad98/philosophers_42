/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:43:24 by ahaddad           #+#    #+#             */
/*   Updated: 2021/04/22 16:20:46 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

void    get_args(char **av, t_phl *phl)
{
    phl->time_must_eat = -1;
    phl->number_of_philosopher = ft_atoi(av[1]);
    phl->time_to_die = ft_atoi(av[2]);
    phl->time_to_eat = ft_atoi(av[3]);
    phl->time_to_sleep = ft_atoi(av[4]);
    if(av[5])
    {
        puts("amine");
        phl->time_must_eat = ft_atoi(av[5]);
    }
}

int main(int ac, char **av)
{
    int i;
    int j;
    t_phl phl;
    
    if (ac >= 5 && !check_args(av, ac))
    {
        get_args(av, &phl);
        printf("%d \n", phl.number_of_philosopher);
        printf("%d \n", phl.time_to_die);
        printf("%d \n", phl.time_to_eat);
        printf("%d \n", phl.time_to_sleep);
        printf("%d \n", phl.time_must_eat);
    }
    else
        printf("ERROR IN PARAMETRES\n");
    return (0);
}