/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:43:24 by ahaddad           #+#    #+#             */
/*   Updated: 2021/05/07 17:49:56 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

void	init_args(t_args *args, t_phl *phl)
{
	int		i;

	i = 0;
	phl->fork_sem = sem_open("file", O_CREAT, S_IRWXU, phl->args->number_of_philosopher);
	phl->args->die_sem = sem_open("file", O_CREAT, S_IRWXU, phl->args->number_of_philosopher);
	phl->args->print_sem = sem_open("file", O_CREAT, S_IRWXU, phl->args->number_of_philosopher);
	phl->args->ss_sem = sem_open("file", O_CREAT, S_IRWXU, phl->args->number_of_philosopher);
}

void	init_thread(t_args *args, t_phl **phl)
{
	int		i;

	i = 0;
	*phl = malloc(sizeof(t_phl) * args->number_of_philosopher);
	while (i < args->number_of_philosopher)
	{
		(*phl)[i].args = args;
		(*phl)[i].num = i;
		(*phl)[i].mutex_sem = sem_open("file", O_CREAT, S_IRWXU, args->number_of_philosopher);
		// pthread_mutex_init(&(*phl)[i].mutex, NULL);
		i++;
	}
}

void	create_threads(t_phl *phl, t_args *args)
{
	int		i;
	int		k;

	k = 0;
	i = -1;
	init_thread(args, &phl);
	init_args(args, phl);
	// pthread_mutex_lock(&phl->args->ss);
	sem_wait(phl->args->ss_sem);
	phl->eating_count = malloc(sizeof(int)
			* (phl->args->number_of_philosopher));
	while (++i < phl->args->number_of_philosopher)
		phl->eating_count[i] = 0;
	while (++k < phl->args->number_of_philosopher)
		phl[k].eating_count = phl[0].eating_count;
	i = 0;
	gettimeofday(&args->time_to_print, NULL);
	while (i < args->number_of_philosopher)
	{
		pthread_create(&phl[i].thrd, NULL, &action, &phl[i]);
		pthread_detach(phl[i].thrd);
		i++;
		usleep(100);
	}
	sem_wait(phl->args->ss_sem);
	// pthread_mutex_lock(&phl->args->ss);
}

void	ft_free(t_phl *phl, t_args *args)
{
	int		i;

	// pthread_mutex_destroy(&args->print);
	// pthread_mutex_destroy(&args->die);
	// pthread_mutex_destroy(&args->ss);
	i = 0;
	free(args->fork);
	while (i < args->number_of_philosopher)
	{
		// pthread_mutex_destroy(&args->fork[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	int		i;
	int		j;
	t_phl	phl;
	t_args	args;

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
