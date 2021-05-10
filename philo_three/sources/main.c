/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:43:24 by ahaddad           #+#    #+#             */
/*   Updated: 2021/05/10 14:04:00 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

void	init_thread(t_args *args, t_phl **phl)
{
	int		i;
	char	*name;

	i = 0;
	*phl = malloc(sizeof(t_phl) * args->number_of_philosopher);
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
}

void	create_process(t_phl *phl, t_args *args)
{
	int		i;

	i = -1;
	args->pid_to_kill = malloc(sizeof(pid_t) * args->number_of_philosopher);
	while (++i < args->number_of_philosopher)
	{
		phl[i].pid = fork();
		if (phl[i].pid == -1)
			return ;
		if (phl[i].pid == 0)
		{
			phl->index = 0;
			action_philo_3(&phl[i]);
			exit(0);
		}
		args->pid_to_kill[i] = phl[i].pid;
		usleep(100);
	}
}

void	create_threads(t_phl *phl, t_args *args)
{
	int		i;

	i = -1;
	init_thread(args, &phl);
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
	pthread_create(&phl->thrd1, NULL, check_count_eat, phl);
	pthread_detach(phl->thrd1);
	gettimeofday(&args->time_to_print, NULL);
	create_process(phl, args);
	sem_wait(phl->args->ss_sem);
}

void	ft_free(t_args *args)
{
	int		i;

	i = 0;
	sem_unlink("/file1");
	sem_unlink("/file2");
	sem_unlink("/file4");
	sem_unlink("/file3");
	sem_unlink("/file6");
	while (i < args->number_of_philosopher)
	{
		kill(args->pid_to_kill[i], 9);
		i++;
	}
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
