/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:43:24 by ahaddad           #+#    #+#             */
/*   Updated: 2021/05/09 17:40:59 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

int	init_args2(t_phl *phl)
{
	int		i;

	i = 0;
	sem_unlink("/file1");
	sem_unlink("/file2");
	sem_unlink("/file3");
	phl->args->fork_sem = sem_open("/file1", O_CREAT, 0777,
			phl->args->number_of_philosopher);
	phl->args->die_sem = sem_open("/file2", O_CREAT, 0777, 1);
	phl->args->print_sem = sem_open("/file3", O_CREAT, 0777, 1);
	return (0);
}

int	init_thread(t_args *args, t_phl **phl)
{
	int		i;
	char	*name;

	i = 0;
	*phl = malloc(sizeof(t_phl) * args->number_of_philosopher);
	if (!(*phl))
		return (0);
	while (i < args->number_of_philosopher)
	{
		(*phl)[i].args = args;
		(*phl)[i].num = i;
		name = ft_itoa(i + 1);
		sem_unlink(name);
		(*phl)[i].mutex_sem = sem_open(name, O_CREAT, 0777, 1);
		i++;
		free(name);
		name = NULL;
	}
	return (1);
}

void	create_threads(t_phl *phl, t_args *args)
{
	int		i;

	i = -1;
	if (!(init_thread(args, &phl)))
		return ;
	init_args2(phl);
	sem_unlink("/file4");
	phl->args->ss_sem = sem_open("/file4", O_CREAT | O_EXCL, 0777, 1);
	if (sem_wait(phl->args->ss_sem))
		printf("error in sem_wait \n");
	phl->eating_count = malloc(sizeof(int)
			* (phl->args->number_of_philosopher));
	while (++i < phl->args->number_of_philosopher)
		phl->eating_count[i] = 0;
	i = 0;
	while (++i < phl->args->number_of_philosopher)
		phl[i].eating_count = phl[0].eating_count;
	i = -1;
	if (gettimeofday(&args->time_to_print, NULL) == -1)
		return ;
	cree_thread(phl, args);
	sem_wait(phl->args->ss_sem);
}

void	ft_free(t_args *args)
{
	int		i;

	i = 0;
	free(args->fork);
	sem_unlink("/file1");
	sem_unlink("/file2");
	sem_unlink("/file3");
	sem_unlink("/file4");
}

int	main(int ac, char **av)
{
	t_phl	phl;
	t_args	args;

	if (ac >= 5 && !check_args(av) && ac < 7)
	{
		get_args(av, &args);
		create_threads(&phl, &args);
		ft_free(&args);
	}
	else
		printf("ERROR IN PARAMETRES\n");
	return (0);
}
