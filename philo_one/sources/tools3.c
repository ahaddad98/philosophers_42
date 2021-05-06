/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:04:41 by ahaddad           #+#    #+#             */
/*   Updated: 2021/05/06 17:23:27 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	is_number(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_args(char **av, int ac)
{
	int		i;

	i = 1;
	while (av[i])
	{
		if (is_number(av[i]))
			return (1);
		i++;
	}
	return (0);
}

void	get_args(char **av, t_args *args)
{
	args->time_must_eat = -1;
	args->number_of_philosopher = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		args->time_must_eat = ft_atoi(av[5]);
}
