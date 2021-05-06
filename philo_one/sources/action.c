/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 02:57:45 by amine             #+#    #+#             */
/*   Updated: 2021/05/06 17:07:35 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

int	start_eat(t_phl *phl, int right)
{
	pthread_mutex_lock(&phl->args->fork[right]);
	print_action(phl, 1);
	pthread_mutex_lock(&phl->args->fork[phl->num]);
	print_action(phl, 1);
	pthread_mutex_lock(&phl->mutex);
	print_action(phl, 2);
	gettimeofday(&phl->start_time, NULL);
	usleep(phl->args->time_to_eat * 1000);
	if (check_num_must_eat(phl) && (phl->args->time_must_eat != -1))
		return (1);
	pthread_mutex_unlock(&phl->mutex);
	pthread_mutex_unlock(&phl->args->fork[right]);
	pthread_mutex_unlock(&phl->args->fork[phl->num]);
	if (phl[0].eating_count[phl->num] == phl->args->time_must_eat)
	{
		return (2);
	}
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
	k = start_eat(phl, right);
	if (phl->args->time_must_eat != -1)
	{
		if (k == 1)
			return (1);
		if (k == 2)
			return (2);
	}
	print_action(phl, 3);
	usleep(phl->args->time_to_sleep * 1000);
	print_action(phl, 4);
	return (0);
}
