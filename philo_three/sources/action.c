/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 02:57:45 by amine             #+#    #+#             */
/*   Updated: 2021/05/09 17:26:26 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

int	start_eat(t_phl *phl, int right)
{
	sem_wait(phl->args->fork_sem);
	print_action(phl, 1);
	sem_wait(phl->args->fork_sem);
	print_action(phl, 1);
	sem_wait(phl->mutex_sem);
	print_action(phl, 2);
	gettimeofday(&phl->start_time, NULL);
	usleep(phl->args->time_to_eat * 1000);
	sem_post(phl->args->sem);
	sem_post(phl->mutex_sem);
	sem_post(phl->args->fork_sem);
	sem_post(phl->args->fork_sem);
	return (0);
}

int	get_fork(t_phl *phl)
{
	int		k;
	int		time;
	int		right;

	right = phl->num - 1;
	time = 0;
	k = 0;
	if (right < 0)
		right = phl->args->number_of_philosopher - 1;
	start_eat(phl, right);
	print_action(phl, 3);
	usleep(phl->args->time_to_sleep * 1000);
	print_action(phl, 4);
	return (0);
}
