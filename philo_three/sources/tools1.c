/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 03:12:43 by amine             #+#    #+#             */
/*   Updated: 2021/05/09 15:29:18 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

void	ft_free_arr(void **array)
{
	if (*array)
		free(*array);
	*array = NULL;
}

void	ft_free_2dem_arr(void ***arr)
{
	int		i;

	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

int	count_line(char **env)
{
	int		i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char		*ptr;
	long		nbr;
	int			len;

	len = 1;
	nbr = n;
	while (nbr > 9)
	{
		nbr /= 10;
		len++;
	}
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ptr[len] = '\0';
	nbr = n;
	while (nbr > 9)
	{
		ptr[--len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	ptr[--len] = nbr + '0';
	return (ptr);
}

void	*check_count_eat(void *data)
{
	t_phl		*phl;
	int			i;

	i = 0;
	phl = (t_phl *)data;
	while (1)
	{
		sem_wait(phl->args->sem);
		i++;
		if (i == (phl->args->time_must_eat * phl->args->number_of_philosopher))
		{
			sem_wait(phl->args->print_sem);
			printf("DONE\n");
			sem_post(phl->args->ss_sem);
			break ;
		}
	}
	return (NULL);
}
