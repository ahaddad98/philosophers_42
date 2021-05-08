/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:43:24 by ahaddad           #+#    #+#             */
/*   Updated: 2021/05/08 03:28:32 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

void	init_args(t_args *args, t_phl *phl)
{
	int		i;

	i = 0;
	phl->fork_sem = sem_open("/file", O_CREAT | O_EXCL, 0777, phl->args->number_of_philosopher);
	phl->args->die_sem = sem_open("/file", O_CREAT | O_EXCL, 0777, phl->args->number_of_philosopher);
	phl->args->print_sem = sem_open("/file", O_CREAT | O_EXCL, 0777 , phl->args->number_of_philosopher);
	
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
		// (*phl)[i].mutex_sem = sem_open("file", O_CREAT, S_IRWXU, args->number_of_philosopher);
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
	if ((phl->args->ss_sem = sem_open("/file1", O_CREAT | O_EXCL, 0777, phl->args->number_of_philosopher)) == SEM_FAILED)
	{
		printf("sir asate  12 12\n");
		return ;
	}
	if (sem_wait(phl->args->ss_sem))
		printf("sir asate \n");
	// else
		// printf("amine hyaffdaf \n");
	// phl->eating_count = malloc(sizeof(int)
	// 		* (phl->args->number_of_philosopher));
	// while (++i < phl->args->number_of_philosopher)
	// 	phl->eating_count[i] = 0;
	// while (++k < phl->args->number_of_philosopher)
	// 	phl[k].eating_count = phl[0].eating_count;
	i = 0;
	// gettimeofday(&args->time_to_print, NULL);
	while (i < args->number_of_philosopher)
	{
		pthread_create(&phl[i].thrd, NULL, &action, &phl[i]);
		pthread_detach(phl[i].thrd);
		i++;
		usleep(100);
	}
	sem_wait(phl->args->ss_sem);
}

void	ft_free(t_phl *phl, t_args *args)
{
	int		i;

	i = 0;
	free(args->fork);
	while (i < args->number_of_philosopher)
	{
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
		// ft_free(&phl, &args);
	}
	else
		printf("ERROR IN PARAMETRES\n");
	return (0);
}
