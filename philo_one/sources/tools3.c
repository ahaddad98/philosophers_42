/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:04:41 by ahaddad           #+#    #+#             */
/*   Updated: 2021/04/22 16:05:06 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"


int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int is_number(char *str)
{
    int i = 0;

    while (str[i])
    {
        if (ft_isdigit(str[i]) == 0)
            return (1);
        i++;
    }
    return (0); 
}

int check_args(char **av, int ac)
{
    int i = 1;

    while (av[i])
    {
        if (is_number(av[i]))
            return (1);
        i++;
    }
    return (0);
}
