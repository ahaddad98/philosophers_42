/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:43:24 by ahaddad           #+#    #+#             */
/*   Updated: 2021/05/09 16:40:04 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

int	init_args1(t_args *args, t_phl *phl)
{
	int		i;

	i = 0;
	args->fork = malloc(sizeof(pthread_mutex_t) * args->number_of_philosopher);
	if (pthread_mutex_init(&args->print, NULL))
		return (0);
	if (pthread_mutex_init(&args->die, NULL))
		return (0);
	if (pthread_mutex_init(&args->ss, NULL))
		return (0);
	if (pthread_mutex_init(&phl->mutex1, NULL))
		return (0);
	while (i < args->number_of_philosopher)
	{
		if (pthread_mutex_init(&args->fork[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

int	init_thread(t_args *args, t_phl **phl)
{
	int		i;

	i = 0;
	*phl = malloc(sizeof(t_phl) * args->number_of_philosopher);
	while (i < args->number_of_philosopher)
	{
		(*phl)[i].args = args;
		(*phl)[i].num = i;
		if (pthread_mutex_init(&(*phl)[i].mutex, NULL))
			return (0);
		i++;
	}
	return (1);
}

void	create_threads(t_phl *phl, t_args *args)
{
	int		i;
	int		k;

	k = 0;
	i = -1;
	if (!init_thread(args, &phl))
		return ;
	if (!init_args1(args, phl))
		return ;
	pthread_mutex_lock(&phl->args->ss);
	phl->eating_count = malloc(sizeof(int)
			*(phl->args->number_of_philosopher));
	if (!phl->eating_count)
		return ;
	while (++i < phl->args->number_of_philosopher)
		phl->eating_count[i] = 0;
	while (++k < phl->args->number_of_philosopher)
		phl[k].eating_count = phl[0].eating_count;
	gettimeofday(&args->time_to_print, NULL);
	cree_thread(phl, args);
	pthread_mutex_lock(&phl->args->ss);
	return ;
}

void	ft_free(t_phl *phl, t_args *args)
{
	int	i;

	if (pthread_mutex_destroy(&args->print))
		return ;
	if (pthread_mutex_destroy(&args->die))
		return ;
	if (pthread_mutex_destroy(&args->ss))
		return ;
	i = 0;
	free(args->fork);
	while (i < args->number_of_philosopher)
	{
		pthread_mutex_destroy(&args->fork[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	int			i;
	int			j;
	t_phl		phl;
	t_args		args;

	if (ac >= 5 && !check_args(av, ac) && ac < 7)
	{
		get_args(av, &args);
		create_threads(&phl, &args);
		ft_free(&phl, &args);
	}
	else
		printf("ERROR IN PARAMETRES\n");
	return (0);
}
